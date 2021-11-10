#ifndef TOKENS_HANDLERS
#define TOKENS_HANDLERS


#include <string>
#include "tokens.hpp"


class Token {
private:
  TokenType token_type;
public:
  Token(TokenType token_type) : token_type(token_type) {}
  virtual void handle();
};


class CommentToken : public Token {
public:
  CommentToken(TokenType token_type = COMMENT) : Token(token_type) {}
  void handle() override;
};


class StringToken : public Token {
private:
  static bool is_open;
  static std::string current_str;
public:
  StringToken(TokenType token_type = STRING) : Token(token_type) {}
  void handle() override;
  static void parse_lexeme(std::string& c);
  static void open();
  static void close();
  static void check_string_is_open();
};


namespace Error {
  void undefined_lexeme();
  namespace String {
    void unexpected_end();
    void undefined_escape_sequence();
  }
}


void get_tokens();
Token* parse_token(int token_num);
void handle_error(int error_num);


#endif /* TOKENS_HANDLERS */
