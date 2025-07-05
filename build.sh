# Lexer + Parser generation
cd ./grammar/
java -Xmx500M -cp "$HOME/tools/antlr/antlr-4.13.1-complete.jar" org.antlr.v4.Tool -visitor -Dlanguage=Cpp ~/nodeAsk/grammar/nodeAsk.g4
cd ..

# main.cpp compilation
cd ./build/
cmake ..
make

# Test
./NowCompiler
cd ..
