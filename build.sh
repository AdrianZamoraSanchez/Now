# Lexer + Parser generation
cd ./grammar/
rm *.tokens *.cpp *.h
java -Xmx500M -cp "$HOME/tools/antlr/antlr-4.13.1-complete.jar" org.antlr.v4.Tool -Dlanguage=Cpp NowLexer.g4
java -Xmx500M -cp "$HOME/tools/antlr/antlr-4.13.1-complete.jar" org.antlr.v4.Tool -visitor -Dlanguage=Cpp NowParser.g4
cd ..

# main.cpp compilation
cd ./build/
rm *.*
cmake ..
make

#clear

# Tests
ctest
cd ..

