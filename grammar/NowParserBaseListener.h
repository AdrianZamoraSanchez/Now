
// Generated from ./NowParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "NowParserListener.h"


/**
 * This class provides an empty implementation of NowParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  NowParserBaseListener : public NowParserListener {
public:

  virtual void enterProg(NowParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(NowParser::ProgContext * /*ctx*/) override { }

  virtual void enterExpr(NowParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(NowParser::ExprContext * /*ctx*/) override { }

  virtual void enterTimeStamp(NowParser::TimeStampContext * /*ctx*/) override { }
  virtual void exitTimeStamp(NowParser::TimeStampContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

