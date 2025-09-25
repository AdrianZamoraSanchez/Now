/* Compiler file */
#include <iostream>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"
#include "ios"
#include "ASTBuilderVisitor.h"

using namespace antlr4;

int main(int argc, char *argv[]){
	std::string line;
	std::string fileText = "";

	std::ifstream testFile(argv[1]);

	// File check
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

	// File view
	std::cout << "Text being analyzed" << std::endl;
	std::cout << fileText << std::endl;

	// Compilation pocess
	ANTLRInputStream input(fileText);
	NowLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	tokens.fill();
	for (auto token : tokens.getTokens()) {
	    std::cout << token->toString() << std::endl;
	}	
	
	// Extraction of the program context
	NowParser parser(&tokens);
	NowParser::ProgramContext* tree = parser.program();

	// AST building process
	ASTBuilderVisitor builder;
	
	std::vector<std::unique_ptr<ASTNode>> nodes = builder.buildTree(tree);

	// TODO SemanticVisitor semanticVisitor
	
	return 0;
}
