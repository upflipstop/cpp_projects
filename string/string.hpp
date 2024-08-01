#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class String {
 private:
  char* str_ = nullptr;
  size_t size_;
  size_t capacity_;

 public:
  String();

  String(size_t size, char character = '?');

  String(const char* line);

  String(const String& other);

  String& operator=(const String& line);

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, char character);

  void Reserve(size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char& operator[](size_t index);

  const char& operator[](size_t index) const;

  char& Front();

  const char& Front() const;

  char& Back();

  const char& Back() const;

  char* Data();

  const char* Data() const;

  bool Empty() const;

  size_t Size() const;

  size_t Capacity() const;

  String operator+(const String& line) const;

  String& operator+=(const String& line);

  String& operator*=(size_t n);

  std::vector<String> Split(const String& delim = " ");

  String Join(const std::vector<String>& strings);

  ~String();
};

String operator*(const String& line, size_t n);

bool operator==(const String& lft, const String& rgt);

bool operator!=(const String& lft, const String& rgt);

bool operator<(const String& lft, const String& rgt);

bool operator>(const String& lft, const String& rgt);

bool operator<=(const String& lft, const String& rgt);

bool operator>=(const String& lft, const String& rgt);

std::istream& operator>>(std::istream& input, String& line);

std::ostream& operator<<(std::ostream& output, const String& line);