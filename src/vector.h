#pragma once

#include <utility>

namespace paige {

template <typename T>

class Vector {
 public:
  // default constructor
  explicit Vector() : head_(nullptr), length_(nullptr) {}

  // non default constructor

  // copy constructor
  Vector(const Vector& vec) : length_(vec.length_) {
    if (*this->length_ == 0) {
      vec->head = nullptr;
    } else {
      for (int i = 0; i < *this->length_; i++) {
        vec[i] = this[i];
      }
    }
  }

  // move constructor
  Vector(Vector&& vec) noexcept : length_(vec.length_) {
    if (*this->length_ == 0) {
      vec->head = nullptr;
    } else {
      auto len = this->length_;
      for (int i = 0; i < *len; i++) {
        vec[i] = this[i];
      }
    }
    // uncertain on this part and how it varies from copy contructor
    this->head_ = nullptr;
    *this->length_ = 0;
  }

  void swap(Vector& vec1, Vector& vec2) {
    // not sure if i need to resize and if theres any other errors
    if ((*vec1->length_ != 0) && ((*vec2->length_ != 0))) {
      if (*vec1->length < vec2->length) {
        for (int i = 0; i < *vec1->length_; i++) {
          auto temp = vec1[i];
          vec1[i] = vec2[i];
          vec2[i] = temp;
        }
        // how to resize vec1??? make it bigger
        //  how to make vec 2 smaller or is changing length enough
        for (int i = *vec1->length_ - 1; i < *vec2->length_; i++) {
          vec1[i] = vec2[i];
        }
      }
    } else {
      for (int i = 0; i < *vec2->length_; i++) {
        auto temp = vec1[i];
        vec1[i] = vec2[i];
        vec2[i] = temp;
      }
      // how to resize vec1??? make it bigger
      //  how to make vec 2 smaller or is changing length enough
      for (int i = *vec2->length_ - 1; i < *vec1->length_; i++) {
        vec2[i] = vec1[i];
      }
    }
    auto temp = vec1->head_;
    vec1->head_ = vec2->head_;
    vec2->head_ = temp;
    auto temp2 = vec1->length_;
    vec1->length_ = vec2->length_;
    vec2->length_ = temp;
  }

  // overload assignment operator
  Vector& operator=(const Vector& vec) {
    Vector(vec).swap(*this);
    return *this;
  }

  // where do i get index from []?
  T& operator[](size_t pos) {
    if (*length_ == 0) {
      // return type default constructor?
      return head_;
    }
    auto location = head_ + pos;
    return location;
  }

  T* get() {}

  int size() {
    return *length_;
  }

  bool empty() {
    return *length_ == 0;
  }

  void erase() {}

  void push_back() {}

  void reserve(int size) {
    head_ = operator new(size);
  }

  void clear() {}

  void insert() {}

  T* front() {
    if (!empty()) {
      return this[0];
    }
  }

  T* back() {
    return this[*length_ - 1];
  }

  // destructor
  ~Vector() {}

 private:
  T* head_;
  int* length_;
};

}  // namespace paige
