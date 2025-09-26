/* Compiler file */
#include <iostream>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"
#include "ios"
#include "ASTBuilderVisitor.h"
#include "LexerErrorListener.h"
#include "ParserErrorListener.h"

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

	/* Compilation pocess */

	// Lexical analysis
	ANTLRInputStream input(fileText);
	NowLexer lexer(&input);

	lexer.removeErrorListeners();
	lexer.addErrorListener(new LexerErrorListener()); // Adding a modified error listener

	CommonTokenStream tokens(&lexer);

	tokens.fill();
	for (auto token : tokens.getTokens()) {
	    std::cout << token->toString() << std::endl;
	}	
	
	// Parsing process
	NowParser parser(&tokens);

	parser.removeErrorListeners();
	parser.addErrorListener(new ParserErrorListener()); // Adding a modified error listener

	NowParser::ProgramContext* tree = parser.program();

	// AST building process
	ASTBuilderVisitor builder;
	std::vector<std::unique_ptr<ASTNode>> nodes = builder.buildTree(tree);

	// TODO SemanticVisitor semanticVisitor
	
	return 0;
}
