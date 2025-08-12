#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Type.h"

/* Declarations */
class Declaration {
public:
    virtual ~Declaration() = 0;
};

// Function declaration
class FuncDeclaration : public Declaration {
    std::string name;
    std::vector<std::pair<std::string, Type>> arguments;
public:
    ~FuncDeclaration() override;
    FuncDeclaration(const std::string funcName,
                    const std::vector<std::pair<std::string, Type>>& funcArguments);
};

// Variable declaration
class VarDeclaration : public Declaration {
    std::string name;
    Type type;
public:
    ~VarDeclaration() override;
    VarDeclaration(const std::string varName, const Type& varType);
};


/* Scope class */
class Scope {
    std::unordered_map<std::string, std::unique_ptr<Declaration>> symbolTable;
    Scope* fatherScope;
public:
    Scope();

    Declaration* lookup(const std::string& symbol);

    bool addSymbol(const std::string& symbolName, std::unique_ptr<Declaration> decl);
};
