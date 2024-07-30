#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>

namespace paige {

template <typename T>

class Vector {
 public:
  // *********** ITERATOR ***********
  class iterator {
    friend class Vector;

   public:
    // pre increment
    iterator& operator++() {
      iter_ptr += sizeof(T);
      iterator iter = iter_ptr;
      return iter;
    }

    // post increment
    iterator operator++(int) {
      iterator iter = iter_ptr;
      iter_ptr += sizeof(T);
      return iter;
    }

    iterator operator+(ssize_t index) {
      return iterator(iter_ptr + index);
    }

    ssize_t operator-(const iterator& iter) const {
      return iter_ptr - iter.iter_ptr;
    }

    ~iterator() = default;

   private:
    iterator(Vector& vec, int index) : iter_ptr((vec.start_ + index)) {}
    explicit iterator(T* ptr) : iter_ptr(ptr) {}
    T* iter_ptr;
  };

  iterator begin() {
    return iterator(*this, 0);
  }

  iterator end() {
    return iter(start_, length_);
  }

  // default constructor
  explicit Vector() {
    start_ = static_cast<T*>(::operator new(sizeof(T)));
  }

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

  void erase(iterator pos) {
    int pos_index = pos - begin();
    int final_index = length_ - 1;
    // scoot everything from pos to end over by 1
    while (pos_index <= final_index) {
      (*this)[pos_index] = std::move((*this)[pos_index + 1]);
      pos_index++;
    }
    length_ -= 1;
  }

  iterator insert(const iterator pos, const T& value) {
    if (length_ >= capacity_) {
      resize(2 * capacity_);
    }
    ssize_t pos_index = pos - begin();
    ssize_t current_index = length_ - 1;
    // scoot everything from pos to end over by 1
    while (pos_index <= current_index) {
      (*this)[current_index + 1] = (*this)[current_index];
      current_index--;
    }
    // insert value before pos
    (*this)[pos_index - 1] = value;
    length_ += 1;
    return iterator(*this, pos_index - 1);
  }

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
  }

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

  ~Vector() {
    clear();
    delete start_;
  }

 private:
  T* start_;
  int length_ = 0;
  int capacity_ = 1;
};

}  // namespace paige
