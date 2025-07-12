/* Tests for general statements */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <gtest/gtest.h>
#include "antlr4-runtime.h"
#include "NowLexer.h"
#include "NowParser.h"

using namespace antlr4;

class MyErrorListener : public BaseErrorListener {
public:
    bool errorFound = false;

    void syntaxError(Recognizer *recognizer,
                     Token *offendingSymbol,
                     size_t line,
                     size_t charPositionInLine,
                     const std::string &msg,
                     std::exception_ptr e) override {
        errorFound = true;
    }

    bool hasErrors() const {
        return errorFound;
    }
};

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
    parser.removeErrorListeners(); // Remove default error listener

	// Adding simple error listener
    MyErrorListener errorListener;
    parser.addErrorListener(&errorListener);

    NowParser::ProgramContext* tree = parser.program();

    std::string actualOutput = tree->toStringTree(&parser);

   	ASSERT_EQ(actualOutput, expectedOutput);
   	ASSERT_FALSE(errorListener.hasErrors());	
}

TEST(NowCompilerStmtTest, timeBlockStmt){ runTests("timeBlockStmt"); }

TEST(NowCompilerStmtTest, assignStmt){ runTests("assignStmt"); }

TEST(NowCompilerStmtTest, declarationStmt){ runTests("declarationStmt"); }

TEST(NowCompilerStmtTest, ifStmt){ runTests("ifStmt"); }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
