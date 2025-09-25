#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Type.h"

// OOP methodology for expansibility, in the future I might include structs, enums, objects, etc.

/* Declarations */
class Declaration {
public:
    virtual ~Declaration() = 0;
};

// Variable declaration
class VarDeclaration : public Declaration {
    std::string name;
    Type type;
public:
    ~VarDeclaration() override;
    VarDeclaration(const std::string varName, const Type& varType);
};


// Function declaration
class FuncDeclaration : public Declaration {
    std::string name;
    Type type;
    std::vector<VarDeclaration> arguments;
public:
    ~FuncDeclaration() override;
    FuncDeclaration(const std::string funcName,
                    const Type funcType,
                    const std::vector<VarDeclaration>& funcArguments);
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
