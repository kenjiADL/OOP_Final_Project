#include <gtest/gtest.h>
#include "Snack.h"

// Fixture (optional)
class SnackTest : public ::testing::Test {
protected:
  Snack s{101, "TestSnack", 125, 5};
};

TEST_F(SnackTest, DescribeFormatsPrice) {
  EXPECT_EQ(s.describe(), "TestSnack (snack) – $1.25");
}

TEST_F(SnackTest, QuantityModifiesCorrectly) {
  EXPECT_EQ(s.getQuantity(), 5);
  s.reduceQuantity();
  EXPECT_EQ(s.getQuantity(), 4);
  s.addStock(6);
  EXPECT_EQ(s.getQuantity(), 10);
}