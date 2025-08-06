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
	std::unique_ptr<ASTNode> visitExpr(NowParser::ExprContext* ctx);
	
	std::unique_ptr<ASTNode> visitOpLiteral(NowParser::OpLiteralContext* ctx);
    std::unique_ptr<ASTNode> visitOpIdentifier(NowParser::OpIdentifierContext* ctx);
    
    std::unique_ptr<ASTNode> visitConditional(NowParser::ConditionalContext* ctx);
    std::unique_ptr<ASTNode> visitTimeBlock(NowParser::TimeBlockContext* ctx);
    std::unique_ptr<ASTNode> visitComparison(NowParser::ComparisonContext* ctx);
	std::unique_ptr<ASTNode> visitDeclaration(NowParser::DeclarationContext* ctx);
    
    std::unique_ptr<ASTNode> visitAddSubExpr(NowParser::AddSubExprContext* ctx);
    std::unique_ptr<ASTNode> visitMulDivExpr(NowParser::MulDivExprContext* ctx);
    std::unique_ptr<ASTNode> visitNumExpr(NowParser::NumExprContext* ctx);
    std::unique_ptr<ASTNode> visitParenExpr(NowParser::ParenExprContext* ctx);

    std::unique_ptr<ASTNode> visitFunction(NowParser::FuncDeclarationContext* ctx);
    std::vector<std::unique_ptr<DeclarationNode>> visitParams(NowParser::ParamListContext* ctx);

    std::unique_ptr<ASTNode> visitStmt(NowParser::StmtContext* stmtCtx);
    std::vector<std::unique_ptr<ASTNode>> visitStmtList(const std::vector<NowParser::StmtContext*>& stmts);
};
