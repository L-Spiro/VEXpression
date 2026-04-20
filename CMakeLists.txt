cmake_minimum_required(VERSION 3.15)
project(VEXpression CXX)

### Detect if we are building for 32-bit or 64-bit.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x64")
    message(STATUS "Configuring for 64-bit architecture.")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(ARCH_DIR "x86")
    message(STATUS "Configuring for 32-bit architecture.")
else()
    set(ARCH_DIR "Unknown")
    message(WARNING "Unknown architecture size!")
endif()

### Route output files to architecture-specific directories so they don't clash.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${ARCH_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${ARCH_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${ARCH_DIR})

### For multi-configuration generators such as Visual Studio, append the config type (Debug/Release).
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config_upper)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/lib/${ARCH_DIR}/${config})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/bin/${ARCH_DIR}/${config})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/bin/${ARCH_DIR}/${config})
endforeach()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Global Compile Definitions
add_compile_definitions(_USE_MATH_DEFINES)

### Locate the Java Runtime.
find_package(Java 11 COMPONENTS Runtime REQUIRED)

### Define Paths.
set(ANTLR_JAR "${CMAKE_SOURCE_DIR}/tools/antlr-4.13.2-complete.jar")
set(GRAMMAR_LEXER "${CMAKE_SOURCE_DIR}/grammar/ExprLexer.g4")
set(GRAMMAR_PARSER "${CMAKE_SOURCE_DIR}/grammar/ExprParser.g4")
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/generated")

### Load the CMake FetchContent Module.
include(FetchContent)

### Configure ANTLR build options BEFORE fetching.
# Turn off tests to save compile time.
set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
# Force a STATIC library. Prevent "DLL Hell" on Windows.
set(WITH_STATIC_CRT OFF CACHE BOOL "" FORCE) 
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

### Tell CMake where to get the code (Bypassing Git)
FetchContent_Declare(
    antlr4_runtime
    URL            https://github.com/antlr/antlr4/archive/refs/tags/4.13.2.zip
    SOURCE_SUBDIR  runtime/Cpp
)

### Actually Download and Configure the Runtime.
FetchContent_MakeAvailable(antlr4_runtime)

### --- C++23 MSVC Missing Include Workaround ---
# MSVC cleaned up transitive includes in C++23.
# We force-include <chrono> into BOTH ANTLR targets to fix it without editing their source.
if (MSVC)
    if (TARGET antlr4_static)
        target_compile_options(antlr4_static PRIVATE /FI"chrono")
    endif()
    if (TARGET antlr4_shared)
        target_compile_options(antlr4_shared PRIVATE /FI"chrono")
    endif()
endif()

### Define the Expected Outputs from ANTLR.
set(GENERATED_SOURCES
    "${GENERATED_DIR}/ExprLexer.cpp"
    "${GENERATED_DIR}/ExprParser.cpp"
)
set(GENERATED_HEADERS
    "${GENERATED_DIR}/ExprLexer.h"
    "${GENERATED_DIR}/ExprParser.h"
    "${GENERATED_DIR}/ExprBaseVisitor.h"
    "${GENERATED_DIR}/ExprVisitor.h"
)

### The Pre-Build Step: Generate C++ from the Grammar.
add_custom_command(
    OUTPUT ${GENERATED_SOURCES} ${GENERATED_HEADERS}
    COMMAND ${Java_JAVA_EXECUTABLE} -jar ${ANTLR_JAR} -Dlanguage=Cpp -visitor -no-listener -o ${GENERATED_DIR} ${GRAMMAR_LEXER} ${GRAMMAR_PARSER}
    DEPENDS ${GRAMMAR_LEXER} ${GRAMMAR_PARSER}
    COMMENT "Generating split C++ lexer and parser..."
)

### Hand-written Source and Header Files.
set(APP_HEADERS
    src/Ast/AddNode.h
	src/Ast/AssignNode.h
    src/Ast/AstArena.h
    src/Ast/AstNode.h
	src/Ast/BitAndNode.h
	src/Ast/BitNotNode.h
	src/Ast/BitOrNode.h
	src/Ast/BitXorNode.h
    src/Ast/ConstantNode.h
	src/Ast/DivNode.h
	src/Ast/EqNode.h
	src/Ast/FunctionCallNode.h
	src/Ast/GeNode.h
	src/Ast/GtNode.h
	src/Ast/LeNode.h
	src/Ast/LogAndNode.h
	src/Ast/LogNotNode.h
	src/Ast/LogOrNode.h
	src/Ast/LtNode.h
	src/Ast/ModNode.h
	src/Ast/MulNode.h
	src/Ast/NeNode.h
	src/Ast/PostDecNode.h
	src/Ast/PostIncNode.h
	src/Ast/PreDecNode.h
	src/Ast/PreIncNode.h
	src/Ast/SequenceNode.h
	src/Ast/ShlNode.h
	src/Ast/ShrNode.h
	src/Ast/SpaceshipNode.h
	src/Ast/SubNode.h
	src/Ast/TernaryNode.h
	src/Ast/UnaryMinusNode.h
	src/Ast/UnaryPlusNode.h
	src/Ast/VarNode.h
    src/Compiler/AstBuilderVisitor.h
	src/Foundation/Character.h
	src/Foundation/Html.h
	src/Foundation/LargeMath.h
	src/Foundation/Math.h
	src/Foundation/System.h
	src/Foundation/Text.h
	src/Foundation/TextPolicy.h
    src/Engine/Errors.h
    src/Engine/ExecutionContext.h
	src/Engine/FunctionDef.h
	src/Engine/IntrinsicBridges.h
	src/Engine/Object.h
	src/Engine/Result.h
	src/Engine/String.h
	src/Strings/Strings.h
	src/Strings/StringEnum.inl
)

set(APP_SOURCES
	src/Engine/ExecutionContext.cpp
	src/Engine/String.cpp
	src/Foundation/Html.cpp
	src/Foundation/Text.cpp
    src/main.cpp
)

### Force Visual Studio to Mirror the Physical Folder Structure (SIGH!!!)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Header Files" FILES ${APP_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${APP_SOURCES})
source_group("Header Files\\Generated" FILES ${GENERATED_HEADERS})
source_group("Source Files\\Generated" FILES ${GENERATED_SOURCES})

### Create the Executable.
add_executable(VEXpression ${APP_SOURCES} ${APP_HEADERS} ${GENERATED_SOURCES} ${GENERATED_HEADERS})

### Include Directories.
target_include_directories(VEXpression PRIVATE
    src
    ${GENERATED_DIR}
)

### Strictly Enforce C++23 on the Executable.
target_compile_features(VEXpression PRIVATE cxx_std_23)

### Link the ANTLR Runtime.
target_link_libraries(VEXpression PRIVATE antlr4_static)

### Link macOS frameworks for Power & Display Management
if(APPLE)
    target_link_libraries(VEXpression PRIVATE "-framework CoreFoundation -framework IOKit")
endif()
