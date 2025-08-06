#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "Type.h"

/* BASE AST NODE CLASS */
class ASTNode {
public:
	virtual ~ASTNode() = default;

	virtual void printNode() const {
		std::cout << "Default!" << std::endl;
	};
};


/*** SIMPLE STRUCTURES ***/

/* IDENTIFIER NODE */
class IdentifierNode : public ASTNode {
    std::string value;

public:
    IdentifierNode(const std::string& val) : value(val) {}

    void printNode() const override {
	   	std::cout << "Node IDENTIFIER: " << value << std::endl;
    }
};

/* INT LITERAL NODE */
class IntLiteralNode : public ASTNode {
    int value;

public:   
    IntLiteralNode(const int val) : value(val) {}

    void printNode() const override {
	   	std::cout << "Node INT LITERAL: " << value << std::endl;
    }
};

/* STRING LITERAL NODE */
class StringLiteralNode : public ASTNode {
    std::string value;

public:
    StringLiteralNode(const std::string& val) : value(val) {}

    void printNode() const override {
	   	std::cout << "Node STRING LITERAL: " << value << std::endl;
    }
};


/*** INTERMEDIATE STRUCTURES ***/

/* BINARY EXPRESION NODE */
class BinaryExprNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    BinaryExprNode(const std::string& op,
                   std::unique_ptr<ASTNode> lhs,
                   std::unique_ptr<ASTNode> rhs)
        		   : op(op), left(std::move(lhs)), right(std::move(rhs)) {}

	void printNode() const override {
   		std::cout << "Node BINARY_EXPR: " << op << std::endl;

   		if(left){
   			std::cout << "With left operand: ";
	   		left->printNode();
	   	}

	   	if(right){
   			std::cout << "With right operand: ";
	   		right->printNode();
	   	}
    }
};

/* COMPARISON NODE */
class ComparisonNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    ComparisonNode(const std::string opSimbol,
                   std::unique_ptr<ASTNode> lt,
                   std::unique_ptr<ASTNode> rt)
		 		   : op(opSimbol), left(std::move(lt)), right(std::move(rt)) {}

	void printNode() const override {
		std::cout << "Node COMPARISON: " << op << std::endl;

		if(left){
			std::cout << "With left node: ";
			left->printNode();
		}

		if(right){
			std::cout << "With right node: ";
			right->printNode();
		}
	}
};


/*** STMTs STRUCTURES ***/

/* ASSIGN NODE */
class AssignNode : public ASTNode {
	std::string id;
    std::unique_ptr<ASTNode> operand;

public:
    AssignNode(const std::string& id,  std::unique_ptr<ASTNode> op)
        : id(id), operand(std::move(op)) {}

    void printNode() const override {
	   	std::cout << "Node ASSIGN: " << id << std::endl;

	   	if(operand){
	   		std::cout << "With operand: ";
	   		operand->printNode();
	   	}
    }
};

/* DECLARATION NODE */
class DeclarationNode : public ASTNode {
	Type type;
	std::string identifier;
	std::unique_ptr<ASTNode> operand;

public:
	DeclarationNode(const Type& typeID,
                    const std::string id,
                    std::unique_ptr<ASTNode> op)
                    : type(typeID), identifier(id), operand(std::move(op)) {}

    DeclarationNode(const Type& typeID,
                    const std::string id)
                    : type(typeID), identifier(id), operand(nullptr) {}

	void printNode() const override {
   		std::cout << "Node DECLARATION: " << getStringFromType(type) << std::endl;

   		if(!identifier.empty()){
   			std::cout << "With ID: " << identifier << std::endl;
	   	}

	   	if(operand){
   			std::cout << "With operand: ";
	   		operand->printNode();
	   	}
    }
};

/* TIME BLOCK NODE */
class TimeBlockNode : public ASTNode {
    int time;
    std::string timeUnit;

    std::vector<std::unique_ptr<ASTNode>> statements;

public:
    TimeBlockNode(int value, const std::string& unit,
                  std::vector<std::unique_ptr<ASTNode>> stmts)
    			  : time(value), timeUnit(unit), statements(std::move(stmts)) {}

	void printNode() const override {
   		std::cout << "Node TIME_BLOCK with time: " << time << " and unit: "<< timeUnit << std::endl;

   		for(const std::unique_ptr<ASTNode>& stmt : statements){
   			stmt->printNode();
   		}
    }
};


/* CONDITIONAL NODE */
class ConditionalNode : public ASTNode {
	std::unique_ptr<ComparisonNode> comparison;
	std::vector<std::unique_ptr<ASTNode>> statements;

public:
	ConditionalNode(std::unique_ptr<ComparisonNode> compNode,
                    std::vector<std::unique_ptr<ASTNode>> stmts)
					: comparison(std::move(compNode)), statements(std::move(stmts)) {}

	void printNode() const override {
		std::cout << "node CONDITIONAL: "; 
		comparison->printNode();
		
		for(const std::unique_ptr<ASTNode>& stmt : statements){
  			stmt->printNode();
   		}
	}
};

/* FUNCTION NODE */
class FunctionNode : public ASTNode {
	std::string functionName;
	Type returnType;
	std::vector<std::unique_ptr<DeclarationNode>> params;
	std::vector<std::unique_ptr<ASTNode>> statements;

public:
	FunctionNode(const std::string& name,
				 const Type& type,
				 std::vector<std::unique_ptr<DeclarationNode>> paramList,
                 std::vector<std::unique_ptr<ASTNode>> stmts)
				 : functionName(name), returnType(type), params(std::move(paramList)), statements(std::move(stmts)) {}

	void printNode() const override {
		std::cout << "node FUNCTION: " << getStringFromType(returnType) << " - " << functionName << std::endl;

	 	std::cout << "params: " << std::endl;
		for(const std::unique_ptr<DeclarationNode>& param : params){
 			param->printNode();
   		}

		std::cout << "stmts: " << std::endl;
		for(const std::unique_ptr<ASTNode>& stmt : statements){
  			stmt->printNode();
   		}
	}
};
