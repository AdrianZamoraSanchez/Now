#include <iostream>
#include <vector>
#include "../src/ASTBuilderVisitor.cpp"
#include "../grammar/NowParser.h"
#include "../grammar/NowParserBaseVisitor.h"
#include "../grammar/NowLexer.h"

using namespace antlr4;

int main(int argc, char** argv){
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

	NowParser parser(&tokens);
	
	NowParser::ProgramContext* tree = parser.program();

	ASTBuilderVisitor visitor;

	std::vector<std::unique_ptr<ASTNode>> nodes;

    nodes = visitor.buildTree(tree);

    for(const auto& node : nodes){
    	node->printNode();
    }
	
	return 0;
}

