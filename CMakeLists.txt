cmake_minimum_required(VERSION 3.10)
project(NowCompiler)

set(CMAKE_CXX_STANDARD 17)

# -------------------
# Compiler

# Incluir directorios de encabezados
include_directories(
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

# Buscar la librería del runtime
link_directories(/usr/local/lib)

# Archivos fuente
add_executable(NowCompiler
    src/main.cpp
    src/ASTBuilderVisitor.cpp
    src/Type.cpp
    src/Scope.cpp
    src/SemanticVisitor.cpp
    grammar/NowLexer.cpp
    grammar/NowParser.cpp
)

# Vincular con antlr4-runtime
target_link_libraries(NowCompiler antlr4-runtime)


# -------------------
# LLVM
find_package(LLVM REQUIRED CONFIG)

#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

target_link_libraries(NowCompiler
        antlr4-runtime
        LLVMCore
        LLVMSupport
)

# Fuentes principales de la app
set(SRC_SOURCES
	${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/ASTBuilderVisitor.cpp
    ${PROJECT_SOURCE_DIR}/src/Type.cpp
    ${PROJECT_SOURCE_DIR}/grammar/NowLexer.cpp
    ${PROJECT_SOURCE_DIR}/grammar/NowParser.cpp
)

# Ejecutable principal
add_executable(NowApp ${SRC_SOURCES})

target_include_directories(NowApp PRIVATE
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

target_link_libraries(NowApp
    antlr4-runtime
    LLVMCore
    LLVMSupport
)

# -------------------
# Tests

enable_testing()

# Archivos fuente comunes
set(GRAMMAR_SOURCES
    ${PROJECT_SOURCE_DIR}/grammar/NowLexer.cpp
    ${PROJECT_SOURCE_DIR}/grammar/NowParser.cpp
)

set(SRC_SOURCES
    ${PROJECT_SOURCE_DIR}/src/ASTBuilderVisitor.cpp
	${PROJECT_SOURCE_DIR}/src/Type.cpp
)

# Crear librería con la lógica del compilador
add_library(now STATIC
    ${SRC_SOURCES}
    ${GRAMMAR_SOURCES}
)

target_include_directories(now PUBLIC
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

target_link_libraries(now
    antlr4-runtime
    LLVMCore
    LLVMSupport
)

# -------------------------------------
# Test manual (no usa GoogleTest): AST.cpp

add_executable(NowRun_AST ${PROJECT_SOURCE_DIR}/tests/ASTtest.cpp)

target_link_libraries(NowRun_AST
    now
    antlr4-runtime
    LLVMCore
    LLVMSupport
)

target_include_directories(NowRun_AST PRIVATE
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

# -------------------------------------
# Tests automatizados con GTest

# Buscar todos los tests que sí usan GoogleTest (por ejemplo: allStmts.cpp)
# Podés refinar este patrón si luego querés separar con sufijos como *_Test.cpp
file(GLOB GTEST_SOURCES
    ${PROJECT_SOURCE_DIR}/tests/allStmts.cpp
    # Otros archivos con TEST() si los hay
)

add_executable(NowTests ${GTEST_SOURCES})

target_include_directories(NowTests PRIVATE
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

target_link_libraries(NowTests
    now
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(NowTests)
