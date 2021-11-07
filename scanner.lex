%{
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
letter        [a-zA-Z]
digit         [0-9]
printable     [\x20-\x7E]
allowed       \\\\|\\\"|\\n|\\r|\\t|\\0|\\x[0-7][0-9A-F]
forbidden     [\\\n\r]
whitespace    [ \t\n\r]
%x STRING_READ

%%

void                                          return VOID;
int                                           return INT;
byte                                          return BYTE;
b                                             return B;
bool                                          return BOOL;
and                                           return AND;
or                                            return OR;
not                                           return NOT;
true                                          return TRUE;
false                                         return FALSE;
return                                        return RETURN;
if                                            return IF;
else                                          return ELSE;
while                                         return WHILE;
break                                         return BREAK;
continue                                      return CONTINUE;
;                                             return SC;
,                                             return COMMA;
\(                                            return LPAREN;
\)                                            return RPAREN;
\{                                            return LBRACE;
\}                                            return RBRACE;
=                                             return ASSIGN;
==|!=|<|>|<=|>=                               return RELOP;
[\+\-\*\/]                                    return BINOP;
\/\/[^\n\r]*                                  return COMMENT;
{letter}({letter}|{digit})*                   return ID;
0|[1-9]{digit}*                               return NUM;

\"                                            BEGIN(STRING_READ);
<STRING_READ>{allowed}                        return STRING;
<STRING_READ>{forbidden}                      BEGIN(INITIAL); return ERROR;
<STRING_READ>\"                               BEGIN(INITIAL); return STRING;
<STRING_READ>{printable}                      return STRING;
<STRING_READ>.                                BEGIN(INITIAL); return ERROR;

{whitespace}                                  ;
.                                             return ERROR;

%%
