/*
Main file

*/


#include <iostream>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"

using namespace antlr4;

int main(){
	ANTLRInputStream input("2ms\n");
	NowLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	NowParser parser(&tokens);
	tree::ParseTree *tree = parser.prog();

	std::cout << tree->toStringTree(&parser) << std::endl;
	return 0;
}
