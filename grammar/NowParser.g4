parser grammar NowParser;

options {
    tokenVocab = NowLexer;
}

prog:   (expr NEWLINE)* ;

expr:   expr (MUL|DIV) expr
    |   expr (PLUS|MINUS) expr
    |   INT
    |   LPAREN expr RPAREN
    ;

timeStamp: NUMBER + SEC ;
