#pragma once

#include "AbstractToken.hpp"
#include "Error.hpp"
#include "ExprInPolishNotation.hpp"
#include "OperandToken.hpp"
#include "OperatorToken.hpp"

namespace calculator {
template <typename T>
class Calculator {
 public:
  static T CalculateExpr(const std::string& expr) {
    ExprInPolishNotation<T> polish_expr(expr);
    const std::vector<AbstractToken*> kTokens = polish_expr.GetTokens();
    std::stack<AbstractToken*> val;
    for (AbstractToken* str : kTokens) {
      if (str->GetStringToken() == "+" || str->GetStringToken() == "-" ||
          str->GetStringToken() == "*" || str->GetStringToken() == "/") {
        OperandToken<T> rhs(val.top()->GetStringToken());
        AbstractToken* delete_tmp = val.top();
        val.pop();
        delete delete_tmp;
        OperandToken<T> lhs(val.top()->GetStringToken());
        delete_tmp = val.top();
        val.pop();
        delete delete_tmp;
        OperatorToken<T, true> oper(str->GetStringToken());
        T new_operand = oper.Calculate(lhs, rhs);
        OperandToken tmp_operand(new_operand);
        const std::string kTmpString = std::to_string(tmp_operand.GetValue());
        val.push(new AbstractToken(kTmpString));
      } else {
        val.push(new AbstractToken(str->GetStringToken()));
      }
    }
    if (val.size() != 1) {
      while (!val.empty()) {
        AbstractToken* delete_tmp = val.top();
        val.pop();
        delete delete_tmp;
      }
      throw InvalidExpr();
    }
    const std::string kAns = val.top()->GetStringToken();
    AbstractToken* delete_tmp = val.top();
    val.pop();
    delete delete_tmp;
    return static_cast<T>(std::stof(kAns));
  }
};
}  // namespace calculator