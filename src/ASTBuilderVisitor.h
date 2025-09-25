#pragma once
#include "AST.h"
#include "../grammar/NowLexer.h"
#include "../grammar/NowParser.h"
#include <memory>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

class ASTBuilderVisitor {
public:
    GVC_t* gvc;
    Agraph_t* g;
    int nextId;

    ASTBuilderVisitor() {
        gvc = gvContext();
        g = agopen((char*)"AST", Agdirected, 0);
        nextId = 0;
    }

    ~ASTBuilderVisitor() {
        saveGraph("AST.png");
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);
    }

    /* AST visual graph generation */
    void saveGraph(const std::string& filename) {
        std::cout << "Generated the file: " << filename << std::endl;
        gvLayout(gvc, g, "dot");
        gvRenderFilename(gvc, g, "png", filename.c_str());
    }

    std::string addGraphNode(const std::string& label) {
        std::string id = "node" + std::to_string(nextId++);
        std::cout << "Node " << id << " - " << label << std::endl;
        Agnode_t* n = agnode(g, (char*)id.c_str(), 1);
        agset(n, (char*)"label", (char*)label.c_str());
        return id;
    }

    void addGraphEdge(const std::string& from, const std::string& to) {
        std::cout << "Edge from " << from << " - " << to << std::endl;
        agedge(g, agnode(g, (char*)from.c_str(), 0), agnode(g, (char*)to.c_str(), 0), 0, 1);
    }

    /* Node generation */
	std::vector<std::unique_ptr<ASTNode>> buildTree(NowParser::ProgramContext* ctx);
    std::unique_ptr<ASTNode> visitProgram(NowParser::ProgramContext* ctx);
    std::unique_ptr<ASTNode> visitAssign(NowParser::AssignContext* ctx);
    std::unique_ptr<ASTNode> visitOperand(NowParser::OperandContext* ctx);
	std::unique_ptr<ASTNode> visitExpr(NowParser::ExprContext* ctx);
	
	std::unique_ptr<ASTNode> visitOpLiteral(NowParser::OpLiteralContext* ctx);
    std::unique_ptr<ASTNode> visitOpIdentifier(NowParser::OpIdentifierContext* ctx);
    
    std::unique_ptr<ASTNode> visitConditional(NowParser::ConditionalContext* ctx);
    std::unique_ptr<ASTNode> visitTimeBlock(NowParser::TimeBlockContext* ctx);
    std::unique_ptr<ASTNode> visitComparison(NowParser::ComparisonContext* ctx);
	std::unique_ptr<ASTNode> visitDeclaration(NowParser::DeclarationContext* ctx);
    
    std::unique_ptr<ASTNode> visitAddSubExpr(NowParser::AddSubExprContext* ctx);
    std::unique_ptr<ASTNode> visitMulDivExpr(NowParser::MulDivExprContext* ctx);
    std::unique_ptr<ASTNode> visitNumExpr(NowParser::NumExprContext* ctx);
    std::unique_ptr<ASTNode> visitParenExpr(NowParser::ParenExprContext* ctx);

    std::unique_ptr<ASTNode> visitFunction(NowParser::FuncDeclarationContext* ctx);
    std::vector<std::unique_ptr<DeclarationNode>> visitParams(NowParser::ParamListContext* ctx);

    std::unique_ptr<ASTNode> visitStmt(NowParser::StmtContext* stmtCtx);
    std::vector<std::unique_ptr<ASTNode>> visitStmtList(const std::vector<NowParser::StmtContext*>& stmts, std::string fatherId);
};
