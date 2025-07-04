
// Generated from ./NowParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "NowParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by NowParser.
 */
class  NowParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by NowParser.
   */
    virtual std::any visitProg(NowParser::ProgContext *context) = 0;

    virtual std::any visitExpr(NowParser::ExprContext *context) = 0;

    virtual std::any visitTimeStamp(NowParser::TimeStampContext *context) = 0;


};

