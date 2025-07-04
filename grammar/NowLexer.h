
// Generated from ./NowLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  NowLexer : public antlr4::Lexer {
public:
  enum {
    NUMBER = 1, IDENTIFIER = 2, FUNC = 3, EVENT = 4, WHEN = 5, EVERY = 6, 
    AFTER = 7, WAIT = 8, ON = 9, IF = 10, WHILE = 11, BREAK = 12, RETURN = 13, 
    INT = 14, FLOAT = 15, CHAR = 16, STRING = 17, MS = 18, SEC = 19, MIN = 20, 
    HR = 21, PLUS = 22, MINUS = 23, MUL = 24, DIV = 25, LPAREN = 26, RPAREN = 27, 
    COMMNET = 28, NEWLINE = 29, WS = 30
  };

  explicit NowLexer(antlr4::CharStream *input);

  ~NowLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

