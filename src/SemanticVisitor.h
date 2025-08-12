#pragma once
#include "AST.h"
#include "Scope.h"
#include <memory>

class SemanticVisitor {
public:
	// Node - Scope associative map
	std::unordered_map<ASTNode*, Scope*> nodeScopes;
	Scope* currentScope = nullptr;

	// New Scope or changes in the scope/symbol table
	Scope visit(DeclarationNode* node);
	Scope visit(AssignNode* node);

	Scope visit(TimeBlockNode* node);
	Scope visit(ConditionalNode* node);
	Scope visit(FunctionNode* node);

	// Type checking 
    Scope visit(BinaryExprNode* node);
	Scope visit(ComparisonNode* node);
};
