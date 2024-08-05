#include <cstdint>

#include "src/vector.h"

int main() {
  paige::Vector<uint64_t> vector;
  vector.insert(vector.begin(), 0);      // 0
  vector.insert(vector.begin() + 1, 3);  // 0,3
  vector.insert(vector.begin(), 5);      // 5,0,3
  vector.insert(vector.begin() + 3, 7);  // 5,0,3,7
  vector.insert(vector.begin() + 2, 9);  // 5,0,9,3,7

  //   ASSERT_FALSE(vector.empty());
  //   ASSERT_EQ(vector.size(), 5);
  //   EXPECT_EQ(vector[0], 5);
  //   EXPECT_EQ(vector[1], 0);
  //   EXPECT_EQ(vector[2], 9);
  //   EXPECT_EQ(vector[3], 3);
  //   EXPECT_EQ(vector[4], 7);
}