lexer grammar NowLexer;

options {
    caseInsensitive = true;
}

/* COMPONENTS */
fragment DIGIT  : [0-9];
fragment LETTER : [A-Z];

// Complex components
NUMBER     : DIGIT+ ;
IDENTIFIER : LETTER+ DIGIT* LETTER*;

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
INT    : 'int' ;
FLOAT  : 'float' ;
CHAR   : 'char' ;
STRING : 'string' ;

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

/* BLANKS */
COMMNET : '//' ~[\r\n]* -> skip ;
NEWLINE : [\r\n]+ ;
WS      : [ \t]+ -> skip ;
