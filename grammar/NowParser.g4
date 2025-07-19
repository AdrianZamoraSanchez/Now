parser grammar NowParser;

options {
  tokenVocab = NowLexer;
}

program: stmt* ;

stmt: conditional	 	# stmtConditional
	| timeBlock 		# stmtTimeBlock
	| declaration		# stmtDeclaration
	| assign			# stmtAssign
	;

timeBlock
  : timeStamp LBRACE stmt* RBRACE
  ;

timeStamp
  : NUMBER_LITERAL MS	# msTimeStamp
  | NUMBER_LITERAL SEC	# secTimeStamp
  | NUMBER_LITERAL MIN 	# minTimeStamp
  | NUMBER_LITERAL HR	# hrTimeStamp
  ;

conditional: IF LPAREN comparison RPAREN LBRACE stmt* RBRACE ;  

comparison: operand comparationOperator operand ;

comparationOperator: EQ_OP 
				   | LT_OP 
				   | GT_OP 
				   | LE_OP 
				   | GE_OP 
				   | NOT_EQ_OP 
				   ;

operand
    : literal		# opLiteral
    | IDENTIFIER	# opIdentifier
    | expr			# opExpr
    ;

expr
  : expr op=(MUL|DIV) expr		# mulDivExpr
  | expr op=(PLUS|MINUS) expr	# addSubExpr
  | NUMBER_LITERAL			# numExpr
  | LPAREN expr RPAREN		# parenExpr
  ;

booleanLiteral : TRUE | FALSE ;

literal: NUMBER_LITERAL		# literalNumber
	   | FLOAT_LITERAL		# literalFloat
	   | STRING_LITERAL		# literalString
	   | CHAR_LITERAL		# literalChar
	   | booleanLiteral		# literalBool
	   ;

type: INT | FLOAT | STRING | CHAR | BOOLEAN ;

declaration: type IDENTIFIER SEMICOLON						# declarationSimple
		   | type IDENTIFIER ASSING_OP operand SEMICOLON	# declarationAssing
		   ;

assign: IDENTIFIER ASSING_OP operand SEMICOLON ;
