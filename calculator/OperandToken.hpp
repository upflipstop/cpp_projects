#pragma once

#include <cstdlib>
#include <type_traits>

#include "AbstractToken.hpp"
namespace calculator {
template <typename T>
class OperandToken : public AbstractToken {
 public:
  OperandToken() = default;
  OperandToken(const std::string& str) : AbstractToken(str) {
    val_ = static_cast<T>(std::atof(str.data()));
  };
  OperandToken(const T& value) : val_(value) {}
  OperandToken& operator=(const T& value) {
    val_ = value;
    return *this;
  }
  const T& GetValue() const { return val_; }
  size_t GetType() const { return kType; }

 private:
  T val_ = 0;
  const size_t kType = 1;
};
}  // namespace calculator