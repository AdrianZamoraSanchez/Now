#include "SemanticVisitor.h"
#include <memory>

/* New Scope or changes in the scope/symbol table */
Scope SemanticVisitor::visit(DeclarationNode* node) {
	auto decl = std::make_unique<VarDeclaration>(node->getID(), node->getType());

	Scope scope;
	scope.addSymbol(node->getID(), std::move(decl));

	nodeScopes.insert({node, currentScope});
	
	return Scope();
}

Scope SemanticVisitor::visit(TimeBlockNode* node) {
	Scope scope;

	return Scope();
}	

/*
Scope SemanticVisitor::visit(FunctionNode* node) {
	Scope scope;
	
	auto decl = std::make_unique<FuncDeclaration>(node->getId(), node->getType(), node->getArguments());

	scope.addSymbol(node->getId(), std::move(decl));

	nodeScopes.insert({node, currentScope});

	return Scope();
}
*/

/*
void SemanticVisitor::visit(ConditionalNode* node) {
	Scope scope;
	
	return Scope();
}
*/

/* Type checking */
/*
void SemanticVisitor::visit(BinaryExprNode* node) {
	auto lhs = node->getLeft();
	auto rhs = node->getRight();

	// TODO lhsType = rhsType
	return;
}
*/

/*
void SemanticVisitor::visit(ComparisonNode* node) {
	// TODO lhsType = rhsType 
	return;
}
*/

/*
void SemanticVisitor::visit(AssignNode* node) {
	auto lhs = currentScope->lookup(node->getId());

	if(auto lhs = dynamic_cast<DeclarationNode*>(lhs)){
		auto lhsType = lhs->getType();
	}else{
		throw std::runtime_error("El lhs debe ser una declaración");
	}

	if (auto intNode = dynamic_cast<IntLiteralNode*>(rhs)) {
		enum Type rhsType = type_int;
	} else if (auto strNode = dynamic_cast<StringLiteralNode*>(rhs)) {
		enum Type rhsType = type_string;
	} else {
		throw std::runtime_error("Operand no es literal válido");
	}

	return;
}
*/
 