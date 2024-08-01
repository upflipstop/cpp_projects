#pragma once

#include <functional>
#include <map>

#include "AbstractToken.hpp"
#include "OperandToken.hpp"

namespace calculator {
template <typename T, bool IsBin>
class OperatorToken : public AbstractToken {
 public:
  OperatorToken(const std::string& token) : AbstractToken(token) {
    if (IsBin) {
      if (token[0] == '+' || token[0] == '-') {
        import_ = 1;
      } else {
        import_ = 2;
      }
    } else {
      import_ = 3;
      kType_ = 3;
    }
  }
  bool IsBinary() const { return IsBin; }
  T Calculate(OperandToken<T>& lhs, OperandToken<T>& rhs) {
    return bin_operator_[token_line[0]](lhs, rhs);
  }
  T Calculate(OperandToken<T>& operand) {
    return unr_operator_[token_line[0]](operand);
  }

  size_t GetPriority() const { return import_; }
  size_t GetType() const { return kType_; }

 private:
  std::map<char, std::function<T(OperandToken<T>&, OperandToken<T>&)>>
      bin_operator_ = {{'+',
                        [](OperandToken<T>& lhs, OperandToken<T>& rhs) {
                          return lhs.GetValue() + rhs.GetValue();
                        }},
                       {'-',
                        [](OperandToken<T>& lhs, OperandToken<T>& rhs) {
                          return lhs.GetValue() - rhs.GetValue();
                        }},
                       {'*',
                        [](OperandToken<T>& lhs, OperandToken<T>& rhs) {
                          return lhs.GetValue() * rhs.GetValue();
                        }},
                       {'/', [](OperandToken<T>& lhs, OperandToken<T>& rhs) {
                          return lhs.GetValue() / rhs.GetValue();
                        }}};

  std::map<char, std::function<T(OperandToken<T>&)>> unr_operator_ = {
      {'+', [](OperandToken<T>& operand) { return operand.GetValue(); }},
      {'-', [](OperandToken<T>& operand) { return operand.GetValue() * -1; }},
  };

  size_t kType_ = 2;
  size_t import_;
};
}  // namespace calculator