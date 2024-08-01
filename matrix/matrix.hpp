#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() { array_.resize(N, std::vector<T>(M)); }

  Matrix(std::vector<std::vector<T> >& other) { array_ = other; }

  Matrix(T elem) {
    array_.resize(N, std::vector<T>(M));
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        array_[i][j] = elem;
      }
    }
  }

  T& operator()(const size_t kIndexI, const size_t kIndexJ) {
    return array_[kIndexI][kIndexJ];
  }

  const T& operator()(const size_t kIndexI, const size_t kIndexJ) const {
    return array_[kIndexI][kIndexJ];
  }

  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& rgh) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        array_[i][j] += rgh(i, j);
      }
    }
    return *this;
  }

  Matrix<N, M, T> operator+(const Matrix<N, M, T>& rgh) const {
    Matrix<N, M, T> tmp = *this;
    tmp += rgh;
    return tmp;
  }

  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& rgh) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        array_[i][j] -= rgh(i, j);
      }
    }
    return *this;
  }

  Matrix<N, M, T> operator-(const Matrix<N, M, T>& rgh) const {
    Matrix<N, M, T> tmp = *this;
    tmp -= rgh;
    return tmp;
  }

  Matrix<N, M, T> operator*(const T& factor) const {
    Matrix<N, M, T> tmp = *this;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        tmp(i, j) *= factor;
      }
    }
    return tmp;
  }

  template <size_t P>
  Matrix<N, P, T> operator*(Matrix<M, P, T>& rgh) const {
    Matrix<N, P, T> tmp;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < P; ++j) {
        for (size_t k = 0; k < M; ++k) {
          tmp(i, j) += array_[i][k] * rgh(k, j);
        }
      }
    }
    return tmp;
  }

  Matrix<M, N, T> Transposed() const {
    Matrix<M, N, T> tmp;
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        tmp(i, j) = array_[j][i];
      }
    }
    return tmp;
  }

  bool operator==(const Matrix<N, M, T>& rgh) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (array_[i][j] != rgh(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<std::vector<T> > array_;
};

template <size_t N, typename T>
class Matrix<N, N, T> {
 public:
  Matrix() { array.resize(N, std::vector<T>(N)); }

  Matrix(std::vector<std::vector<T> >& other) { array = other; }

  Matrix(T elem) {
    array.resize(N, std::vector<T>(N));
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        array[i][j] = elem;
      }
    }
  }

  T& operator()(const size_t kIndexI, const size_t kIndexJ) {
    return array[kIndexI][kIndexJ];
  }

  const T& operator()(const size_t kIndexI, const size_t kIndexJ) const {
    return array[kIndexI][kIndexJ];
  }

  Matrix<N, N, T>& operator+=(const Matrix<N, N, T>& rgh) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        array[i][j] += rgh(i, j);
      }
    }
    return *this;
  }

  Matrix<N, N, T> operator+(const Matrix<N, N, T>& rgh) const {
    Matrix<N, N, T> tmp = *this;
    tmp += rgh;
    return tmp;
  }

  Matrix<N, N, T>& operator-=(const Matrix<N, N, T>& rgh) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        array[i][j] -= rgh(i, j);
      }
    }
    return *this;
  }

  Matrix<N, N, T> operator-(const Matrix<N, N, T>& rgh) const {
    Matrix<N, N, T> tmp = *this;
    tmp -= rgh;
    return tmp;
  }

  Matrix<N, N, T> operator*(const T& factor) const {
    Matrix<N, N, T> tmp = *this;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        tmp(i, j) *= factor;
      }
    }
    return tmp;
  }

  template <size_t P>
  Matrix<N, P, T> operator*(const Matrix<N, P, T>& rgh) const {
    Matrix<N, N, T> tmp;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < P; ++j) {
        for (size_t k = 0; k < N; ++k) {
          tmp(i, j) += array[i][k] * rgh(k, j);
        }
      }
    }
    return tmp;
  }

  Matrix<N, N, T> Transposed() const {
    Matrix<N, N, T> tmp;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        tmp(i, j) = array[j][i];
      }
    }
    return tmp;
  }

  bool operator==(const Matrix<N, N, T>& rgh) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        if (array[i][j] != rgh(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  T Trace() const {
    T trc = 0;
    for (size_t i = 0; i < N; ++i) {
      trc += array[i][i];
    }
    return trc;
  }

  std::vector<std::vector<T> > array;
};