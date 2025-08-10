#include "AST.h"
#include "ASTBuilderVisitor.h"
#include "../grammar/NowParser.h"
#include "../grammar/NowParserBaseVisitor.h"
#include <memory>
#include <vector>

#include <iostream>

// Root of the AST
std::vector<std::unique_ptr<ASTNode>> ASTBuilderVisitor::buildTree(NowParser::ProgramContext* ctx){
	// List of program main stmt nodes
	return visitStmtList(ctx->stmt());
}

/*** Intermediate nodes visit functions ***/

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
	// Literal operand	
    if (auto literalCtx = dynamic_cast<NowParser::OpLiteralContext*>(ctx)) {
    	std::string value = literalCtx->literal()->getText();

	    if(std::all_of(value.begin(), value.end(), ::isdigit)){
	    	return std::make_unique<IntLiteralNode>(std::stoi(value));
	    }
       	
    	return std::make_unique<StringLiteralNode>(value);
    } 
    // Identifier operand
    else if (auto idCtx = dynamic_cast<NowParser::OpIdentifierContext*>(ctx)) {
		std::string id = idCtx->IDENTIFIER()->getText();
      	return std::make_unique<IdentifierNode>(id);
  	}
  	// Expr operand
  	else if (auto exprCtx = dynamic_cast<NowParser::OpExprContext*>(ctx)) {
   		auto exprNode = visitExpr(exprCtx->expr());
	   	return exprNode;
   }
   return nullptr;
}

// Expr visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitExpr(NowParser::ExprContext* ctx) {
	// * or /
    if (auto mulDivCtx = dynamic_cast<NowParser::MulDivExprContext*>(ctx)) {
        auto left = visitExpr(mulDivCtx->expr(0));
        auto right = visitExpr(mulDivCtx->expr(1));
        std::string op = mulDivCtx->op->getText();
        
        return std::make_unique<BinaryExprNode>(op, std::move(left), std::move(right));
    } 
    // + or -
    else if (auto addSubCtx = dynamic_cast<NowParser::AddSubExprContext*>(ctx)) {
        auto left = visitExpr(addSubCtx->expr(0));
        auto right = visitExpr(addSubCtx->expr(1));
        std::string op = addSubCtx->op->getText();
        
        return std::make_unique<BinaryExprNode>(op, std::move(left), std::move(right));
    }
    // Final recursive call of a numeric value  
    else if (auto numCtx = dynamic_cast<NowParser::NumExprContext*>(ctx)) {
        int value = std::stoi(numCtx->NUMBER_LITERAL()->getText());
        
        return std::make_unique<IntLiteralNode>(value);
    }
    // Context in which the expr is surrounded by parenthesis
    else if (auto parenCtx = dynamic_cast<NowParser::ParenExprContext*>(ctx)) {
        return visitExpr(parenCtx->expr());
    }

    throw std::runtime_error("Unsupported expression type");
}

/*** Final stmt visit functions ***/

// Declaration visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitDeclaration(NowParser::DeclarationContext* ctx) {
	if(auto decCtx = dynamic_cast<NowParser::DeclarationAssingContext*>(ctx)){
		auto typeCtx = dynamic_cast<NowParser::TypeContext*>(decCtx->type());

		std::string typeString = typeCtx->getText();

		std::cout << typeString << std::endl;

		Type type = getTypeFromString(typeString);
					
		std::string id = decCtx->IDENTIFIER()->getText();
		
		auto operandNode = visitOperand(decCtx->operand());
			
	    return std::make_unique<DeclarationNode>(type, id, std::move(operandNode));
	}

	if(auto simplDecCtx = dynamic_cast<NowParser::DeclarationSimpleContext*>(ctx)){
		auto typeCtx = dynamic_cast<NowParser::TypeContext*>(simplDecCtx->type());
		std::string typeString = typeCtx->getText();
		
		Type type = getTypeFromString(typeString);
			
		std::string id = simplDecCtx->IDENTIFIER()->getText();
			
		return std::make_unique<DeclarationNode>(type, id);
	}

	return nullptr;
}

// Comparison visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitComparison(NowParser::ComparisonContext* ctx) { 
	auto left = visitOperand(ctx->operand(0));
    auto right = visitOperand(ctx->operand(1));

	std::string op = ctx->comparationOperator()->getText();
	
	return std::make_unique<ComparisonNode>(op, std::move(left), std::move(right)); 
}

// Conditional visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitConditional(NowParser::ConditionalContext* ctx) { 
	std::unique_ptr<ASTNode> rawCondition = visitComparison(ctx->comparison());

	// Cast to comparison context
	auto* rawPtr = dynamic_cast<ComparisonNode*>(rawCondition.get());
	if (!rawPtr) {
	    throw std::runtime_error("Expected ComparisonNode in Conditional");
	}
	
	// Transfer of the pointer property to the right type
	std::unique_ptr<ComparisonNode> condition(static_cast<ComparisonNode*>(rawCondition.release()));
	
	auto stmts = visitStmtList(ctx->stmt());
	
	return std::make_unique<ConditionalNode>(std::move(condition), std::move(stmts));
}

// Time Block visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitTimeBlock(NowParser::TimeBlockContext* ctx) { 
	std::string timeUnit;
	std::string time;
	
	// Cast to the time unit context
	auto tsCtx = ctx->timeStamp();
	if (auto msCtx = dynamic_cast<NowParser::MsTimeStampContext*>(tsCtx)) {
	    time = msCtx->NUMBER_LITERAL()->getText();
	    timeUnit = "ms";
	} else if (auto secCtx = dynamic_cast<NowParser::SecTimeStampContext*>(tsCtx)) {
	    time = secCtx->NUMBER_LITERAL()->getText();
	    timeUnit = "sec";
	} else if (auto minCtx = dynamic_cast<NowParser::MinTimeStampContext*>(tsCtx)) {
	    time = minCtx->NUMBER_LITERAL()->getText();
		timeUnit = "min";
	} else if (auto hrCtx = dynamic_cast<NowParser::HrTimeStampContext*>(tsCtx)) {
	    time = hrCtx->NUMBER_LITERAL()->getText();
	    timeUnit = "hr";
	} else {
	    throw std::runtime_error("Unknown timeStamp type");
	}

	auto stmts = visitStmtList(ctx->stmt());

	return std::make_unique<TimeBlockNode>(stoi(time), timeUnit, std::move(stmts)); 
}

// Function visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitFunction(NowParser::FuncDeclarationContext* ctx){
	std::string functionName = ctx->IDENTIFIER()->getText();
	
	std::string functionTypeString = ctx->type()->getText();
	Type functionType = getTypeFromString(functionTypeString);

	std::vector<std::unique_ptr<DeclarationNode>> paramList = visitParams(ctx->paramList());

	auto stmts = visitStmtList(ctx->stmt());
	
	return std::make_unique<FunctionNode>(functionName, functionType, std::move(paramList), std::move(stmts));
}

// ParamList visitor
std::vector<std::unique_ptr<DeclarationNode>> ASTBuilderVisitor::visitParams(NowParser::ParamListContext* ctx){
	std::vector<std::unique_ptr<DeclarationNode>> paramList;

	// Params to declaration nodes
	for (auto* paramCtx : ctx->param()) {
		auto typeCtx = dynamic_cast<NowParser::TypeContext*>(paramCtx->type());
		std::string paramId = paramCtx->IDENTIFIER()->getText();
	    std::string functionTypeString = paramCtx->type()->getText();
    	Type functionType = getTypeFromString(functionTypeString);

		paramList.push_back(std::make_unique<DeclarationNode>(functionType, paramId, nullptr));
	}

	return paramList;
}


/*** Auxiliary visit functions ***/

// STMT list
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitStmt(NowParser::StmtContext* stmtCtx) {
    if (auto assignCtx = dynamic_cast<NowParser::StmtAssignContext*>(stmtCtx)) {
        return visitAssign(assignCtx->assign());
    } else if (auto declarationCtx = dynamic_cast<NowParser::StmtDeclarationContext*>(stmtCtx)) {
        return visitDeclaration(declarationCtx->declaration());
    } else if (auto timeBlockCtx = dynamic_cast<NowParser::StmtTimeBlockContext*>(stmtCtx)) {
        return visitTimeBlock(timeBlockCtx->timeBlock());
    } else if (auto conditionalCtx = dynamic_cast<NowParser::StmtConditionalContext*>(stmtCtx)) {
        return visitConditional(conditionalCtx->conditional());
    } else if (auto functionCtx = dynamic_cast<NowParser::StmtFunDeclarationContext*>(stmtCtx)) {
        return visitFunction(functionCtx->funcDeclaration());
    }
    
    return nullptr;
}

// Single STMT visit
std::vector<std::unique_ptr<ASTNode>> ASTBuilderVisitor::visitStmtList(const std::vector<NowParser::StmtContext*>& stmts) {
    std::vector<std::unique_ptr<ASTNode>> result;

    for (auto* stmt : stmts) {
        if (auto node = visitStmt(stmt)) {
            result.push_back(std::move(node));
        }
    }

    return result;
}

