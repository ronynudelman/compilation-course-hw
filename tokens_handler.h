#ifndef TOKENS_HANDLERS
#define TOKENS_HANDLERS


#include <string>


void handle_token(int token);
void parse_char(std::string& c);
void print_token_info(const char* token_name);
void handle_error(std::string error_msg);


#endif /* TOKENS_HANDLERS */
