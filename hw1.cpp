#include "tokens.hpp"
#include "tokens_handler.h"
#include <iostream>

int main() {
	int token;
	bool string_is_open = false;
	while(token = yylex()) {
		std::cout << "got token: " << token << std::endl;
		handle_token(token, string_is_open);
	}
	if (string_is_open) {
		std::cout << "Error unclosed string" << "\n";
	}
	return 0;
}
