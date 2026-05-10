cmake_minimum_required(VERSION 3.15)
project(VEXpression CXX)

### Build Options.
option(VEXPRESSION_BUILD_UI "Build the standalone interactive UI executable" ON)

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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    enable_language(ASM_MASM)
else()
    enable_language(ASM)
endif()

### Global Compile Definitions.
add_compile_definitions(_USE_MATH_DEFINES SIMDE_NO_NATIVE SIMDE_NO_CHECK_IMMEDIATE_CONSTANT VE_HTML_ESCAPES VE_NAMED_ESCAPES VE_FULL_STRINGS)

### Locate the Java Runtime.
find_package(Java 11 COMPONENTS Runtime REQUIRED)

### Locate Iconv (Required for macOS, often built-in on Linux).
if(NOT WIN32)
    find_package(Iconv REQUIRED)
endif()

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
set(WITH_STATIC_CRT ON CACHE BOOL "" FORCE) 
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

### Tell CMake where to get the Core dependencies (Bypassing Git)
FetchContent_Declare(
    antlr4_runtime
    URL            https://github.com/antlr/antlr4/archive/refs/tags/4.13.2.zip
    SOURCE_SUBDIR  runtime/Cpp
)

FetchContent_Declare(
    simde
    URL            https://github.com/simd-everywhere/simde/archive/refs/tags/v0.7.6.zip
)

### Actually Download and Configure the Core Runtimes.
FetchContent_MakeAvailable(antlr4_runtime simde)

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
    src/Ast/AddAssignNode.h
    src/Ast/AddNode.h
    src/Ast/ArrayAccessExNode.h
    src/Ast/ArrayAccessNode.h
    src/Ast/ArrayAssignNode.h
    src/Ast/ArrayExAssignNode.h
    src/Ast/AssignNode.h
    src/Ast/AstArena.h
    src/Ast/AstNode.h
    src/Ast/BitAndAssignNode.h
    src/Ast/BitAndNode.h
    src/Ast/BitNotNode.h
    src/Ast/BitOrAssignNode.h
    src/Ast/BitOrNode.h
    src/Ast/BitXorAssignNode.h
    src/Ast/BitXorNode.h
    src/Ast/BreakNode.h
    src/Ast/CastNode.h
    src/Ast/ConstantNode.h
    src/Ast/ConstructPrimitiveNode.h
    src/Ast/ConstructSimdNode.h
    src/Ast/ContinueNode.h
    src/Ast/DivAssignNode.h
    src/Ast/DivNode.h
	src/Ast/DoWhileNode.h
    src/Ast/EqNode.h
	src/Ast/FlatVectorNode.h
    src/Ast/ForNode.h
    src/Ast/ForRangeNode.h
    src/Ast/FunctionCallNode.h
    src/Ast/GeNode.h
    src/Ast/GtNode.h
    src/Ast/IfNode.h
    src/Ast/LeNode.h
    src/Ast/LogAndNode.h
    src/Ast/LogNotNode.h
    src/Ast/LogOrNode.h
    src/Ast/LtNode.h
    src/Ast/MapNode.h
    src/Ast/MethodCallNode.h
    src/Ast/ModAssignNode.h
    src/Ast/ModNode.h
    src/Ast/MulAssignNode.h
    src/Ast/MulNode.h
    src/Ast/NeNode.h
    src/Ast/ParamAccessNode.h
    src/Ast/PostDecNode.h
    src/Ast/PostIncNode.h
    src/Ast/PreDecNode.h
    src/Ast/PreIncNode.h
    src/Ast/ReturnNode.h
	src/Ast/ScopeNode.h
    src/Ast/SequenceNode.h
    src/Ast/ShlAssignNode.h
    src/Ast/ShlNode.h
    src/Ast/ShrAssignNode.h
    src/Ast/ShrNode.h
    src/Ast/SpaceshipNode.h
    src/Ast/SubAssignNode.h
    src/Ast/SubNode.h
    src/Ast/TernaryNode.h
    src/Ast/TotalParmsNode.h
    src/Ast/UnaryMinusNode.h
    src/Ast/UnaryPlusNode.h
    src/Ast/UserValueNode.h
    src/Ast/VarNode.h
    src/Ast/VectorNode.h
	src/Ast/WhileNode.h
    src/Compiler/AstBuilderVisitor.h
    src/Foundation/Case.h
    src/Foundation/Character.h
    src/Foundation/Encode.h
    src/Foundation/EncodeEnum.inl
    src/Foundation/Html.h
    src/Foundation/LargeMath.h
    src/Foundation/Math.h
    src/Foundation/SinCos.h
    src/Foundation/System.h
    src/Foundation/Text.h
    src/Foundation/TextPolicy.h
    src/Foundation/Unicode.h
    src/Foundation/UnicodeData.inl
    src/Engine/BFloat16.h
    src/Engine/Errors.h
    src/Engine/ExecutionContext.h
    src/Engine/Float16.h
    src/Engine/FunctionDef.h
    src/Engine/IntrinsicBridges.h
    src/Engine/Map.h
    src/Engine/Object.h
    src/Engine/Result.h
    src/Engine/SimdBridges.h
    src/Engine/SimdBridgeTable.inl
    src/Engine/SimdIncludes.h
    src/Engine/SimdObject.h
    src/Engine/String.h
    src/Engine/Vector.h
    src/OS/OS.h
    src/Strings/Strings.h
    src/Strings/StringEnum.inl
    src/Strings/SimdDescriptions.inl
	src/SIMDeX/mips/asub.h
	src/SIMDeX/mips/ave.h
	src/SIMDeX/mips/aver.h
	src/SIMDeX/mips/bclr.h
	src/SIMDeX/mips/bclri.h
	src/SIMDeX/mips/binsl.h
	src/SIMDeX/mips/binsli.h
	src/SIMDeX/mips/binsr.h
	src/SIMDeX/mips/binsri.h
	src/SIMDeX/mips/bmnz_v.h
	src/SIMDeX/mips/bmnzi.h
	src/SIMDeX/mips/bmz_v.h
	src/SIMDeX/mips/bmzi.h
	src/SIMDeX/mips/bneg.h
	src/SIMDeX/mips/bnegi.h
	src/SIMDeX/mips/bsel_v.h
	src/SIMDeX/mips/bseli.h
	src/SIMDeX/mips/bset.h
	src/SIMDeX/mips/bseti.h
	src/SIMDeX/mips/cast_to_scalar_double.h
	src/SIMDeX/mips/cast_to_scalar_float.h
	src/SIMDeX/mips/cast_to_vector_double.h
	src/SIMDeX/mips/cast_to_vector_float.h
	src/SIMDeX/mips/ceq.h
	src/SIMDeX/mips/ceqi.h
	src/SIMDeX/mips/cfcmsa.h
	src/SIMDeX/mips/cle.h
	src/SIMDeX/mips/clei.h
	src/SIMDeX/mips/clt.h
	src/SIMDeX/mips/clti.h
	src/SIMDeX/mips/copy.h
	src/SIMDeX/mips/div.h
	src/SIMDeX/mips/dotp.h
	src/SIMDeX/mips/dpadd.h
	src/SIMDeX/mips/dpsub.h
	src/SIMDeX/mips/fadd.h
	src/SIMDeX/mips/fcaf.h
	src/SIMDeX/mips/fceq.h
	src/SIMDeX/mips/fclass.h
	src/SIMDeX/mips/fcle.h
	src/SIMDeX/mips/fclt.h
	src/SIMDeX/mips/fcne.h
	src/SIMDeX/mips/fcor.h
	src/SIMDeX/mips/fcueq.h
	src/SIMDeX/mips/fcule.h
	src/SIMDeX/mips/fcult.h
	src/SIMDeX/mips/fcun.h
	src/SIMDeX/mips/fcune.h
	src/SIMDeX/mips/fdiv.h
	src/SIMDeX/mips/fexdo.h
	src/SIMDeX/mips/fexp2.h
	src/SIMDeX/mips/fexupl.h
	src/SIMDeX/mips/fexupr.h
	src/SIMDeX/mips/ffint.h
	src/SIMDeX/mips/ffql.h
	src/SIMDeX/mips/ffqr.h
	src/SIMDeX/mips/fill.h
	src/SIMDeX/mips/flog2.h
	src/SIMDeX/mips/fmax.h
	src/SIMDeX/mips/fmax_a.h
	src/SIMDeX/mips/fmin.h
	src/SIMDeX/mips/fmin_a.h
	src/SIMDeX/mips/fmsub.h
	src/SIMDeX/mips/fmul.h
	src/SIMDeX/mips/frcp.h
	src/SIMDeX/mips/frint.h
	src/SIMDeX/mips/frsqrt.h
	src/SIMDeX/mips/fsaf.h
	src/SIMDeX/mips/fseq.h
	src/SIMDeX/mips/fsle.h
	src/SIMDeX/mips/fslt.h
	src/SIMDeX/mips/fsne.h
	src/SIMDeX/mips/fsor.h
	src/SIMDeX/mips/fsqrt.h
	src/SIMDeX/mips/fsub.h
	src/SIMDeX/mips/fsueq.h
	src/SIMDeX/mips/fsule.h
	src/SIMDeX/mips/fsult.h
	src/SIMDeX/mips/fsun.h
	src/SIMDeX/mips/fsune.h
	src/SIMDeX/mips/ftint.h
	src/SIMDeX/mips/ftq.h
	src/SIMDeX/mips/ftrunc.h
	src/SIMDeX/mips/hadd.h
	src/SIMDeX/mips/hsub.h
	src/SIMDeX/mips/ilvev.h
	src/SIMDeX/mips/ilvl.h
	src/SIMDeX/mips/ilvod.h
	src/SIMDeX/mips/ilvr.h
	src/SIMDeX/mips/insert.h
	src/SIMDeX/mips/insve.h
	src/SIMDeX/mips/ldi.h
	src/SIMDeX/mips/madd_q.h
	src/SIMDeX/mips/maddr_q.h
	src/SIMDeX/mips/maddv.h
	src/SIMDeX/mips/max.h
	src/SIMDeX/mips/max_a.h
	src/SIMDeX/mips/maxi.h
	src/SIMDeX/mips/min.h
	src/SIMDeX/mips/min_a.h
	src/SIMDeX/mips/mini.h
	src/SIMDeX/mips/mod.h
	src/SIMDeX/mips/move_v.h
	src/SIMDeX/mips/msub_q.h
	src/SIMDeX/mips/msubr_q.h
	src/SIMDeX/mips/msubv.h
	src/SIMDeX/mips/mul_q.h
	src/SIMDeX/mips/mulr_q.h
	src/SIMDeX/mips/mulv.h
	src/SIMDeX/mips/nloc.h
	src/SIMDeX/mips/nlzc.h
	src/SIMDeX/mips/nor_v.h
	src/SIMDeX/mips/nori.h
	src/SIMDeX/mips/or_v.h
	src/SIMDeX/mips/ori.h
	src/SIMDeX/mips/pckev.h
	src/SIMDeX/mips/pckod.h
	src/SIMDeX/mips/pcnt.h
	src/SIMDeX/mips/sat.h
	src/SIMDeX/mips/shf.h
	src/SIMDeX/mips/sld.h
	src/SIMDeX/mips/sldi.h
	src/SIMDeX/mips/sll.h
	src/SIMDeX/mips/slli.h
	src/SIMDeX/mips/splat.h
	src/SIMDeX/mips/splati.h
	src/SIMDeX/mips/sra.h
	src/SIMDeX/mips/srai.h
	src/SIMDeX/mips/srar.h
	src/SIMDeX/mips/srari.h
	src/SIMDeX/mips/srl.h
	src/SIMDeX/mips/srli.h
	src/SIMDeX/mips/srlr.h
	src/SIMDeX/mips/srlri.h
	src/SIMDeX/mips/subs.h
	src/SIMDeX/mips/subsus.h
	src/SIMDeX/mips/subsuu.h
	src/SIMDeX/mips/subvi.h
	src/SIMDeX/mips/test_bnz.h
	src/SIMDeX/mips/test_bnz_v.h
	src/SIMDeX/mips/test_bz.h
	src/SIMDeX/mips/test_bz_v.h
	src/SIMDeX/mips/vshf.h
	src/SIMDeX/mips/xor_v.h
	src/SIMDeX/mips/xori.h
)

set(CORE_SOURCES
    src/Engine/ExecutionContext.cpp
    src/Engine/Map.cpp
    src/Engine/SimdObject.cpp
    src/Engine/String.cpp
    src/Engine/Vector.cpp
    src/Foundation/Case.cpp
    src/Foundation/Character.cpp
    src/Foundation/Encode.cpp
    src/Foundation/Html.cpp
    src/Foundation/Text.cpp
    src/Foundation/Unicode.cpp
)

if(WIN32)
    list(APPEND CORE_SOURCES src/Foundation/SinCos.asm)
endif()

### Force Visual Studio to Mirror the Physical Folder Structure
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Header Files" FILES ${APP_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${CORE_SOURCES})
source_group("Header Files\\Generated" FILES ${GENERATED_HEADERS})
source_group("Source Files\\Generated" FILES ${GENERATED_SOURCES})

### Create the Static Library.
add_library(VEXpressionCore STATIC ${CORE_SOURCES} ${APP_HEADERS} ${GENERATED_SOURCES} ${GENERATED_HEADERS})

### Apply MSVC Runtime Settings to Core (Static Runtime /MT)
if(MSVC)
    set_property(TARGET VEXpressionCore PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

### Include Directories (PUBLIC so dependents inherit them automatically).
target_include_directories(VEXpressionCore PUBLIC
    src
    ${GENERATED_DIR}
    ${simde_SOURCE_DIR}
)

### Strictly Enforce C++20 on Core.
target_compile_features(VEXpressionCore PUBLIC cxx_std_20)

### Link the Core Dependencies.
target_link_libraries(VEXpressionCore PUBLIC antlr4_static)
if(NOT WIN32)
    target_link_libraries(VEXpressionCore PUBLIC Iconv::Iconv)
endif()
if(APPLE)
    target_link_libraries(VEXpressionCore PUBLIC "-framework CoreFoundation -framework IOKit")
endif()


### =========================================================================
### OPTIONAL UI BUILD (wxWidgets)
### =========================================================================
if(VEXPRESSION_BUILD_UI)
    message(STATUS "VEXPRESSION_BUILD_UI is ON. Building cross-platform wxWidgets UI...")

    # 1. Find wxWidgets on the host OS.
    #    Requires wxWidgets to be installed via vcpkg (Win), Homebrew (Mac), or APT (Linux).
    if(WIN32)
        set(wxWidgets_USE_STATIC ON)
        # Fix for vcpkg: CMake looks for 'vc_x64_lib'. vcpkg uses 'lib'. 
        if(DEFINED VCPKG_INSTALLED_DIR)
            set(wxWidgets_ROOT_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
            set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib")
        endif()
    endif()
    
    find_package(wxWidgets REQUIRED COMPONENTS core base stc aui)
    include(${wxWidgets_USE_FILE})

    # 2. UI Sources.
    set(UI_HEADERS
        src/UI/MainApp.h
        src/UI/MainFrame.h
    )
    set(UI_SOURCES
        src/main.cpp
        src/UI/MainApp.cpp
        src/UI/MainFrame.cpp
    )

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Header Files" FILES ${UI_HEADERS})
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${UI_SOURCES})

    # 3. Create the Executable based on the target OS.
    if(WIN32)
        add_executable(VEXpression WIN32 ${UI_SOURCES} ${UI_HEADERS})
        # Tell wxWidgets we are on Windows (__WXMSW__) so it generates WinMain/wWinMain
        target_compile_definitions(VEXpression PRIVATE __WXMSW__ UNICODE _UNICODE)
    elseif(APPLE)
        add_executable(VEXpression MACOSX_BUNDLE ${UI_SOURCES} ${UI_HEADERS})
    else()
        add_executable(VEXpression ${UI_SOURCES} ${UI_HEADERS})
    endif()

    target_compile_features(VEXpression PRIVATE cxx_std_20)

    # Apply MSVC Runtime Settings to the UI Executable (Static Runtime /MT).
    if(MSVC)
        set_property(TARGET VEXpression PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()

    # 4. Link the Core Library and the OS-specific wxWidgets libraries.
    target_link_libraries(VEXpression PRIVATE VEXpressionCore ${wxWidgets_LIBRARIES})
    
    # Manually resolve vcpkg STC static dependencies on Windows for BOTH configurations.
    if(WIN32)
        find_library(LEXILLA_LIB_RELEASE NAMES lexilla wxlexilla)
        find_library(LEXILLA_LIB_DEBUG NAMES lexillad wxlexillad)
        
        find_library(SCINTILLA_LIB_RELEASE NAMES scintilla wxscintilla)
        find_library(SCINTILLA_LIB_DEBUG NAMES scintillad wxscintillad)
        
        # Link the correct library based on the current Visual Studio build configuration.
        target_link_libraries(VEXpression PRIVATE 
            optimized ${LEXILLA_LIB_RELEASE} debug ${LEXILLA_LIB_DEBUG}
            optimized ${SCINTILLA_LIB_RELEASE} debug ${SCINTILLA_LIB_DEBUG}
            rpcrt4
        )
    endif()
    
endif()
