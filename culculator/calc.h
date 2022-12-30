#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>

class Calculator {
 public:
  static int Calculate(const std::string&);

 private:
  enum class TokenType {
    kUnknown,
    kConstant,
    kAbsolut,
    kUnaryMinus,
    kMultiple,
    kModule,
    kDivide,
    kPlus,
    kMinus,
    kOpenBracket,
    kCloseBracket
  };

  struct Token {
    TokenType type;
    int value{};

    Token();
    Token(const std::string& operation, bool is_unary_minus);
  };

  static int Priority(const Token&);
  static bool IsOperation(char);
  void StringToTokens(const std::string&);
  void ReversePolishNotation();

  std::vector<Token> tokens_;
};
