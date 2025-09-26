#include "AST.h"
#include "ASTBuilderVisitor.h"
#include "../grammar/NowParser.h"
#include "../grammar/NowParserBaseVisitor.h"
#include <memory>
#include <vector>

#include <iostream>

// Root of the AST
std::vector<std::unique_ptr<ASTNode>> ASTBuilderVisitor::buildTree(NowParser::ProgramContext* ctx){
	// --- Graphviz ---
	std::string graphNode = addGraphNode("PROGRAM");
	
	// List of program main stmt nodes
	return visitStmtList(ctx->stmt(), graphNode);
}

/*** Intermediate nodes visit functions ***/

// Identifier visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitOpIdentifier(NowParser::OpIdentifierContext* ctx) {
    std::string value = ctx->IDENTIFIER()->getText();

	auto identifierNode = std::make_unique<IdentifierNode>(value);

	// --- Graphviz ---
	std::string myGraphId = addGraphNode("ASSIGN: " + identifierNode->getValue());

    return identifierNode;
}

// Assign visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitAssign(NowParser::AssignContext* ctx) {
	std::string id = ctx->IDENTIFIER()->getText();

	// --- Graphviz ---
    std::string graphNode = addGraphNode("ASSIGN: " + id);
	int childNodeId = this->nextId;

    auto operandNode = visitOperand(ctx->operand());
	
    auto assignNode = std::make_unique<AssignNode>(id, std::move(operandNode));

	addGraphEdge(graphNode, "node"+std::to_string(childNodeId));

    return assignNode;
}

// Operand visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitOperand(NowParser::OperandContext* ctx) {
	// Literal operand	
    if (auto literalCtx = dynamic_cast<NowParser::OpLiteralContext*>(ctx)) {
    	std::string value = literalCtx->literal()->getText();

	    if(std::all_of(value.begin(), value.end(), ::isdigit)){
			auto operandNode = std::make_unique<IntLiteralNode>(std::stoi(value));
			
			// --- Graphviz ---
    		std::string myGraphId = addGraphNode("OPERAND: " + value);

			return operandNode;
	    }

		auto operandNode = std::make_unique<StringLiteralNode>(value);
		
		// --- Graphviz ---
		std::string myGraphId = addGraphNode("OPERAND: " + value);

    	return operandNode;
    } 
    // Identifier operand
    else if (auto idCtx = dynamic_cast<NowParser::OpIdentifierContext*>(ctx)) {
		std::string id = idCtx->IDENTIFIER()->getText();
		auto operandNode = std::make_unique<IdentifierNode>(id); 

		// --- Graphviz ---
    	std::string myGraphId = addGraphNode("OPERAND: " + id);

      	return operandNode;
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
		std::string op = mulDivCtx->op->getText();

		// --- Graphviz ---
		std::string graphNode = addGraphNode("EXPR: " + op);
		
		int leftChildGraphId = this->nextId;
		auto left = visitExpr(mulDivCtx->expr(0));

		int rightChildGraphId = this->nextId;
        auto right = visitExpr(mulDivCtx->expr(1));
		

		auto exprNode = std::make_unique<BinaryExprNode>(op, std::move(left), std::move(right));

		addGraphEdge(graphNode, "node"+std::to_string(leftChildGraphId));
		addGraphEdge(graphNode, "node"+std::to_string(rightChildGraphId));

        return exprNode;
    } 
    // + or -
    else if (auto addSubCtx = dynamic_cast<NowParser::AddSubExprContext*>(ctx)) {
		std::string op = addSubCtx->op->getText();
		
		// --- Graphviz ---
		std::string graphNode = addGraphNode("EXPR: " + op);

        int leftChildGraphId = this->nextId;
		auto left = visitExpr(addSubCtx->expr(0));

		int rightChildGraphId = this->nextId;
        auto right = visitExpr(addSubCtx->expr(1));

		auto exprNode = std::make_unique<BinaryExprNode>(op, std::move(left), std::move(right));

		addGraphEdge(graphNode, "node"+std::to_string(leftChildGraphId));
		addGraphEdge(graphNode, "node"+std::to_string(rightChildGraphId));
        
        return exprNode;
    }
    // Final recursive call of a numeric value  
    else if (auto numCtx = dynamic_cast<NowParser::NumExprContext*>(ctx)) {
        int value = std::stoi(numCtx->NUMBER_LITERAL()->getText());

        auto exprNode = std::make_unique<IntLiteralNode>(value);

		// --- Graphviz ---
		std::string myGraphId = addGraphNode("EXPR: " + std::to_string(value));

        return exprNode;
    }
    // Context in which the expr is surrounded by parenthesis
    else if (auto parenCtx = dynamic_cast<NowParser::ParenExprContext*>(ctx)) {
        return visitExpr(parenCtx->expr());
    }
	// Variable being use as value  
    else if (auto variableCtx = dynamic_cast<NowParser::VariableExprContext*>(ctx)) {
        std::string value = variableCtx->IDENTIFIER()->getText();

        auto exprNode = std::make_unique<IdentifierNode>(value);

		// --- Graphviz ---
		std::string myGraphId = addGraphNode("EXPR: " + value);

        return exprNode;
    }

    throw std::runtime_error("Unsupported expression");
}

/*** Final stmt visit functions ***/

// Declaration visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitDeclaration(NowParser::DeclarationContext* ctx) {
	if(auto decCtx = dynamic_cast<NowParser::DeclarationAssingContext*>(ctx)){
		
		auto typeCtx = dynamic_cast<NowParser::TypeContext*>(decCtx->type());

		std::string typeString = typeCtx->getText();

		Type type = getTypeFromString(typeString);
					
		std::string id = decCtx->IDENTIFIER()->getText();

		// --- Graphviz ---
		std::string graphNode = addGraphNode("DECLARATION: " + typeString + " " + id);
		int childNodeId = this->nextId;
		
		auto operandNode = visitOperand(decCtx->operand());

		addGraphEdge(graphNode, "node"+std::to_string(childNodeId));
			
	    return std::make_unique<DeclarationNode>(type, id, std::move(operandNode));
	}

	if(auto simplDecCtx = dynamic_cast<NowParser::DeclarationSimpleContext*>(ctx)){
		auto typeCtx = dynamic_cast<NowParser::TypeContext*>(simplDecCtx->type());
		std::string typeString = typeCtx->getText();
		
		Type type = getTypeFromString(typeString);
			
		std::string id = simplDecCtx->IDENTIFIER()->getText();

		// --- Graphviz ---
		std::string graphNode = addGraphNode("DECLARATION: " + typeString + " " + id);
			
		return std::make_unique<DeclarationNode>(type, id);
	}

	return nullptr;
}

// Comparison visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitComparison(NowParser::ComparisonContext* ctx) { 
	std::string op = ctx->comparationOperator()->getText();
	
	// --- Graphviz ---
	std::string graphNode = addGraphNode("COMPARISON NODE: " + op);
	int leftChildGraphId = this->nextId;
	int rightChildGraphId = leftChildGraphId + 1;

	auto left = visitOperand(ctx->operand(0));
    auto right = visitOperand(ctx->operand(1));

	auto comparisonNode = std::make_unique<ComparisonNode>(op, std::move(left), std::move(right));

	addGraphEdge(graphNode, "node"+std::to_string(leftChildGraphId));
	addGraphEdge(graphNode, "node"+std::to_string(rightChildGraphId));
	
	return comparisonNode; 
}

// Conditional visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitConditional(NowParser::ConditionalContext* ctx) { 
	// --- Graphviz ---
	std::string graphNode = addGraphNode("CONDICTIONAL NODE: ");
	int childGraphId = this->nextId;

	std::unique_ptr<ASTNode> rawCondition = visitComparison(ctx->comparison());
	
	addGraphEdge(graphNode, "node"+std::to_string(childGraphId));

	// Cast to comparison context
	auto* rawPtr = dynamic_cast<ComparisonNode*>(rawCondition.get());
	if (!rawPtr) {
	    throw std::runtime_error("Expected ComparisonNode in Conditional");
	}
	
	// Transfer of the pointer property to the right type
	std::unique_ptr<ComparisonNode> condition(static_cast<ComparisonNode*>(rawCondition.release()));

	int trueBlockGraphId = this->nextId;
	std::string trueBlockGraph = addGraphNode("CONDICTIONAL TRUE BLOCK: ");

	auto stmts = visitStmtList(ctx->stmt(), trueBlockGraph);
	addGraphEdge(graphNode, "node"+std::to_string(trueBlockGraphId));
	
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

	// --- Graphviz ---
	std::string graphNode = addGraphNode("TIME BLOCK: " + time + " " + timeUnit );

	auto stmts = visitStmtList(ctx->stmt(), graphNode);

	return std::make_unique<TimeBlockNode>(stoi(time), timeUnit, std::move(stmts)); 
}

// Function visitor
std::unique_ptr<ASTNode> ASTBuilderVisitor::visitFunction(NowParser::FuncDeclarationContext* ctx){
	std::string functionName = ctx->IDENTIFIER()->getText();
	
	std::string functionTypeString = ctx->type()->getText();
	Type functionType = getTypeFromString(functionTypeString);

	std::vector<std::unique_ptr<DeclarationNode>> paramList = visitParams(ctx->paramList());

	// --- Graphviz ---
	std::string graphNode = addGraphNode("FUNCTION: " + functionTypeString + " " + functionName);

	auto stmts = visitStmtList(ctx->stmt(), graphNode);
	
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

// Single STMT visit
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

// STMT list
std::vector<std::unique_ptr<ASTNode>> ASTBuilderVisitor::visitStmtList(const std::vector<NowParser::StmtContext*>& stmts, std::string fatherId) {
    std::vector<std::unique_ptr<ASTNode>> result;
	std::cerr << "visitStmtList: size=" << stmts.size() << std::endl;
    for (auto* stmt : stmts) {
		int childId = this->nextId;
		auto node = visitStmt(stmt);
        if (node) {
			std::cerr << " -> visiting stmt" << std::endl;
            addGraphEdge(fatherId ,
                         "node" + std::to_string(childId));
            result.push_back(std::move(node));
        }
    }

	std::cerr << "visitStmtList end" << std::endl;
    return result;
}