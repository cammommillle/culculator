#include "calc.h"

Calculator::Token::Token() {
  type = TokenType::kUnknown;
}

Calculator::Token::Token(const std::string& operation,
                         const bool is_unary_minus = false) {
  value = 0;
  if (operation == "(") {
    type = TokenType::kOpenBracket;
  } else if (operation == ")") {
    type = TokenType::kCloseBracket;
  } else if (operation == "+") {
    type = TokenType::kPlus;
  } else if (operation == "*") {
    type = TokenType::kMultiple;
  } else if (operation == "/") {
    type = TokenType::kDivide;
  } else if (operation == "%") {
    type = TokenType::kModule;
  } else if (operation == "abs") {
    type = TokenType::kAbsolut;
  } else if (operation == "-") {
    if (is_unary_minus) {
      type = TokenType::kUnaryMinus;
    } else {
      type = TokenType::kMinus;
    }
  } else {
    type = TokenType::kConstant;
    value = std::stoi(operation);
  }
}

int Calculator::Priority(const Token& token) {
  switch (token.type) {
    case TokenType::kAbsolut: { return 4; }
    case TokenType::kUnaryMinus: { return 3; }
    case TokenType::kMultiple:
    case TokenType::kDivide:
    case TokenType::kModule: { return 2; }
    case TokenType::kPlus:
    case TokenType::kMinus: { return 1; }
    case TokenType::kConstant:
    case TokenType::kUnknown:
    case TokenType::kOpenBracket:
    case TokenType::kCloseBracket: { return -1; }
  }
  return -1;
}

bool Calculator::IsOperation(const char chr) {
  return (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '%');
}

void Calculator::StringToTokens(const std::string& expression) {
  int pos = 0;
  bool next_may_be_unary = true;
  while (pos < expression.length()) {
    std::string current;
    bool is_unary_minus = false;
    if (expression.at(pos) == ' ') {
      pos++;
      continue;
    }
    if (std::isdigit(expression.at(pos))) {
      while (pos < expression.length() && std::isdigit(expression.at(pos))) {
        current += expression.at(pos);
        pos++;
      }
      next_may_be_unary = false;
    } else if (expression.at(pos) == 'a') {
      current = "abs";
      pos += 3;
    } else {
      current = expression.at(pos);
      if (current == "-") {
        if (next_may_be_unary) {
          is_unary_minus = true;
        }
      }
      if (Calculator::IsOperation(expression.at(pos))
          || expression.at(pos) == '(') {
        next_may_be_unary = true;
      }
      pos++;
    }
    Token token(current, is_unary_minus);
    tokens_.push_back(token);
  }
}

void Calculator::ReversePolishNotation() {
  // because always input_pos >= output_pos we can use only one vector tokens_
  int input_pos = 0;
  int output_pos = 0;
  std::stack<Token> operations_stack;

  while (input_pos < tokens_.size()) {
    Token curr_token = tokens_.at(input_pos);
    input_pos++;
    if (curr_token.type == TokenType::kConstant) {
      tokens_.at(output_pos) = curr_token;
      output_pos++;
    } else if (curr_token.type == TokenType::kUnaryMinus
        || curr_token.type == TokenType::kOpenBracket) {
      operations_stack.push(curr_token);
    } else if (curr_token.type == TokenType::kCloseBracket) {
      while (operations_stack.top().type != TokenType::kOpenBracket) {
        tokens_.at(output_pos) = operations_stack.top();
        output_pos++;
        operations_stack.pop();
      }
      operations_stack.pop();
    } else {
      while (!operations_stack.empty()
          && Priority(operations_stack.top()) >= Priority(curr_token)) {
        tokens_.at(output_pos) = operations_stack.top();
        output_pos++;
        operations_stack.pop();
      }
      operations_stack.push(curr_token);
    }
  }
  while (!operations_stack.empty()) {
    tokens_.at(output_pos) = operations_stack.top();
    output_pos++;
    operations_stack.pop();
  }
  tokens_.resize(output_pos);
}

int Calculator::Calculate(const std::string& expression) {
  Calculator stack_machine;
  stack_machine.StringToTokens(expression);

  stack_machine.ReversePolishNotation();

  std::stack<int> values_stack;

  for (Token curr_token : stack_machine.tokens_) {
    if (curr_token.type == TokenType::kConstant) {  // TokenType::kConstant
      values_stack.push(curr_token.value);
    } else if (Priority(curr_token) >= 3) {  // unary operations
      int val = values_stack.top();
      values_stack.pop();

      switch (curr_token.type) {
        case TokenType::kAbsolut: {
          values_stack.push(std::abs(val));
          break;
        }
        case TokenType::kUnaryMinus: {
          values_stack.push(-1 * val);
          break;
        }
        default: { std::cerr << "Invalid unary operation\n"; }
      }
    } else {  // binary operations
      int val_2 = values_stack.top();
      values_stack.pop();
      int val_1 = values_stack.top();
      values_stack.pop();

      switch (curr_token.type) {
        case TokenType::kPlus : {
          values_stack.push(val_1 + val_2);
          break;
        }
        case TokenType::kMinus: {
          values_stack.push(val_1 - val_2);
          break;
        }
        case TokenType::kMultiple : {
          values_stack.push(val_1 * val_2);
          break;
        }
        case TokenType::kModule : {
          values_stack.push(val_1 % val_2);
          break;
        }
        case TokenType::kDivide : {
          values_stack.push(val_1 / val_2);
          break;
        }
        default: { std::cerr << "Invalid binary operation\n"; }
      }
    }
  }
  stack_machine.tokens_.clear();
  return values_stack.top();
}
