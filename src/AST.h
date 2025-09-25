#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "Type.h"
#include "Scope.h"
/*
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
*/
// Auxiliar function for print nodes
inline void printIndent(int indent){
	for(int i = 0; i < indent; i++){
  		std::cout << "	";
   	}
}

/* BASE AST NODE CLASS */
class ASTNode {
private:
	//int nodeId;
public:
	virtual ~ASTNode() = default;

	virtual void printNode(int indent = 0) const {
		std::cout << "Default!" << std::endl;
	};
	/*
	std::string getNodeId() const {
		return std::to_string(nodeId);
	};
	*/
};


/*** SIMPLE STRUCTURES ***/

/* IDENTIFIER NODE */
class IdentifierNode : public ASTNode {
    std::string value;

public:
    IdentifierNode(const std::string& val) : value(val) {}

    void printNode(int indent = 0) const override {
    	printIndent(indent);
	   	std::cout << "Node IDENTIFIER: " << value << std::endl;
    }

    std::string getValue() const {
    	return value;
	}

	// TODO!
	/*
	llvm::Value codegen(){
		return nullptr
	}
	*/
};

/* INT LITERAL NODE */
class IntLiteralNode : public ASTNode {
    int value;

public:   
    IntLiteralNode(const int val) : value(val) {}

    void printNode(int indent = 0) const override {
    	printIndent(indent);
	   	std::cout << "Node INT LITERAL: " << value << std::endl;
    }

    std::string getValue() const {
       	return std::to_string(value);
    }

	int getNumericValue() const {
       	return value;
    }
};

/* STRING LITERAL NODE */
class StringLiteralNode : public ASTNode {
    std::string value;

public:
    StringLiteralNode(const std::string& val) : value(val) {}

    void printNode(int indent = 0) const override {
    	printIndent(indent);
	   	std::cout << "Node STRING LITERAL: " << value << std::endl;
    }

    std::string getValue() const{
    	return value;
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

	void printNode(int indent = 0) const override {
		printIndent(indent);
       	
   		std::cout << "Node BINARY_EXPR: " << op << std::endl;

   		if(left){
   			printIndent(indent);
   			std::cout << "With left operand: " << std::endl;
	   		left->printNode(indent+1);
	   	}

	   	if(right){
	   		printIndent(indent);
   			std::cout << "With right operand: " << std::endl;
	   		right->printNode(indent+1);
	   	}
    }

    std::string getOperator() const{
   		return op;
   	}

   	std::unique_ptr<ASTNode> getRight(){
		return std::move(right);
	}
   	
	std::unique_ptr<ASTNode> getLeft(){
		return std::move(left);
	}

	std::string getValue() const {
		return "ExprNode";
	}

	ASTNode* getLeftRaw() const { return left.get(); }
	ASTNode* getRightRaw() const { return right.get(); }
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

	void printNode(int indent = 0) const override {
		printIndent(indent);
       	
		std::cout << "Node COMPARISON: " << op << std::endl;

		if(left){
			printIndent(indent);
			std::cout << "With left node: " << std::endl;
			left->printNode(indent+1);
		}

		if(right){
			printIndent(indent);
			std::cout << "With right node: " << std::endl;
			right->printNode(indent+1);
		}
	}

	std::string getOperator(){
		return op;
	}

	std::unique_ptr<ASTNode> getRight(){
		return std::move(right);
	}

	std::unique_ptr<ASTNode> getLeft(){
		return std::move(left);
	}

	std::string getValue() const {
		return "ComparisonNode";
	}

	ASTNode* getLeftRaw() const { return left.get(); }
	ASTNode* getRightRaw() const { return right.get(); }
};


/*** STMTs STRUCTURES ***/

/* ASSIGN NODE */
class AssignNode : public ASTNode {
	std::string identifier;
    std::unique_ptr<ASTNode> operand;

public:
    AssignNode(const std::string& id,  std::unique_ptr<ASTNode> op)
        : identifier(id), operand(std::move(op)) {}

    void printNode(int indent = 0) const override {
    	printIndent(indent);
	   	std::cout << "Node ASSIGN: " << identifier << std::endl;

	   	if(operand){
	   		printIndent(indent);
	   		std::cout << "With operand: " << std::endl;
	   		operand->printNode(indent+1);
	   	}
    }

    std::string getValue() const{
    	return identifier;
    }

    std::unique_ptr<ASTNode> getOperand(){
    	return std::move(operand);
    }

	ASTNode* getOperandRaw() const { return operand.get(); }
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

	void printNode(int indent = 0) const override {
		printIndent(indent);
       	
   		std::cout << "Node DECLARATION: " << getStringFromType(type) << " - With ID: " << identifier << std::endl;

	   	if(operand){
	   		printIndent(indent);
   			std::cout << "With operand: " << std::endl;
	   		operand->printNode(indent+1);
	   	}
    }

    Type getType(){
    	return type;
    }

    std::string getID(){
    	return identifier;
    }

	std::string getValue() const {
		return getStringFromType(type) + identifier;
	}

    std::unique_ptr<ASTNode> getOperand(){
    	return std::move(operand);
    }

	ASTNode* getOperandRaw() const { return operand.get(); }
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

	void printNode(int indent = 0) const override {
		printIndent(indent);
   		std::cout << "Node TIME_BLOCK with time: " << time << " and unit: "<< timeUnit << std::endl;

   		for(const std::unique_ptr<ASTNode>& stmt : statements){
   			stmt->printNode(indent+1);
   		}
    }

    std::string getValue() const {
    	return timeUnit + std::to_string(time);
    }
	
	int getTime(){
    	return time;
    }

    std::string getTimeUnit(){
    	return timeUnit;
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

	void printNode(int indent = 0) const override {
		printIndent(indent);
		std::cout << "node CONDITIONAL: " << std::endl;
		comparison->printNode(indent+1);
		
		for(const std::unique_ptr<ASTNode>& stmt : statements){
  			stmt->printNode(indent+2);
   		}
	}

	std::string getValue() const {
		return "CONDITIONAL NODE";
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

	void printNode(int indent = 0) const override {
		printIndent(indent);
		std::cout << "node FUNCTION: " << getStringFromType(returnType) << " - " << functionName << std::endl;

		printIndent(indent);
	 	std::cout << "params: " << std::endl;
		/*
		for(const std::unique_ptr<VarDeclaration>& param : params){
 			param->printNode(indent+1);
   		}
		*/

		std::cout << "stmts: " << std::endl;
		for(const std::unique_ptr<ASTNode>& stmt : statements){
  			stmt->printNode(indent+1);
   		}
	}

	Type getType(){
    	return returnType;
    }

	//std::vector<std::unique_ptr<VarDeclaration>>& getArgs(){
		//return params;
	//}
	
    std::string getValue() const {
   		return functionName;
    }
};
