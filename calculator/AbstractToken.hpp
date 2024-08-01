#pragma once

#include <string>
namespace calculator {
class AbstractToken {
 public:
  AbstractToken() = default;
  AbstractToken(AbstractToken&) = default;
  AbstractToken(const AbstractToken&) = default;

  explicit AbstractToken(const std::string& token) : token_line(token) {}

  const std::string& GetStringToken() const { return token_line; };

  virtual ~AbstractToken() = default;

  std::string token_line;
};
}  // namespace calculator