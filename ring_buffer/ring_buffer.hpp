#pragma once
#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity)
      : size_(0),
        first_(0),
        last_(0),
        capacity_(capacity),
        queue_(capacity, 0) {}

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    if (size_ == capacity_) {
      return false;
    }
    size_++;
    queue_[last_] = element;
    last_++;
    last_ %= capacity_;
    return true;
  }

  bool TryPop(int* element) {
    if (Empty()) {
      return false;
    }
    size_--;
    *element = queue_[first_];
    first_++;
    first_ %= capacity_;
    return true;
  }

 private:
  int size_;
  int first_;
  int last_;
  int capacity_;
  std::vector<int> queue_;
};