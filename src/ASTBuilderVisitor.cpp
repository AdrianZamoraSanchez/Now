#include "AST.h"
#include "ASTBuilderVisitor.h"
#include "../grammar/NowParser.h"
#include "../grammar/NowParserBaseVisitor.h"
#include <memory>
#include <vector>

#include <iostream>

// Root of the AST
std::vector<std::unique_ptr<ASTNode>> ASTBuilderVisitor::buildTree(NowParser::ProgramContext* ctx){

	std::vector<std::unique_ptr<ASTNode>> programNodeList;

	for (auto stmtCtx : ctx->stmt()) {
		if (auto assignStmt = dynamic_cast<NowParser::StmtAssignContext*>(stmtCtx)) {
            std::unique_ptr<ASTNode> node = visitAssign(assignStmt->assign());
			programNodeList.push_back(std::move(node));
            break;
        }
		/*
		if(auto timeBlockCtx = dynamic_cast<NowParser::StmtTimeBlockContext*>(stmtCtx)){
			std::unique_ptr<ASTNode> node = visitAssign(timeBlockCtx);
		}

		if(auto conditionalCtx = dynamic_cast<NowParser::StmtConditionalContext*>(stmtCtx)){
			std::unique_ptr<ASTNode> node = visitAssign(conditionalCtx);	
		}

		if(auto declarationCtx = dynamic_cast<NowParser::StmtDeclarationContext*>(stmtCtx)){
			std::unique_ptr<ASTNode> node = visitAssign(declarationCtx);			
		}*/
    }

    return programNodeList;
}

// Identifier visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitOpIdentifier(NowParser::OpIdentifierContext* ctx) {
    std::string value = ctx->IDENTIFIER()->getText();

    return std::make_unique<IdentifierNode>(value);
}


// Assign visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitAssign(NowParser::AssignContext* ctx) {
    std::string id = ctx->IDENTIFIER()->getText();
    
    auto operandNode = visitOperand(ctx->operand());

    return std::make_unique<AssignNode>(id, std::move(operandNode));
}

// Operand visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitOperand(NowParser::OperandContext* ctx) {
   if (auto literalCtx = dynamic_cast<NowParser::OpLiteralContext*>(ctx)) {
       std::string value = literalCtx->literal()->getText();
       return std::make_unique<LiteralNode>(value);
   } 
   else if (auto idCtx = dynamic_cast<NowParser::OpIdentifierContext*>(ctx)) {
       std::string id = idCtx->IDENTIFIER()->getText();
       return std::make_unique<IdentifierNode>(id);
   }
   return nullptr;
}
