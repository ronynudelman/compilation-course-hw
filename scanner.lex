%{
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
lparen        [(]
rparen        [)]
lbrace        [{]
rbrace        [}]
relop         ==|!=|<|>|<=|>=
binop         [\+\-\*/]
whitespace    [ \t\n\r]

%%

void          return VOID;
int           return INT;
byte          return BYTE;
b             return B;
bool          return BOOL;
and           return AND;
or            return OR;
not           return NOT;
true          return TRUE;
false         return FALSE;
return        return RETURN;
if            return IF;
else          return ELSE;
while         return WHILE;
break         return BREAK;
continue      return CONTINUE;
;             return SC;
,             return COMMA;
{lparen}      return LPAREN;
{rparen}      return RPAREN;
{lbrace}      return LBRACE;
{rbrace}      return RBRACE;
=             return ASSIGN;
{relop}       return RELOP;
{binop}       return BINOP;
{whitespace}  ;

%%
