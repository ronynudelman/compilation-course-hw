#ifndef TOKENS_HANDLERS
#define TOKENS_HANDLERS


#include <string>

void handle_token(int token, bool& string_open);
void parse_char(std::string& c);
void print_token_info(const char* token_name, bool* string_open = nullptr);
//void handle_error(std::string error_msg);
void handle_error_char();
void handle_error_string_end();
void handle_error_undefined_escape();
void handle_error_unclosed_string();
void handle_error_undefined_escape_x();

#endif /* TOKENS_HANDLERS */
