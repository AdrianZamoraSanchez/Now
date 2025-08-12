#include "SemanticVisitor.h"
#include <memory>

/* New Scope or changes in the scope/symbol table */
Scope SemanticVisitor::visit(DeclarationNode* node) {
	return Scope();
}

Scope SemanticVisitor::visit(AssignNode* node) {
	return Scope();
}

Scope SemanticVisitor::visit(TimeBlockNode* node) {
	return Scope();
}	

Scope SemanticVisitor::visit(ConditionalNode* node) {
	return Scope();
}

Scope SemanticVisitor::visit(FunctionNode* node) {
	return Scope();
}

/* Type checking */
Scope SemanticVisitor::visit(BinaryExprNode* node) {
	return Scope();
}

Scope SemanticVisitor::visit(ComparisonNode* node) {
	return Scope();
}
