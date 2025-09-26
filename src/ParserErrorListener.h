#include "antlr4-runtime.h"

class ParserErrorListener : public antlr4::BaseErrorListener {
public:
   void syntaxError(antlr4::Recognizer *recognizer,
                     antlr4::Token *offendingSymbol,
                     size_t line,
                     size_t charPositionInLine,
                     const std::string &msg,
                     std::exception_ptr e) override {
        std::cerr << "Syntax error in line "
                  << line << ":" << charPositionInLine
                  << " near "
                  << (offendingSymbol ? offendingSymbol->getText() : "<EOF>")
                  << " -> " << msg << std::endl;
    }
};