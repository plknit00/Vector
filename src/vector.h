#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>

namespace paige {

template <typename T>

class Vector {
 public:
  // default constructor
  explicit Vector() {
    start_ = static_cast<T*>(::operator new(sizeof(T)));
  }

  // non default constructor

  // copy constructor
  Vector(const Vector& vec) : length_(vec.length_), capacity_(vec.capacity_) {
    if (vec.length_ == 0) {
      start_ = static_cast<T*>(::operator new(sizeof(T)));
    } else {
      start_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
      for (int i = 0; i < length_; i++) {
        (*this)[i] = vec[i];
      }
    }
  }

  // move constructor
  Vector(Vector&& vec) noexcept
      : start_(vec.start_), length_(vec.length_), capacity_(vec.capacity_) {
    vec.start_ = nullptr;
    vec.length_ = 0;
    vec.capacity_ = 0;
  }

  void swap(Vector& vec1, Vector& vec2) {
    std::swap(vec1.start_, vec2.start_);
    std::swap(vec1.length_, vec2.length_);
    std::swap(vec1.capacity_, vec2.capacity_);
  }

  Vector& operator=(const Vector& vec) {
    Vector(vec).swap(*this);
    return *this;
  }

  const T& operator[](size_t pos) const {
    if (length_ == 0) {
      return *start_;
    }
    auto location = start_ + pos;
    return *location;
  }

  T& operator[](size_t pos) {
    if (length_ == 0) {
      return *start_;
    }
    auto location = start_ + pos;
    return *location;
  }

  const T* data() const {
    return start_;
  }

  T* data() {
    return start_;
  }

  int size() {
    return length_;
  }

  bool empty() {
    return length_ == 0;
  }

  /*void erase(std::iterator<T*> pos) {
    // std::iterator<T*> start_
    // int index = pos
    // T::~T;
    // start_[0].~T();
  }*/

  // only make vector bigger
  // count must be greater than capacity
  void resize(size_t count) {
    // allocate space
    // copy info over
    start_ = static_cast<T*>(realloc(start_, count * sizeof(T)));
    capacity_ = count;
  }

  void push_back(const T& element) {
    if (length_ >= capacity_) {
      resize(2 * capacity_);
    }
    T* ptr = &(*this)[length_];
    new (ptr) T(element);
    length_ += 1;
  }

  void reserve(int new_capacity) {
    capacity_ = new_capacity;
    if (start_ == nullptr) {
      start_ = operator new(new_capacity);
    } else {
      // is this move constructor?
      start_ = paige::Vector(&this);
    }
  }

  void clear() {
    for (int i = 0; i < length_; i++) {
      start_[0].~T();
    }
    length_ = 0;
    // size = 0
    // capacity remains unchanged
  }

  // void insert() {}

  T& front() {
    return (*this)[0];
  }

  T& back() {
    return (*this)[length_ - 1];
  }

  void pop_back() {
    start_[length_ - 1].~T();
    length_ -= 1;
  }

  // destructor
  ~Vector() {
    clear();
    delete start_;
  }

 private:
  T* start_;
  int length_ = 0;
  int capacity_ = 1;
  // how to implement custom iterator
  // do i need to keep track of start and end
};

}  // namespace paige
