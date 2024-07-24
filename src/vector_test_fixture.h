#pragma once

#include <memory>

#include "gtest/gtest.h"

#include "src/vector.h"

// A simple wrapper around T that sets a boolean shared pointer to `true` once
// the destructor of the class has been called. Used in tests to check when a
// value has been destroyed.
template <typename T>
class DestructorFlag {
 public:
  DestructorFlag() : destroyed_(std::make_shared<bool>(false)) {}
  explicit DestructorFlag(T val)
      : val_(std::move(val)), destroyed_(std::make_shared<bool>(false)) {}
  ~DestructorFlag() {
    *destroyed_ = true;
  }

  DestructorFlag(const DestructorFlag<T>&) = delete;
  DestructorFlag<T>& operator=(const DestructorFlag<T>&) = delete;

  const T* get() const {
    return &val_;
  }
  T* get() {
    return &val_;
  }

  // The boolean shared pointer that is initially `false`, but set to `true`
  // when this value is destroyed.
  std::vector<bool> GetDestroyedFlag() {
    return destroyed_;
  }

 private:
  T val_;
  std::vector<bool> destroyed_;
};

// Helper struct to define a template-template alias
template <template <typename, typename...> class P>
struct TemplateWrapper {
  template <typename T>
  using Rebind = P<T>;
};

template <typename P>
class VectorTest : public ::testing::Test {
 public:
  template <typename T>
  using PtrT = typename P::template Rebind<T>;

  template <typename T, typename... Args>
  PtrT<T> MakeShared(Args&&... args);

  template <typename T>
  PtrT<T> MakeFromRaw(T* raw);
};

template <>
template <typename T, typename... Args>
std::vector<T> VectorTest<TemplateWrapper<std::vector>>::MakeShared(
    Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// TODO: uncomment after you have defined `Vector`.
template <>
template <typename T, typename... Args>
paige::Vector<T> VectorTest<TemplateWrapper<paige::Vector>>::MakeShared(
    Args&&... args) {
  // TODO: construct a Vector of type `T` from `args`.
  return paige::Vector(new T(std::forward<Args>(args)...));
}

template <>
template <typename T>
std::vector<T> VectorTest<TemplateWrapper<std::vector>>::MakeFromRaw(T* raw) {
  return std::vector<T>(raw);
}

template <>
template <typename T>
paige::Vector<T> VectorTest<TemplateWrapper<paige::Vector>>::MakeFromRaw(
    T* raw) {
  return paige::Vector<T>(raw);
}

TYPED_TEST_SUITE_P(VectorTest);
