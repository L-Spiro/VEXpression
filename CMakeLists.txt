cmake_minimum_required(VERSION 3.15)
project(VEXpression CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    src/Ast/AstArena.h
    src/Ast/AstNode.h
    src/Ast/ConstantNode.h
    src/Compiler/AstBuilderVisitor.h
    src/Engine/Errors.h
    src/Engine/ExecutionContext.h
	src/Engine/Result.h
)

set(APP_SOURCES
	src/Engine/ExecutionContext.cpp
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
