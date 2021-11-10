%{
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap

letter                                [a-zA-Z]
digit                                 [0-9]
string_open_close                     [\"]
string_printable_char                 [\t\x20-\x7E]
string_defined_escape_sequence        \\\\|\\\"|\\n|\\r|\\t|\\0|\\x[0-7][0-9A-F]
string_undefined_escape_sequence      \\.|\\\n|\\\r|\\x|\\x(.|\r\n)|\\x(.|\r\n)(.|\r\n)
string_unexpected_end                 [\n]
whitespace                            [ \t\n\r]

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

{string_open_close}                                 BEGIN(STRING_READ); return STRING;
<STRING_READ>{string_defined_escape_sequence}       return STRING;
<STRING_READ>{string_undefined_escape_sequence}     return ERROR_STRING_UNDEFINED_ESCAPE_SEQUENCE;
<STRING_READ>{string_unexpected_end}                return ERROR_STRING_UNEXPECTED_END;
<STRING_READ>{string_open_close}                    BEGIN(INITIAL); return STRING;
<STRING_READ>{string_printable_char}                return STRING;
<STRING_READ>.                                      return ERROR_UNDEFINED_LEXEME;

{whitespace}                                  ;
.                                             return ERROR_UNDEFINED_LEXEME;

%%
