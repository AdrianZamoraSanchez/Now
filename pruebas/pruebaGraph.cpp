#include "../src/AST.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <iostream>
#include <fstream>

void exportASTtoDOT(const ASTNode* root, std::ostream& out, int& id) {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << typeid(*root).name() << "\"];\n";

    // Identificador
    if (auto idNode = dynamic_cast<const IdentifierNode*>(root)) {
        out << "  node" << myId << " [label=\"IDENT: " << idNode->getValue() << "\"];\n";
    }
    else if (auto intNode = dynamic_cast<const IntLiteralNode*>(root)) {
        out << "  node" << myId << " [label=\"INT: " << intNode->getValue() << "\"];\n";
    }
    if (auto bin = dynamic_cast<const BinaryExprNode*>(root)) {
        out << "  node" << myId << " [label=\"BINARY: " << bin->getOperator() << "\"];\n";
    }

    // Ejemplo con hijos (BinaryExprNode)
    if (auto bin = dynamic_cast<const BinaryExprNode*>(root)) {
        if (bin->getLeftRaw()) {
            int leftId = id;
            exportASTtoDOT(bin->getLeftRaw(), out, id);
            out << "  node" << myId << " -> node" << leftId << ";\n";
        }
        if (bin->getRightRaw()) {
            int rightId = id;
            exportASTtoDOT(bin->getRightRaw(), out, id);
            out << "  node" << myId << " -> node" << rightId << ";\n";
        }
    }

    if (auto assignNode = dynamic_cast<const AssignNode*>(root)) {
        out << "  node" << myId << " [label=\"ASSIGN: " << assignNode->getID() << "\"];\n";
    
        if (assignNode->getOperandRaw()) {
            int childId = id;
            exportASTtoDOT(assignNode->getOperandRaw(), out, id);
            out << "  node" << myId << " -> node" << childId << ";\n";
        }
    }
}

void saveASTtoDOT(const ASTNode* root, const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph AST {\n";
    int id = 0;
    exportASTtoDOT(root, out, id);
    out << "}\n";
}


int main() {
    // Construir AST de prueba: a = 5 + 3
    auto left = std::make_unique<IntLiteralNode>(5);
    auto right = std::make_unique<IntLiteralNode>(3);
    auto binExpr = std::make_unique<BinaryExprNode>("+", std::move(left), std::move(right));
    auto assign = std::make_unique<AssignNode>("a", std::move(binExpr));

    // Exportar a DOT
    saveASTtoDOT(assign.get(), "ast.dot");

    std::cout << "Archivo AST generado: ast.dot\n";
    std::cout << "Para generar PNG: dot -Tpng ast.dot -o ast.png\n";
    return 0;
}
