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
	Scope visit(FunctionNode* node);
	
	Scope visit(TimeBlockNode* node);

	// Type checking 
    void visit(BinaryExprNode* node);
	void visit(ComparisonNode* node);

	// IDs existence check
	void visit(AssignNode* node);
	void visit(ConditionalNode* node);
};
