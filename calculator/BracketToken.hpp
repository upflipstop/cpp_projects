#pragma once

#include "AbstractToken.hpp"

namespace calculator {
class BracketToken : public AbstractToken {
 public:
  BracketToken(const std::string& token) : AbstractToken(token) {
    if (token[0] != '(') {
      open_ = false;
    }
  }
  bool IsOpening() const { return open_; }

  size_t GetType() const { return kType; }

 private:
  bool open_ = true;
  const size_t kType = 0;
};
}  // namespace calculator