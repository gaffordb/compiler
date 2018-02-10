#ifndef LEX_H
#define LEX_H

union TokenData {
  char ch;
  float f;
  int i;
};
enum TokenType {
  tlparen, trparen, tplus, tfloat, tint
};

class Token {
public:
  TokenType type;
  TokenData data;

  //constructor for char-based tokens
  Token(TokenType t, char ch);

  //constructor for int-based tokens
  Token(TokenType t, int n);

  //constructor for float-based tokens
  Token(TokenType t, float f);

  friend std::ostream& operator<<(std::ostream &strm, Token const& token);

  static std::shared_ptr<std::vector<Token> > lex(std::ifstream& in);
  friend std::ostream& operator<<(std::ostream &strm, Token const& token);
};

#endif
