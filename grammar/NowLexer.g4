lexer grammar NowLexer;

options {
    caseInsensitive = false;
}

/* RESERVED WORDS */
FUNC   : 'func' ;
EVENT  : 'event' ;
WHEN   : 'when' ;
EVERY  : 'every' ;
AFTER  : 'after' ;
WAIT   : 'wait' ;
ON     : 'on' ;
IF     : 'if' ;
WHILE  : 'while' ;
BREAK  : 'break' ;
RETURN : 'RETURN' ;

/* TYPES */
INT     : 'int' ;
FLOAT   : 'float' ;
CHAR    : 'char' ;
STRING  : 'string' ;
BOOLEAN : 'boolean' ;

// Time Stamps
MS  : 'ms' ;
SEC : 'sec' ;
MIN : 'min' ;
HR  : 'hr' ;

/* SYMBOLS */
PLUS  : '+' ;
MINUS : '-' ;
MUL   : '*' ;
DIV   : '/' ;

LPAREN : '(' ;
RPAREN : ')' ;

LBRACE : '{' ;
RBRACE : '}' ;

SEMICOLON : ';' ;

// OPERATORS
ASSING_OP : '=' ;

NOT_EQ_OP : '!=' ;

EQ_OP : '==' ;
LT_OP : '<' ;
GT_OP : '>' ;
LE_OP : '<=' ;
GE_OP : '>=' ;


// BOOLEAN OPERATORS
TRUE  : 'true' | 'TRUE' ;
FALSE : 'false' | 'FALSE' ; 

/* COMPONENTS */
fragment DIGIT  : [0-9] ;
fragment LETTER : [a-zA-Z] ;

// Complex components
IDENTIFIER     : LETTER+ DIGIT* LETTER* ;
NUMBER_LITERAL : DIGIT+ ;
FLOAT_LITERAL  : DIGIT+ '.' DIGIT+ ;
CHAR_LITERAL   : '\'' LETTER '\'' ;
STRING_LITERAL : '"' LETTER+ '"' ;

/* BLANKS */
COMMNET : '//' ~[\r\n]* -> skip ;
NEWLINE : [\r\n]+ -> skip ;
WS      : [ \t]+ -> skip ;
