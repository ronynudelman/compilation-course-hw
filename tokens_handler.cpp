#include "tokens.hpp"
#include "tokens_handler.h"
#include <iostream>
#include <string>
#include <sstream>


bool StringToken::is_open = false;
std::string StringToken::current_str = std::string();


void Token::handle() {
	std::string token_name;
	switch (token_type) {
		case VOID:
			token_name = std::string("VOID");
			break;
		case INT:
			token_name = std::string("INT");
			break;
		case BYTE:
			token_name = std::string("BYTE");
			break;
		case B:
			token_name = std::string("B");
			break;
		case BOOL:
			token_name = std::string("BOOL");
			break;
		case AND:
			token_name = std::string("AND");
			break;
		case OR:
			token_name = std::string("OR");
			break;
		case NOT:
			token_name = std::string("NOT");
			break;
		case TRUE:
			token_name = std::string("TRUE");
			break;
		case FALSE:
			token_name = std::string("FALSE");
			break;
		case RETURN:
			token_name = std::string("RETURN");
			break;
		case IF:
			token_name = std::string("IF");
			break;
		case ELSE:
			token_name = std::string("ELSE");
			break;
		case WHILE:
			token_name = std::string("WHILE");
			break;
		case BREAK:
			token_name = std::string("BREAK");
			break;
		case CONTINUE:
			token_name = std::string("CONTINUE");
			break;
		case SC:
			token_name = std::string("SC");
			break;
		case COMMA:
			token_name = std::string("COMMA");
			break;
		case LPAREN:
			token_name = std::string("LPAREN");
			break;
		case RPAREN:
			token_name = std::string("RPAREN");
			break;
		case LBRACE:
			token_name = std::string("LBRACE");
			break;
		case RBRACE:
			token_name = std::string("RBRACE");
			break;
		case ASSIGN:
			token_name = std::string("ASSIGN");
			break;
		case RELOP:
			token_name = std::string("RELOP");
			break;
		case BINOP:
			token_name = std::string("BINOP");
			break;
		case ID:
			token_name = std::string("ID");
			break;
		case NUM:
			token_name = std::string("NUM");
			break;
		default:
			break;
	}
	std::cout << yylineno << " " << token_name << " " << yytext << "\n";
}


void CommentToken::handle() {
	std::cout << yylineno << " " << "COMMENT" << " " << "//" << "\n";
}


void StringToken::handle() {
	if (std::string(yytext) == std::string("\"")) {
		if (is_open) {
			std::cout << yylineno << " " << "STRING" << " " << current_str << "\n";
			current_str.clear();
			close();
		} else {
			open();
		}
	} else {
		std::string current_lexeme(yytext);
		parse_lexeme(current_lexeme);
		current_str += current_lexeme;
	}
}


void StringToken::parse_lexeme(std::string& lexeme) {
	size_t current_pos = 0;
	if ((current_pos = lexeme.find("\\\\")) != std::string::npos) {
		lexeme.replace(current_pos, 2, 1, '\\');
	} else if ((current_pos = lexeme.find("\\\"")) != std::string::npos) {
		lexeme.replace(current_pos, 2, 1, '\"');
	} else if ((current_pos = lexeme.find("\\n")) != std::string::npos) {
		lexeme.replace(current_pos, 2, 1, '\n');
	} else if ((current_pos = lexeme.find("\\r")) != std::string::npos) {
		lexeme.replace(current_pos, 2, 1, '\r');
	} else if ((current_pos = lexeme.find("\\t")) != std::string::npos) {
		lexeme.replace(current_pos, 2, 1, '\t');
	} else if ((current_pos = lexeme.find("\\0")) != std::string::npos) {
		lexeme.replace(current_pos, 2, 1, '\0');
	} else if ((current_pos = lexeme.find("\\x")) != std::string::npos) {
		std::string hex_str = lexeme.substr(current_pos + 2, 2);
		std::istringstream hex_stream(hex_str);
		int hex_int;
		hex_stream >> std::hex >> hex_int;
		char hex_char = char(hex_int);
		lexeme.replace(current_pos, 4, 1, hex_char);
	}
}


void StringToken::open() {
	is_open = true;
}


void StringToken::close() {
	is_open = false;
}


void StringToken::check_string_is_open() {
	if (is_open) {
		Error::String::unexpected_end();
	}
}


void Error::undefined_lexeme() {
	std::cout << "Error " << yytext << "\n";
}


void Error::String::unexpected_end() {
	std::cout << "Error unclosed string" << "\n";
}


void Error::String::undefined_escape_sequence() {
	std::string escape_sequence(yytext);
	escape_sequence.erase(0,1);
	std::cout << "Error undefined escape sequence " << escape_sequence << "\n";
}


void get_tokens() {
	Token* token = nullptr;
	bool string_is_open = false;
	int token_num = 0;;
	while (token_num = yylex()) {
		Token* token = parse_token(token_num);
		if (!token) {
			handle_error(token_num);
		}
		else {
			token->handle();
			delete token;
		}
	}
	StringToken::check_string_is_open();
}


Token* parse_token(int token_num) {
	if (token_num < 0) {
		return nullptr;
	} else if (token_num == STRING) {
		return new StringToken;
	} else if (token_num == COMMENT) {
		return new CommentToken;
	} else {
		return new Token(TokenType(token_num));
	}
}


void handle_error(int error_num) {
	switch (error_num) {
		case ERROR_UNDEFINED_LEXEME:
			Error::undefined_lexeme();
			break;
		case ERROR_STRING_UNEXPECTED_END:
			Error::String::unexpected_end();
			break;
		case ERROR_STRING_UNDEFINED_ESCAPE_SEQUENCE:
			Error::String::undefined_escape_sequence();
			break;
		default:
			break;
	}
	exit(0);
}
