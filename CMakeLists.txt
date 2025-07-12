cmake_minimum_required(VERSION 3.10)
project(NowCompiler)

set(CMAKE_CXX_STANDARD 17)

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
    grammar/NowLexer.cpp
    grammar/NowParser.cpp
)

# Vincular con antlr4-runtime
target_link_libraries(NowCompiler antlr4-runtime)

# LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

target_link_libraries(NowCompiler
        antlr4-runtime
        LLVMCore
        LLVMSupport
)

# Unit tests
enable_testing()

# Buscar todos los archivos .cpp en la carpeta tests
file(GLOB TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/tests/*.cpp
)

set(GRAMMAR_SOURCES
    ${PROJECT_SOURCE_DIR}/grammar/NowLexer.cpp
    ${PROJECT_SOURCE_DIR}/grammar/NowParser.cpp
)


# Los añade como ejecutables
add_executable(NowTests ${TEST_SOURCES} ${GRAMMAR_SOURCES})

# Incluir headers del proyecto en los tests
target_include_directories(NowTests PRIVATE
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

# Enlazar con GTest y tu librería
target_link_libraries(NowTests
    gtest
    gtest_main
    antlr4-runtime
    LLVMCore
    LLVMSupport
)

# Agregar las pruebas
add_test(NAME NowCompilerStmtTest COMMAND NowTests)
