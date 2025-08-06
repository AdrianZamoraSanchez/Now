#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Type.h"

class Declaration {
public:
	virtual ~Declaration() = 0;
};

class FuncDeclaration : public Declaration {
	std::string name;
	std::vector<std::string, Type> arguments;
public:
	FuncDeclaration(const std::string funcName,
					std::vector<std::string, Type> funcArguments) 
					: name(funcName), arguments(funcArguments){};
};

class VarDeclaration : public Declaration {
	std::string name;
	Type type;
public:
	VarDeclaration(const std::string varName, 
				   const Type varType) 
				   : name(varName), type(varType){};
};

class Scope {
	std::unordered_map<std::string, Declaration> symbolTable;
};
