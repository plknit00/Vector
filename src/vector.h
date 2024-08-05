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

  // Copy-assignment
  Vector& operator=(Vector&& vector) {
    clear();
    free(start_);
    start_ = vector.start_;
    length_ = vector.length_;
    capacity_ = vector.capacity_;
    vector.start_ = nullptr;
    vector.length_ = 0;
    vector.capacity_ = 0;
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
    // scoot everything from current (pos) to end (final) left by 1
    while (pos_index <= final_index) {
      (*this)[pos_index] = std::move((*this)[pos_index + 1]);
      pos_index++;
    }
    length_ -= 1;
  }

  iterator insert(const iterator pos, const T& value) {
    ssize_t pos_index = pos - begin();
    if (length_ == capacity_) {
      resize(2 * capacity_);
    }
    ssize_t current_index = length_ - 1;
    // scoot everything from end (current) to pos right by 1
    while (pos_index <= current_index) {
      (*this)[current_index + 1] = std::move((*this)[current_index]);
      current_index--;
    }
    // insert value before pos
    // CHECK INDEX
    (*this)[pos_index] = value;
    length_ += 1;
    // CHECK INDEX
    return iterator(*this, pos_index);
  }

  // only make vector bigger
  // count must be greater than capacity
  void resize(size_t count) {
    auto new_start = static_cast<T*>(malloc(count * sizeof(T)));
    for (int i = 0; i < length_; i++) {
      // Call the move constructor on new_start[i], with start_[i] as the
      // parameter.
      new (&new_start[i]) T(std::move(start_[i]));
      // Need to destroy start_[i] even though it was moved (for every
      // construction there is a matching destruction).
      start_[i].~T();
    }
    start_ = new_start;
    capacity_ = count;
  }

  void push_back(const T& element) {
    if (length_ == capacity_) {
      resize(2 * capacity_);
    }
    T* ptr = &(*this)[length_];
    // call constructor of T on ptr, passing element as constructor parameters
    new (ptr) T(element);
    length_ += 1;
  }

  void push_back(T&& element) {
    if (length_ == capacity_) {
      resize(2 * capacity_);
    }
    T* ptr = &(*this)[length_];
    // call constructore of T on ptr, passing elt as constructor parameters
    new (ptr) T(std::move(element));
    length_ += 1;
  }

  void reserve(int new_capacity) {
    capacity_ = new_capacity;
    if (start_ == nullptr) {
      start_ = operator new(new_capacity);
    } else if (new_capacity > capacity_) {
      resize(new_capacity);
    }
  }

  void clear() {
    for (int i = 0; i < length_; i++) {
      start_[i].~T();
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
    free(start_);
  }

 private:
  T* start_;
  int length_ = 0;
  int capacity_ = 1;
};

}  // namespace paige
