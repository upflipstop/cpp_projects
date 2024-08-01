#pragma once

#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

#include "AbstractToken.hpp"
#include "BracketToken.hpp"
#include "Error.hpp"
#include "OperandToken.hpp"
#include "OperatorToken.hpp"

namespace calculator {
std::map<std::string, int> priority = {{"(", 0}, {"+", 1}, {"-", 1}, {"*", 2}};
template <typename T>
class ExprInPolishNotation {
 public:
  ExprInPolishNotation(const std::string& expr) {
    std::vector<std::string> res = ExprOnVector(expr);
    std::stack<std::string> operators;
    for (size_t ind = 0; ind < res.size(); ++ind) {
      if (res[ind] == "(") {
        operators.push(res[ind]);
      } else if (res[ind] == ")") {
        while (operators.top() != "(") {
          const std::string kTmp = operators.top();
          tokens_.push_back(new AbstractToken(kTmp));
          operators.pop();
        }
        operators.pop();
      } else if (res[ind] == "+" || res[ind] == "-" || res[ind] == "*" ||
                 res[ind] == "/") {
        while (!operators.empty() &&
               priority[operators.top()] >= priority[res[ind]]) {
          const std::string kTmp = operators.top();
          tokens_.push_back(new AbstractToken(kTmp));
          operators.pop();
        }
        operators.push(res[ind]);
      } else {
        const std::string kTmp = res[ind];
        tokens_.push_back(new AbstractToken(kTmp));
      }
    }
    while (!operators.empty()) {
      if (operators.top() == "(") {
        for (auto& token : tokens_) {
          delete token;
        }
        throw InvalidExpr();
      }
      const std::string kTmp = operators.top();
      tokens_.push_back(new AbstractToken(kTmp));
      operators.pop();
    }
  }
  const std::vector<AbstractToken*>& GetTokens() { return tokens_; }
  ~ExprInPolishNotation() {
    for (auto& token : tokens_) {
      delete token;
    }
  }

 private:
  static std::vector<std::string> ExprOnVector(const std::string& expr) {
    std::vector<std::string> res;
    std::set<std::string> operators = {"+", "-", "*", "/", "("};
    std::string tmp(0, ' ');
    for (size_t ind = 0; ind < expr.size(); ++ind) {
      if (expr[ind] == ' ') {
        continue;
      }
      if (expr[ind] == '(' || expr[ind] == '*' || expr[ind] == '/' ||
          expr[ind] == ')') {
        if (!tmp.empty()) {
          res.push_back(tmp);
          tmp = "";
        }
        tmp = expr[ind];
        res.push_back(tmp);
        tmp = "";
        continue;
      }
      if (expr[ind] == '+' || expr[ind] == '-') {
        if (!tmp.empty()) {
          res.push_back(tmp);
          tmp = "";
        }
        if (ind == 0 || res.back() == "(" || res.back() == "+" ||
            res.back() == "-" || res.back() == "*" || res.back() == "/") {
          tmp += expr[ind++];
        } else {
          tmp = expr[ind];
          res.push_back(tmp);
          tmp = "";
          continue;
        }
      }
      if (expr[ind] != '(' && expr[ind] != '+' && expr[ind] != '-' &&
          expr[ind] != '*' && expr[ind] != '/' && expr[ind] != ')') {
        tmp += expr[ind];
      }
    }
    if (!tmp.empty()) {
      res.push_back(tmp);
      tmp = "";
    }
    return res;
  }
  std::vector<AbstractToken*> tokens_;
};
}  // namespace calculator
