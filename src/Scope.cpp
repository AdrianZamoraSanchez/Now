#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Type.h"
#include "Scope.h"

/* Functions and variable declarations */
Declaration::~Declaration() = default;

// Function declaration
FuncDeclaration::~FuncDeclaration() = default;

FuncDeclaration::FuncDeclaration(
    const std::string funcName,
    const Type funcType,
    const std::vector<VarDeclaration>& funcArguments
) : name(funcName), type(funcType), arguments(funcArguments) {}

// Variable declaration
VarDeclaration::~VarDeclaration() = default;

VarDeclaration::VarDeclaration(
    const std::string varName,
    const Type& varType
) : name(varName), type(varType) {}


/* Scope class */
Scope::Scope() : fatherScope(nullptr) {}

Declaration* Scope::lookup(const std::string& symbol) {
    auto it = symbolTable.find(symbol);
    if (it != symbolTable.end()) {
        return it->second.get();
    } else if (fatherScope != nullptr) {
        return fatherScope->lookup(symbol);
    }
    return nullptr;
}

bool Scope::addSymbol(const std::string& symbolName, std::unique_ptr<Declaration> decl) {
    auto inserted = symbolTable.emplace(symbolName, std::move(decl));
    return inserted.second;
}
