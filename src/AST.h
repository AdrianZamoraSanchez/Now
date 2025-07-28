#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class ASTNode {
public:
	virtual ~ASTNode() = default;

	virtual void printNode(){
		std::cout << "Default" << std::endl;
	};
};

class StmtNode : public ASTNode {
	std::string stmt;
	std::unique_ptr<ASTNode> left, right;

public:
	StmtNode(const std::string value,
             std::unique_ptr<ASTNode> left,
             std::unique_ptr<ASTNode> right) 
             : stmt(value), left(std::move(left)), right(std::move(right)) {}

    void printNode(){
    	std::cout << "Node STMT" << std::endl;

    	if(left){
    		std::cout << "Nodo left: ";
    		left->printNode();
    	}
    	if(right){
    		std::cout << "Nodo right: ";
    		right->printNode();
    	}
    }
};

class AssignNode : public ASTNode {
	std::string id;
    std::unique_ptr<ASTNode> operand;

public:
    AssignNode(const std::string& id,  std::unique_ptr<ASTNode> op)
        : id(id), operand(std::move(op)) {}

    void printNode(){
	   	std::cout << "Node ASSIGN: " << id << std::endl;

	   	if(operand){
	   		std::cout << "With operand: ";
	   		operand->printNode();
	   	}
    }
};

class DeclarationNode : public ASTNode {
	std::string type;
	std::string identifier;
	std::unique_ptr<ASTNode> operand;

public:
	DeclarationNode(const std::string typeID,
                    const std::string id,
                    std::unique_ptr<ASTNode> op)
                    : type(typeID), identifier(id), operand(std::move(op)) {}

	void printNode(){
   		std::cout << "Node DECLARATION: " << type << std::endl;

   		if(!identifier.empty()){
   			std::cout << "With ID: " << identifier << std::endl;
	   	}

	   	if(operand){
   			std::cout << "With operand: ";
	   		operand->printNode();
	   	}
    }
};

class IdentifierNode : public ASTNode {
    std::string value;

public:
    IdentifierNode(const std::string& n) : value(n) {}

    void printNode(){
	   	std::cout << "Node IDENTIFIER: " << value << std::endl;
    }
};

class IntLiteralNode : public ASTNode {
    int value;

public:   
    IntLiteralNode(const int val) : value(val) {}

    void printNode(){
	   	std::cout << "Node INT LITERAL: " << value << std::endl;
    }
};

class StringLiteralNode : public ASTNode {
    std::string value;

public:
    StringLiteralNode(const std::string& val) : value(val) {}

    void printNode(){
	   	std::cout << "Node STRING LITERAL: " << value << std::endl;
    }
};

class BinaryExprNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    BinaryExprNode(const std::string& op,
                   std::unique_ptr<ASTNode> lhs,
                   std::unique_ptr<ASTNode> rhs)
        		   : op(op), left(std::move(lhs)), right(std::move(rhs)) {}

	void printNode(){
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

class TimeBlockNode : public ASTNode {
    int time;
    std::string timeUnit;

    std::vector<std::unique_ptr<ASTNode>> statements;

public:
    TimeBlockNode(int value, const std::string& unit,
                  std::vector<std::unique_ptr<ASTNode>> stmts)
    			  : time(value), timeUnit(unit), statements(std::move(stmts)) {}

	void printNode(){
   		std::cout << "Node TIME_BLOCK: " << std::to_string(time) << timeUnit << std::endl;

   		for(const std::unique_ptr<ASTNode>& stmt : statements){
   			stmt->printNode();
   		}
    }
};

class ComparisonNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    ComparisonNode(const std::string opSimbol,
                   std::unique_ptr<ASTNode> lt,
                   std::unique_ptr<ASTNode> rt)
		 		   : op(opSimbol), left(std::move(lt)), right(std::move(rt)) {}

	void printNode(){
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

class ConditionalNode : public ASTNode {
	std::unique_ptr<ComparisonNode> comparison;
	std::vector<std::unique_ptr<ASTNode>> statements;

public:
	ConditionalNode(std::unique_ptr<ComparisonNode> compNode,
                    std::vector<std::unique_ptr<ASTNode>> stmts)
					: comparison(std::move(compNode)), statements(std::move(stmts)) {}

	void printNode(){
		std::cout << "node CONDITIONAL: "; 
		comparison->printNode();
		
		for(const std::unique_ptr<ASTNode>& stmt : statements){
  			stmt->printNode();
   		}
	}
};
