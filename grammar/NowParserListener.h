
// Generated from ./NowParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "NowParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by NowParser.
 */
class  NowParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(NowParser::ProgContext *ctx) = 0;
  virtual void exitProg(NowParser::ProgContext *ctx) = 0;

  virtual void enterExpr(NowParser::ExprContext *ctx) = 0;
  virtual void exitExpr(NowParser::ExprContext *ctx) = 0;

  virtual void enterTimeStamp(NowParser::TimeStampContext *ctx) = 0;
  virtual void exitTimeStamp(NowParser::TimeStampContext *ctx) = 0;


};

