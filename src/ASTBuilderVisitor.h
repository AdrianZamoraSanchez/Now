#pragma once

#include "AST.h"
#include "../grammar/NowParser.h"
#include <memory>

class ASTBuilderVisitor {
public:
	std::vector<std::unique_ptr<ASTNode>> buildTree(NowParser::ProgramContext* ctx);
    std::unique_ptr<ASTNode> visitProgram(NowParser::ProgramContext* ctx);
    std::unique_ptr<ASTNode> visitAssign(NowParser::AssignContext* ctx);
    std::unique_ptr<ASTNode> visitOperand(NowParser::OperandContext* ctx);
    std::unique_ptr<ASTNode> visitConditional(NowParser::ConditionalContext* ctx);
    std::unique_ptr<ASTNode> visitComparison(NowParser::ComparisonContext* ctx);
    std::unique_ptr<ASTNode> visitOpLiteral(NowParser::OpLiteralContext* ctx);
    std::unique_ptr<ASTNode> visitOpIdentifier(NowParser::OpIdentifierContext* ctx);
    std::unique_ptr<ASTNode> visitOpExpr(NowParser::OpExprContext* ctx);
    std::unique_ptr<ASTNode> visitAddSubExpr(NowParser::AddSubExprContext* ctx);
    std::unique_ptr<ASTNode> visitMulDivExpr(NowParser::MulDivExprContext* ctx);
    std::unique_ptr<ASTNode> visitNumExpr(NowParser::NumExprContext* ctx);
    std::unique_ptr<ASTNode> visitParenExpr(NowParser::ParenExprContext* ctx);
};
