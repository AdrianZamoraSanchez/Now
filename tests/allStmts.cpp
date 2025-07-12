/* Tests for general statements */
#include <iostream>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"
#include "ios"
#include <list>
#include <gtest/gtest.h>

using namespace antlr4;

void runTests(std::string fileName){
	std::string line;
	std::string fileText = "";
	std::string expectedOutput = "";

	std::string inputFileName = "/home/adrian/Now/tests/input/" + fileName + ".now";
	std::string outputFileName = "/home/adrian/Now/tests/output/" + fileName + ".out";

    std::ifstream inputFile (inputFileName);
    std::ifstream outputFile (outputFileName);

	// Input text
    if (inputFile.is_open()) {
    	while (getline (inputFile,line)) {
    		fileText += line + '\n';
      	}

      	inputFile.close();
    }
    else {
    	std::cout << "Unable to open " << inputFileName << " file" << std::endl;
        return;
    }
    
    line = "";

	// Expected final output
    if (outputFile.is_open()) {
    	while (getline (outputFile,line)) {
    		expectedOutput += line;
    	}

    	outputFile.close();
    }
    else {
	    std::cout << "Unable to open " << outputFileName << " file" << std::endl;
	    return;
    }

	/*
    std::cout << "Text being analyzed" << std::endl;
    std::cout << fileText << std::endl;
	*/
	
    ANTLRInputStream input(fileText);
    NowLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

	/*
    for (auto token : tokens.getTokens()) {
    	std::cout << token->toString() << std::endl;
    }
    */

    NowParser parser(&tokens);

    NowParser::ProgContext* tree = parser.prog();

    std::string actualOutput = tree->toStringTree(&parser);

   	ASSERT_EQ(actualOutput, expectedOutput);	
}

TEST(NowCompilerStmtTest, ifStmt){
    	runTests("ifStmt");
    }
