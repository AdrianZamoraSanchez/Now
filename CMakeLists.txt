cmake_minimum_required(VERSION 3.10)
project(CompilerName)

set(CMAKE_CXX_STANDARD 17)

# Directorios de trabajo
include_directories(
    ${PROJECT_SOURCE_DIR}/grammar
    /usr/local/include/antlr4-runtime
)

# Librería del runtime
link_directories(/usr/local/lib)

# Archivos fuente
add_executable(CompilerName
    src/main.cpp
    grammar/LanguageNameLexer.cpp
    grammar/LanguageNameParser.cpp
)

# Vincular con antlr4-runtime
target_link_libraries(CompilerName antlr4-runtime)

