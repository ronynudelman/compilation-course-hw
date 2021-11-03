#include "tokens.hpp"
#include "tokens_handler.h"
#include <iostream>


int main() {
	int token;
	while(token = yylex()) {
		handle_token(token);
	}
	return 0;
}
