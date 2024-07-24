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
class CommunalPtrTest : public ::testing::Test {
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
std::shared_ptr<T>
CommunalPtrTest<TemplateWrapper<std::shared_ptr>>::MakeShared(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// TODO: uncomment after you have defined `CommunalPtr`.
template <>
template <typename T, typename... Args>
paige::CommunalPtr<T>
CommunalPtrTest<TemplateWrapper<paige::CommunalPtr>>::MakeShared(
    Args&&... args) {
  // TODO: construct a CommunalPtr of type `T` from `args`.
  return paige::CommunalPtr(new T(std::forward<Args>(args)...));
}

template <>
template <typename T>
std::shared_ptr<T>
CommunalPtrTest<TemplateWrapper<std::shared_ptr>>::MakeFromRaw(T* raw) {
  return std::shared_ptr<T>(raw);
}

template <>
template <typename T>
paige::CommunalPtr<T>
CommunalPtrTest<TemplateWrapper<paige::CommunalPtr>>::MakeFromRaw(T* raw) {
  return paige::CommunalPtr<T>(raw);
}

TYPED_TEST_SUITE_P(CommunalPtrTest);
