#pragma once

#include <memory>

#include "gtest/gtest.h"

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

  // The boolean Vector pointer that is initially `false`, but set to `true`
  // when this value is destroyed.
  std::shared_ptr<bool> GetDestroyedFlag() {
    return destroyed_;
  }

 private:
  T val_;
  std::shared_ptr<bool> destroyed_;
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
  using VectorT = typename P::template Rebind<T>;
};

TYPED_TEST_SUITE_P(VectorTest);
