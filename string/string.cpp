#include "string.hpp"

String::String() { size_ = capacity_ = 0; }

String::String(size_t size, char character)
    : str_(new char[size + 1]), size_(size), capacity_(size) {
  memset(str_, character, size);
  str_[size_] = '\0';
}

String::String(const char* line) {
  size_ = strlen(line);
  capacity_ = size_;
  str_ = new char[size_ + 1];
  memcpy(str_, line, size_);
  str_[size_] = '\0';
}

String::String(const String& other) { *this = other; }

String& String::operator=(const String& line) {
  size_ = line.size_;
  capacity_ = line.capacity_;
  delete[] str_;
  str_ = new char[capacity_ + 1];
  if (line.str_ != nullptr) {
    memcpy(str_, line.str_, size_);
  }
  str_[size_] = '\0';
  return *this;
}

void String::Clear() { size_ = 0; }

void String::PushBack(char character) {
  if (size_ >= capacity_) {
    Reserve(2 * size_ + 1);
  }
  str_[size_++] = character;
  str_[size_] = '\0';
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  str_[size_--] = '\0';
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    Reserve(new_size);
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  size_t siz = size_;
  Resize(new_size);
  for (size_t i = size_ - 1; i >= siz; --i) {
    str_[i] = character;
  }
  str_[size_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (new_cap <= capacity_) {
    return;
  }
  char* copy = new char[new_cap + 1];
  if (str_ != nullptr) {
    memcpy(copy, str_, size_);
  }
  copy[size_] = '\0';
  delete[] str_;
  str_ = copy;
  capacity_ = new_cap;
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    char* copy = new char[size_ + 1];
    memcpy(copy, str_, size_);
    copy[size_] = '\0';
    delete[] str_;
    str_ = copy;
    capacity_ = size_;
  }
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

char& String::operator[](size_t index) { return str_[index]; }

const char& String::operator[](size_t index) const { return str_[index]; }

char& String::Front() { return str_[0]; }

const char& String::Front() const { return str_[0]; }

char& String::Back() { return str_[size_ - 1]; }

const char& String::Back() const { return str_[size_ - 1]; }

char* String::Data() { return &str_[0]; }

const char* String::Data() const { return &str_[0]; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

String& String::operator+=(const String& line) {
  String copy = line;
  Reserve(size_ + copy.Size());
  memcpy(str_ + size_, copy.str_, copy.Size());
  size_ += copy.Size();
  str_[size_] = '\0';
  return *this;
}

String String::operator+(const String& line) const {
  String copy("");
  copy += *this;
  copy += line;
  return copy;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> result;
  String curr("");
  for (size_t i = 0; i < size_; ++i) {
    if (i + delim.Size() <= size_) {
      String copy(delim.Size());
      for (size_t j = 0; j < delim.Size(); ++j) {
        copy.str_[j] = str_[i + j];
      }
      if (copy == delim) {
        i += delim.Size() - 1;
        curr.str_[curr.size_] = '\0';
        result.push_back(curr);
        curr.Clear();
        continue;
      }
    }
    curr.PushBack(str_[i]);
  }
  curr.str_[curr.size_] = '\0';
  result.push_back(curr);
  return result;
}

String String::Join(const std::vector<String>& strings) {
  String result("");
  for (size_t i = 0; i < strings.size(); ++i) {
    for (size_t j = 0; j < strings[i].Size(); ++j) {
      result.PushBack(strings[i][j]);
    }
    if (i < strings.size() - 1) {
      result += str_;
    }
  }
  return result;
}

String::~String() { delete[] str_; }

bool operator==(const String& lft, const String& rgt) {
  if (lft.Size() != rgt.Size()) {
    return false;
  }
  for (size_t i = 0; i < lft.Size(); ++i) {
    if (lft[i] != rgt[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& lft, const String& rgt) { return !(lft == rgt); }

bool operator<(const String& lft, const String& rgt) {
  size_t min = lft.Size();
  if (rgt.Size() < min) {
    min = rgt.Size();
  }
  for (size_t i = 0; i < min; i++) {
    if (lft[i] < rgt[i]) {
      return true;
    }
    if (lft[i] > rgt[i]) {
      return false;
    }
  }
  return lft.Size() < rgt.Size();
}

bool operator>(const String& lft, const String& rgt) { return !(lft <= rgt); }

bool operator<=(const String& lft, const String& rgt) {
  return (lft < rgt || lft == rgt);
}

bool operator>=(const String& lft, const String& rgt) { return !(lft < rgt); }

String operator*(const String& line, size_t n) {
  int num = 0;
  String result(line.Size() * n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < line.Size(); ++j) {
      result[num++] = line[j];
    }
  }
  return result;
}

String& String::operator*=(size_t n) {
  String copy = *this;
  copy = copy * n;
  Swap(copy);
  return *this;
}

std::istream& operator>>(std::istream& input, String& line) {
  char character;
  line.Clear();
  while (input >> character) {
    line.PushBack(character);
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, const String& line) {
  for (size_t i = 0; i < line.Size(); ++i) {
    output << line[i];
  }
  return output;
}