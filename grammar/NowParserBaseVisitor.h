
// Generated from ./NowParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "NowParserVisitor.h"


/**
 * This class provides an empty implementation of NowParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  NowParserBaseVisitor : public NowParserVisitor {
public:

  virtual std::any visitProg(NowParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(NowParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTimeStamp(NowParser::TimeStampContext *ctx) override {
    return visitChildren(ctx);
  }


};

