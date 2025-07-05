/*
Main file
*/


#include <iostream>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"
#include "ios"

using namespace antlr4;

int main(){
	std::string line;
	std::string fileText = "";

	std::ifstream testFile ("../input.now");

	if (testFile.is_open()) {
	  while (getline (testFile,line)) {
	    fileText += line + '\n';
	  }

	  testFile.close();
	} 
	else {
		std::cout << "Unable to open file" << std::endl;
		return 1;
	} 
	
	std::cout << "Text being analyzed" << std::endl;
	std::cout << fileText << std::endl;

	ANTLRInputStream input(fileText);
	NowLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	NowParser parser(&tokens);
	tree::ParseTree *tree = parser.prog();

	std::cout << tree->toStringTree(&parser) << std::endl;
	return 0;
}
