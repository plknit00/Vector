#pragma once

#include <utility>

namespace paige {

template <typename T>

class Vector {
 public:
  // default constructor
  explicit Vector() : start_(nullptr), length_(0), capacity_(0) {}

  // non default constructor

  // copy constructor
  Vector(const Vector& vec) : length_(vec.length_), capacity_(vec.length_) {
    if (this->length_ == 0) {
      vec->start = nullptr;
    } else {
      for (int i = 0; i < *this->length_; i++) {
        vec[i] = this[i];
      }
    }
  }

  // move constructor
  Vector(Vector&& vec) noexcept : length_(vec.length_), capacity_(vec.length_) {
    if (this->length_ == 0) {
      vec->start = nullptr;
    } else {
      for (int i = 0; i < this->length; i++) {
        vec[i] = this[i];
      }
    }
    // uncertain on this part and how it varies from copy contructor
    this->start_ = nullptr;
    this->length_ = 0;
  }

  void swap(Vector& vec1, Vector& vec2) {
    // not sure if i need to resize and if theres any other errors
    if ((vec1->length_ != 0) && ((vec2->length_ != 0))) {
      if (vec1->length < vec2->length) {
        for (int i = 0; i < *vec1->length_; i++) {
          auto temp = vec1[i];
          vec1[i] = vec2[i];
          vec2[i] = temp;
        }
        // how to resize vec1??? make it bigger
        //  how to make vec 2 smaller or is changing length enough
        for (int i = vec1->length_ - 1; i < vec2->length_; i++) {
          vec1[i] = vec2[i];
        }
      }
    } else {
      for (int i = 0; i < vec2->length_; i++) {
        auto temp = vec1[i];
        vec1[i] = vec2[i];
        vec2[i] = temp;
      }
      // how to resize vec1??? make it bigger
      //  how to make vec 2 smaller or is changing length enough
      for (int i = vec2->length_ - 1; i < vec1->length_; i++) {
        vec2[i] = vec1[i];
      }
    }
    auto temp = vec1->start_;
    vec1->start_ = vec2->start_;
    vec2->start_ = temp;
    auto temp2 = vec1->length_;
    vec1->length_ = vec2->length_;
    vec2->length_ = temp;
    vec1->capacity_ = vec1->length_;
    vec2->capacity_ = vec2.length_;
  }

  // overload assignment operator
  Vector& operator=(const Vector& vec) {
    Vector(vec).swap(*this);
    return *this;
  }

  T& operator[](size_t pos) {
    if (length_ == 0) {
      // return type default constructor?
      return start_;
    }
    auto location = start_ + pos;
    return location;
  }

  T* data(int index) {
    return start_ + index;
  }

  int size() {
    return length_;
  }

  bool empty() {
    return length_ == 0;
  }

  void erase(std::iterator<T*> pos) {
    // std::iterator<T*> start_
    // int index = pos
    // T::~T;
    // start_[0].~T();
  }

  void resize(size_t count) {
    if (length_ < count) {
      if (capacity_ < count) {
        capacity_ = count;
      }
      length_ = count;
    } else if (length_ > count) {
      length_ = count;
    }
  }

  void push_back(T* element) {
    if (length_ == capacity_) {
      this.resize();
    }
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
      T::~T;
      start_[0].~T();
    }
    // size = 0
    // capacity remains unchanged
  }

  void insert() {}

  T* front() {
    if (!empty()) {
      return this[0];
    }
  }

  T* back() {
    return this[length_ - 1];
  }

  void pop_back() {}

  // destructor
  ~Vector() {}

 private:
  T* start_;
  int length_;
  int capacity_;
};

}  // namespace paige
