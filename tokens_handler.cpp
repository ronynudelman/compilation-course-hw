#include "tokens_handler.h"
#include <iostream>


void handle_token(int token) {
	switch (token) {
		case VOID:
			print_token_info("VOID");
			break;
		case INT:
			print_token_info("INT");
			break;
		case BYTE:
			print_token_info("BYTE");
			break;
		case B:
			print_token_info("B");
			break;
		case BOOL:
			print_token_info("BOOL");
			break;
		case AND:
			print_token_info("AND");
			break;
		case OR:
			print_token_info("OR");
			break;
		case NOT:
			print_token_info("NOT");
			break;
		case TRUE:
			print_token_info("TRUE");
			break;
		case FALSE:
			print_token_info("FALSE");
			break;
		case RETURN:
			print_token_info("RETURN");
			break;
		case IF:
			print_token_info("IF");
			break;
		case ELSE:
			print_token_info("ELSE");
			break;
		case WHILE:
			print_token_info("WHILE");
			break;
		case BREAK:
			print_token_info("BREAK");
			break;
		case CONTINUE:
			print_token_info("CONTINUE");
			break;
		case SC:
			print_token_info("SC");
			break;
		case COMMA:
			print_token_info("COMMA");
			break;
		case LPAREN:
			print_token_info("LPAREN");
			break;
		case RPAREN:
			print_token_info("RPAREN");
			break;
		case LBRACE:
			print_token_info("LBRACE");
			break;
		case RBRACE:
			print_token_info("RBRACE");
			break;
		case ASSIGN:
			print_token_info("ASSIGN");
			break;
		case RELOP:
			print_token_info("RELOP");
			break;
		case BINOP:
			print_token_info("BINOP");
			break;
		default:
			handle_error();
	}
}


void print_token_info(const char* token_name) {
	std::cout << yylineno << " " << token_name << " " << yytext << "\n";
}


void handle_error() {
	std::cout << "ERROR" << "\n";
	exit(0);
}
