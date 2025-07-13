/*
Main file
*/


#include <iostream>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"
#include "ios"
#include "ASTBuilderVisitor.cpp"

using namespace antlr4;

int main(int argc, char *argv[]){
	std::string line;
	std::string fileText = "";

	std::ifstream testFile(argv[1]);

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

	tokens.fill();
	for (auto token : tokens.getTokens()) {
	    std::cout << token->toString() << std::endl;
	}	

	NowParser parser(&tokens);
	
	NowParser::ProgramContext* tree = parser.program();

	std::cout << tree->toStringTree(&parser) << std::endl;
	
	return 0;
}
