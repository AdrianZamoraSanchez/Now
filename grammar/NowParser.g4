parser grammar NowParser;

options {
  tokenVocab = NowLexer;
}

program: stmt* ;

stmt: conditionalExpr 
	| timedBlock 
	| declaration
	| assign
	;

timedBlock
  : timeStamp LBRACE stmt* RBRACE
  ;

timeStamp
  : NUMBER_LITERAL MS
  | NUMBER_LITERAL SEC
  | NUMBER_LITERAL MIN
  | NUMBER_LITERAL HR
  ;

conditionalExpr: IF LPAREN comparison RPAREN LBRACE stmt* RBRACE
    		   ;  

comparison: operand comparationOperator operand ;

comparationOperator: EQ_OP 
				   | LT_OP 
				   | GT_OP 
				   | LE_OP 
				   | GE_OP 
				   | NOT_EQ_OP 
				   ;

operand
    : literal
    | IDENTIFIER
    | expr
    ;

expr
  : expr (MUL|DIV) expr
  | expr (PLUS|MINUS) expr
  | NUMBER_LITERAL
  | LPAREN expr RPAREN
  ;

booleanLiteral : TRUE | FALSE ;

literal: NUMBER_LITERAL
	   | FLOAT_LITERAL
	   | STRING_LITERAL
	   | CHAR_LITERAL
	   | booleanLiteral
	   ;

type: INT | FLOAT | STRING | CHAR | BOOLEAN ;

declaration: type IDENTIFIER SEMICOLON
		   | type IDENTIFIER ASSING_OP operand SEMICOLON
		   ;

assign: IDENTIFIER ASSING_OP operand SEMICOLON ;
