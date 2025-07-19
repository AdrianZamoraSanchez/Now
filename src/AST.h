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
public:
	std::string stmt;

	std::unique_ptr<ASTNode> left, right;

	StmtNode(const std::string value,
             std::unique_ptr<ASTNode> left,
             std::unique_ptr<ASTNode> right) 
             : stmt(value), left(std::move(left)), right(std::move(right)) {}

    void printNode(){
    	std::cout << "Nodo STMT" << std::endl;

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
public:
	std::string id;
    std::unique_ptr<ASTNode> operand;
    
    AssignNode(const std::string& id,  std::unique_ptr<ASTNode> op)
        : id(id), operand(std::move(op)) {}

    void printNode(){
	   	std::cout << "Nodo ASSIGN: " << id << std::endl;

	   	if(operand){
	   		std::cout << "Nodo operand: ";
	   		operand->printNode();
	   	}
    }
};

class DeclarationNode : public ASTNode {
public:
	std::string type;
	std::string identifier;
	std::unique_ptr<ASTNode> operand;

	DeclarationNode(const std::string typeID,
                    const std::string id,
                    std::unique_ptr<ASTNode> op)
                    : type(typeID), identifier(id), operand(std::move(op)) {}
};

class IdentifierNode : public ASTNode {
public:
    std::string value;

    IdentifierNode(const std::string& n) : value(n) {}

    void printNode(){
	   	std::cout << "Nodo IDENTIFIER: " << value << std::endl;
    }
};

class IntLiteralNode : public ASTNode {
public:
    int value;
    
    IntLiteralNode(const int val) : value(val) {}

    void printNode(){
	   	std::cout << "Nodo INT LITERAL: " << value << std::endl;
    }
};

class StringLiteralNode : public ASTNode {
public:
    std::string value;
    
    StringLiteralNode(const std::string& val) : value(val) {}

    void printNode(){
	   	std::cout << "Nodo STRING LITERAL: " << value << std::endl;
    }
};

class BinaryExprNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryExprNode(const std::string& op,
                   std::unique_ptr<ASTNode> lhs,
                   std::unique_ptr<ASTNode> rhs)
        		   : op(op), left(std::move(lhs)), right(std::move(rhs)) {}
};

class TimeBlockNode : ASTNode {
    int time;
    std::string timeUnit;

    std::vector<std::unique_ptr<ASTNode>> statements;

    TimeBlockNode(int value, const std::string& unit,
                  std::vector<std::unique_ptr<ASTNode>> stmts)
    			  : time(value), timeUnit(unit), statements(std::move(stmts)) {}
};

class ComparisonNode : ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    ComparisonNode(const std::string opSimbol,
                   std::unique_ptr<ASTNode> lt,
                   std::unique_ptr<ASTNode> rt)
		 		   : op(opSimbol), left(std::move(lt)), right(std::move(rt)) {}
};

class ConditionalNode : ASTNode {
	std::unique_ptr<ComparisonNode> comparison;
	std::vector<std::unique_ptr<ASTNode>> statements;

	ConditionalNode(std::unique_ptr<ComparisonNode> compNode,
                    std::vector<std::unique_ptr<ASTNode>> stmts)
					: comparison(std::move(compNode)), statements(std::move(stmts)) {}
};
