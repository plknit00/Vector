#include "src/vector.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "src/vector_test_fixture.h"

TYPED_TEST_P(VectorTest, Empty) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;

  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), 0);
}

TYPED_TEST_P(VectorTest, CopyEmpty) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  VectorT vector2 = vector;

  EXPECT_TRUE(vector2.empty());
  EXPECT_EQ(vector2.size(), 0);
}

// TYPED_TEST_P(VectorTest, MoveEmpty) {
//   using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
//   VectorT vector;
//   VectorT vector2 = std::move(vector);

//   EXPECT_TRUE(vector2.empty());
//   EXPECT_EQ(vector2.size(), 0);
// }

TYPED_TEST_P(VectorTest, PushBack) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(0);

  std::vector<uint64_t> v;
  std::allocator<uint64_t> a;
  v.push_back(1);

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.size(), 1);
}

// TYPED_TEST_P(VectorTest, Copy) {
//   using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
//   VectorT vector;
//   VectorT vector2 = vector;

//   EXPECT_TRUE(vector2.empty());
//   EXPECT_EQ(vector2.size(), 0);
// }

// TYPED_TEST_P(VectorTest, Move) {
//   using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
//   VectorT vector;
//   VectorT vector2 = std::move(vector);

//   EXPECT_TRUE(vector2.empty());
//   EXPECT_EQ(vector2.size(), 0);
// }

REGISTER_TYPED_TEST_SUITE_P(VectorTest, Empty, CopyEmpty, PushBack);
// Copy, Empty);

using Implementations = testing::Types<TemplateWrapper<std::vector>,
                                       TemplateWrapper<paige::Vector>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector, VectorTest, Implementations);
