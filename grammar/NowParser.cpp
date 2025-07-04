
// Generated from ./NowParser.g4 by ANTLR 4.13.1


#include "NowParserListener.h"
#include "NowParserVisitor.h"

#include "NowParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct NowParserStaticData final {
  NowParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  NowParserStaticData(const NowParserStaticData&) = delete;
  NowParserStaticData(NowParserStaticData&&) = delete;
  NowParserStaticData& operator=(const NowParserStaticData&) = delete;
  NowParserStaticData& operator=(NowParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag nowparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
NowParserStaticData *nowparserParserStaticData = nullptr;

void nowparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (nowparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(nowparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<NowParserStaticData>(
    std::vector<std::string>{
      "prog", "expr", "timeStamp"
    },
    std::vector<std::string>{
      "", "", "", "'func'", "'event'", "'when'", "'every'", "'after'", "'wait'", 
      "'on'", "'if'", "'while'", "'break'", "'RETURN'", "'int'", "'float'", 
      "'char'", "'string'", "'ms'", "'sec'", "'min'", "'hr'", "'+'", "'-'", 
      "'*'", "'/'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "NUMBER", "IDENTIFIER", "FUNC", "EVENT", "WHEN", "EVERY", "AFTER", 
      "WAIT", "ON", "IF", "WHILE", "BREAK", "RETURN", "INT", "FLOAT", "CHAR", 
      "STRING", "MS", "SEC", "MIN", "HR", "PLUS", "MINUS", "MUL", "DIV", 
      "LPAREN", "RPAREN", "COMMNET", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,30,41,2,0,7,0,2,1,7,1,2,2,7,2,1,0,1,0,1,0,5,0,10,8,0,10,0,12,0,13,
  	9,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,21,8,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,29,
  	8,1,10,1,12,1,32,9,1,1,2,4,2,35,8,2,11,2,12,2,36,1,2,1,2,1,2,0,1,2,3,
  	0,2,4,0,2,1,0,24,25,1,0,22,23,42,0,11,1,0,0,0,2,20,1,0,0,0,4,34,1,0,0,
  	0,6,7,3,2,1,0,7,8,5,29,0,0,8,10,1,0,0,0,9,6,1,0,0,0,10,13,1,0,0,0,11,
  	9,1,0,0,0,11,12,1,0,0,0,12,1,1,0,0,0,13,11,1,0,0,0,14,15,6,1,-1,0,15,
  	21,5,14,0,0,16,17,5,26,0,0,17,18,3,2,1,0,18,19,5,27,0,0,19,21,1,0,0,0,
  	20,14,1,0,0,0,20,16,1,0,0,0,21,30,1,0,0,0,22,23,10,4,0,0,23,24,7,0,0,
  	0,24,29,3,2,1,5,25,26,10,3,0,0,26,27,7,1,0,0,27,29,3,2,1,4,28,22,1,0,
  	0,0,28,25,1,0,0,0,29,32,1,0,0,0,30,28,1,0,0,0,30,31,1,0,0,0,31,3,1,0,
  	0,0,32,30,1,0,0,0,33,35,5,1,0,0,34,33,1,0,0,0,35,36,1,0,0,0,36,34,1,0,
  	0,0,36,37,1,0,0,0,37,38,1,0,0,0,38,39,5,19,0,0,39,5,1,0,0,0,5,11,20,28,
  	30,36
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  nowparserParserStaticData = staticData.release();
}

}

NowParser::NowParser(TokenStream *input) : NowParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

NowParser::NowParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  NowParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *nowparserParserStaticData->atn, nowparserParserStaticData->decisionToDFA, nowparserParserStaticData->sharedContextCache, options);
}

NowParser::~NowParser() {
  delete _interpreter;
}

const atn::ATN& NowParser::getATN() const {
  return *nowparserParserStaticData->atn;
}

std::string NowParser::getGrammarFileName() const {
  return "NowParser.g4";
}

const std::vector<std::string>& NowParser::getRuleNames() const {
  return nowparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& NowParser::getVocabulary() const {
  return nowparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView NowParser::getSerializedATN() const {
  return nowparserParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

NowParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<NowParser::ExprContext *> NowParser::ProgContext::expr() {
  return getRuleContexts<NowParser::ExprContext>();
}

NowParser::ExprContext* NowParser::ProgContext::expr(size_t i) {
  return getRuleContext<NowParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> NowParser::ProgContext::NEWLINE() {
  return getTokens(NowParser::NEWLINE);
}

tree::TerminalNode* NowParser::ProgContext::NEWLINE(size_t i) {
  return getToken(NowParser::NEWLINE, i);
}


size_t NowParser::ProgContext::getRuleIndex() const {
  return NowParser::RuleProg;
}

void NowParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NowParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void NowParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NowParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}


std::any NowParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NowParserVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

NowParser::ProgContext* NowParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, NowParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(11);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == NowParser::INT

    || _la == NowParser::LPAREN) {
      setState(6);
      expr(0);
      setState(7);
      match(NowParser::NEWLINE);
      setState(13);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

NowParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* NowParser::ExprContext::INT() {
  return getToken(NowParser::INT, 0);
}

tree::TerminalNode* NowParser::ExprContext::LPAREN() {
  return getToken(NowParser::LPAREN, 0);
}

std::vector<NowParser::ExprContext *> NowParser::ExprContext::expr() {
  return getRuleContexts<NowParser::ExprContext>();
}

NowParser::ExprContext* NowParser::ExprContext::expr(size_t i) {
  return getRuleContext<NowParser::ExprContext>(i);
}

tree::TerminalNode* NowParser::ExprContext::RPAREN() {
  return getToken(NowParser::RPAREN, 0);
}

tree::TerminalNode* NowParser::ExprContext::MUL() {
  return getToken(NowParser::MUL, 0);
}

tree::TerminalNode* NowParser::ExprContext::DIV() {
  return getToken(NowParser::DIV, 0);
}

tree::TerminalNode* NowParser::ExprContext::PLUS() {
  return getToken(NowParser::PLUS, 0);
}

tree::TerminalNode* NowParser::ExprContext::MINUS() {
  return getToken(NowParser::MINUS, 0);
}


size_t NowParser::ExprContext::getRuleIndex() const {
  return NowParser::RuleExpr;
}

void NowParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NowParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void NowParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NowParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


std::any NowParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NowParserVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


NowParser::ExprContext* NowParser::expr() {
   return expr(0);
}

NowParser::ExprContext* NowParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  NowParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  NowParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, NowParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(20);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case NowParser::INT: {
        setState(15);
        match(NowParser::INT);
        break;
      }

      case NowParser::LPAREN: {
        setState(16);
        match(NowParser::LPAREN);
        setState(17);
        expr(0);
        setState(18);
        match(NowParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(30);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(28);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(22);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(23);
          _la = _input->LA(1);
          if (!(_la == NowParser::MUL

          || _la == NowParser::DIV)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(24);
          expr(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(25);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(26);
          _la = _input->LA(1);
          if (!(_la == NowParser::PLUS

          || _la == NowParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(27);
          expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(32);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TimeStampContext ------------------------------------------------------------------

NowParser::TimeStampContext::TimeStampContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* NowParser::TimeStampContext::SEC() {
  return getToken(NowParser::SEC, 0);
}

std::vector<tree::TerminalNode *> NowParser::TimeStampContext::NUMBER() {
  return getTokens(NowParser::NUMBER);
}

tree::TerminalNode* NowParser::TimeStampContext::NUMBER(size_t i) {
  return getToken(NowParser::NUMBER, i);
}


size_t NowParser::TimeStampContext::getRuleIndex() const {
  return NowParser::RuleTimeStamp;
}

void NowParser::TimeStampContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NowParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTimeStamp(this);
}

void NowParser::TimeStampContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NowParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTimeStamp(this);
}


std::any NowParser::TimeStampContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NowParserVisitor*>(visitor))
    return parserVisitor->visitTimeStamp(this);
  else
    return visitor->visitChildren(this);
}

NowParser::TimeStampContext* NowParser::timeStamp() {
  TimeStampContext *_localctx = _tracker.createInstance<TimeStampContext>(_ctx, getState());
  enterRule(_localctx, 4, NowParser::RuleTimeStamp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(33);
      match(NowParser::NUMBER);
      setState(36); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == NowParser::NUMBER);
    setState(38);
    match(NowParser::SEC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool NowParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool NowParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void NowParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  nowparserParserInitialize();
#else
  ::antlr4::internal::call_once(nowparserParserOnceFlag, nowparserParserInitialize);
#endif
}
