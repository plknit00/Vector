#include "src/vector.h"

#include <cstdint>
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

TYPED_TEST_P(VectorTest, MoveEmpty) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  VectorT vector2 = std::move(vector);

  EXPECT_TRUE(vector2.empty());
  EXPECT_EQ(vector2.size(), 0);
}

TYPED_TEST_P(VectorTest, PushBack) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(3);

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.size(), 1);
}

TYPED_TEST_P(VectorTest, Copy) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(4);
  VectorT vector2 = vector;

  EXPECT_FALSE(vector2.empty());
  EXPECT_EQ(vector2.size(), 1);
}

TYPED_TEST_P(VectorTest, Move) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(5);
  VectorT vector2 = std::move(vector);

  EXPECT_FALSE(vector2.empty());
  EXPECT_EQ(vector2.size(), 1);
}

TYPED_TEST_P(VectorTest, SquareBracketsOp) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(6);
  vector.push_back(13);

  EXPECT_EQ(vector[0], 6);
  EXPECT_EQ(vector[1], 13);
}

TYPED_TEST_P(VectorTest, CopyBig) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(19);
  vector.push_back(47);
  vector.push_back(6432);
  vector.push_back(0355);
  VectorT vector2 = vector;
  vector[1] = 4;

  EXPECT_EQ(vector[0], 19);
  EXPECT_EQ(vector[1], 4);
  EXPECT_EQ(vector[2], 6432);
  EXPECT_EQ(vector[3], 0355);

  EXPECT_EQ(vector2[0], 19);
  EXPECT_EQ(vector2[1], 47);
  EXPECT_EQ(vector2[2], 6432);
  EXPECT_EQ(vector2[3], 0355);
}

TYPED_TEST_P(VectorTest, Data) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(19);
  vector.push_back(47);
  vector.push_back(6432);
  vector.push_back(0355);
  VectorT vector2 = vector;

  EXPECT_EQ(*vector.data(), 19);
  EXPECT_EQ(*vector2.data(), 19);
}

TYPED_TEST_P(VectorTest, Clear) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(6);
  vector.push_back(13);
  vector.clear();

  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), 0);
}

TYPED_TEST_P(VectorTest, ClearCopy) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(6);
  vector.push_back(13);
  VectorT vector2 = vector;
  vector.clear();

  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), 0);
  EXPECT_FALSE(vector2.empty());
  EXPECT_EQ(vector2.size(), 2);
  EXPECT_EQ(vector2[1], 13);
}

TYPED_TEST_P(VectorTest, ClearMove) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(6);
  vector.push_back(13);
  VectorT vector2 = std::move(vector);
  vector.clear();

  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), 0);
  EXPECT_FALSE(vector2.empty());
  EXPECT_EQ(vector2.size(), 2);
  EXPECT_EQ(vector2[1], 13);
}

TYPED_TEST_P(VectorTest, Front) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(20);
  vector.push_back(30);
  vector.push_back(40);
  vector.push_back(50);

  EXPECT_EQ(vector.front(), 20);
}

TYPED_TEST_P(VectorTest, Back) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(20);
  vector.push_back(30);
  vector.push_back(40);
  vector.push_back(50);

  EXPECT_EQ(vector.back(), 50);
}

TYPED_TEST_P(VectorTest, FrontBackEqual) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(5);

  EXPECT_EQ(vector.front(), 5);
  EXPECT_EQ(vector.back(), 5);
}

TYPED_TEST_P(VectorTest, PopBack) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(5);
  vector.push_back(6);
  vector.push_back(7);
  vector.push_back(8);

  EXPECT_EQ(vector.size(), 4);
  EXPECT_EQ(vector.back(), 8);
  vector.pop_back();
  EXPECT_EQ(vector.size(), 3);
  EXPECT_EQ(vector.back(), 7);
}

TYPED_TEST_P(VectorTest, Insert) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  auto start = vector.begin();
  vector.insert(start, 7);

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.size(), 1);
  EXPECT_EQ(vector[0], 7);
}

TYPED_TEST_P(VectorTest, Erase) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(9);
  auto start = vector.begin();
  vector.erase(start);

  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), 0);
}

TYPED_TEST_P(VectorTest, EraseMedium) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(0);
  vector.push_back(1);  // e
  vector.push_back(2);
  vector.push_back(3);
  vector.push_back(4);  // e
  vector.push_back(5);
  vector.erase(vector.begin() + 1);
  vector.erase(vector.begin() + 3);

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.size(), 4);
  EXPECT_EQ(vector[0], 0);
  EXPECT_EQ(vector[1], 2);
  EXPECT_EQ(vector[2], 3);
  EXPECT_EQ(vector[3], 5);
}

TYPED_TEST_P(VectorTest, EraseLong) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(0);  // e
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);  // e
  vector.push_back(4);
  vector.push_back(5);
  vector.push_back(6);  // e
  vector.push_back(7);
  vector.push_back(8);  // e
  vector.erase(vector.begin());
  vector.erase(vector.begin() + 5);
  vector.erase(vector.begin() + 2);
  vector.erase(vector.begin() + 5);

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.size(), 5);
  EXPECT_EQ(vector[0], 1);
  EXPECT_EQ(vector[1], 2);
  EXPECT_EQ(vector[2], 4);
  EXPECT_EQ(vector[3], 5);
  EXPECT_EQ(vector[4], 7);
}

TYPED_TEST_P(VectorTest, InsertLong) {
  using VectorT = VectorTest<TypeParam>::template VectorT<uint64_t>;
  VectorT vector;
  vector.push_back(9);
  auto start = vector.begin();
  vector.erase(start);

  EXPECT_TRUE(vector.empty());
  EXPECT_EQ(vector.size(), 0);
}

REGISTER_TYPED_TEST_SUITE_P(VectorTest, Empty, CopyEmpty, MoveEmpty, PushBack,
                            Copy, Move, SquareBracketsOp, CopyBig, Data, Clear,
                            ClearCopy, ClearMove, Front, Back, FrontBackEqual,
                            PopBack, Insert, Erase, EraseMedium, EraseLong,
                            InsertLong);

using Implementations = testing::Types<TemplateWrapper<std::vector>,
                                       TemplateWrapper<paige::Vector>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector, VectorTest, Implementations);
