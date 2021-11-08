#include "tokens.hpp"
#include "tokens_handler.h"
#include <iostream>
#include <string>
#include <sstream>



void handle_token(int token, bool& string_is_open) {
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
		case COMMENT:
			print_token_info("COMMENT");
			break;
		case ID:
			print_token_info("ID");
			break;
		case NUM:
			print_token_info("NUM");
			break;
		case STRING:
			print_token_info("STRING", &string_is_open);
			break;
		case ERROR_CHAR:
			handle_error_char();
			break;
		case ERROR_STRING_END:
			handle_error_string_end();
			break;
		case ERROR_UNDEFINED_ESCAPE:
			handle_error_undefined_escape();
			break;
		case ERROR_UNCLOSED_STRING:
			handle_error_unclosed_string();
			break;
		case ERROR_UNDEFINED_ESCAPE_X:
			handle_error_undefined_escape_x();
		default:
			std::cout << "Undefined error !!!" << std::endl;
			exit(0);
	}
}


void parse_char(std::string& c) {
	size_t current_pos = 0;
	if ((current_pos = c.find("\\\\")) != std::string::npos) {
		c.replace(current_pos, 2, 1, '\\');
	} else if ((current_pos = c.find("\\\"")) != std::string::npos) {
		c.replace(current_pos, 2, 1, '\"');
	} else if ((current_pos = c.find("\\n")) != std::string::npos) {
		c.replace(current_pos, 2, 1, '\n');
	} else if ((current_pos = c.find("\\r")) != std::string::npos) {
		c.replace(current_pos, 2, 1, '\r');
	} else if ((current_pos = c.find("\\t")) != std::string::npos) {
		c.replace(current_pos, 2, 1, '\t');
	} else if ((current_pos = c.find("\\0")) != std::string::npos) {
		c.replace(current_pos, 2, 1, '\0');
	} else if ((current_pos = c.find("\\x")) != std::string::npos) {
		std::string hex_str = c.substr(current_pos + 2, 2);
		std::istringstream hex_stream(hex_str);
		int hex_int;
		hex_stream >> std::hex >> hex_int;
		char hex_char = char(hex_int);
		c.replace(current_pos, 4, 1, hex_char);
	}
}


void print_token_info(const char* token_name, bool* string_is_open) {
	static std::string current_str;
	if (std::string(token_name) == std::string("COMMENT")) {
		std::cout << yylineno << " " << token_name << " " << "//" << "\n";
	} else if (std::string(token_name) == std::string("STRING")) {
		if (std::string(yytext) == std::string("\"")) {
			if (*string_is_open) {
				std::cout << yylineno << " " << token_name << " " << current_str << "\n";
				current_str.clear();
				*string_is_open = false;
			} else {
				*string_is_open = true;
			}
		} else {
			std::string current_char(yytext);
			parse_char(current_char);
			current_str += current_char;
		}
	} else {
		std::cout << yylineno << " " << token_name << " " << yytext << "\n";
	}
}


void handle_error_char() {
	std::cout << "Error " << yytext << "\n";
	exit(0);
}

void handle_error_string_end() {
	std::cout << "Error unclosed string" << "\n";
	exit(0);
}


void handle_error_undefined_escape(){
	std::string error_sequence(yytext);
	std::cout << "Error undefined escape sequence " << error_sequence[1] << "\n";
	exit(0);
}

void handle_error_unclosed_string() {
	std::cout << "Error unclosed string" << "\n";
	exit(0);
}

void handle_error_undefined_escape_x() {
	std::string error_sequence(yytext);
	error_sequence.erase(0,1);
	std::cout << "Error undefined escape sequence " << error_sequence << "\n";
	exit(0);
}



	
	
