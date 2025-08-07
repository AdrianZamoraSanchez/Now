#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Type.h"

/* Functions and variable declarations */
class Declaration {
public:
	virtual ~Declaration() = 0;
};

// Function declaration
class FuncDeclaration : public Declaration {
	std::string name;
	std::vector<std::pair<std::string, Type>> arguments;
public:
	~FuncDeclaration() override {}

	FuncDeclaration(const std::string funcName,
					const std::vector<std::pair<std::string, Type>>& funcArguments) 
					: name(funcName), arguments(funcArguments){};
};

// Variable declaration
class VarDeclaration : public Declaration {
	std::string name;
	Type type;
public:
	~VarDeclaration() override {}

	VarDeclaration(const std::string varName, 
				   const Type& varType) 
				   : name(varName), type(varType){};
};

/* Scope class */
class Scope {
	std::unordered_map<std::string, std::unique_ptr<Declaration>> symbolTable;
	Scope* fatherScope;
public:
	Scope() : fatherScope(nullptr) {}

	// Getting symbols in the valid scope
	Declaration* lookup(const std::string& symbol){
		auto it = symbolTable.find(symbol);

		if (it != symbolTable.end()) {
			return it->second.get();
		}else if (fatherScope != nullptr){
			return fatherScope->lookup(symbol);
		}

		return nullptr;
	}

	// Adding symbols to this scope
	bool addSymbol(const std::string& symbolName, std::unique_ptr<Declaration> decl){
		auto inserted = symbolTable.emplace(symbolName, std::move(decl));
	    return inserted.second; 
	}
};
