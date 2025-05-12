#include <gtest/gtest.h>
#include "Drink.h"

TEST(DrinkDescribeTest, DietFlag) {
  Drink d1{201, "Cola", 150, 10, true};
  EXPECT_EQ(d1.describe(), "Cola (diet drink) – $1.50");
  Drink d2{202, "Juice", 175, 8, false};
  EXPECT_EQ(d2.describe(), "Juice (drink) – $1.75");
}

TEST(DrinkStockTest, InheritedBehavior) {
  Drink d{203, "Water", 100, 1, false};
  EXPECT_EQ(d.getQuantity(), 1);
  d.reduceQuantity();
  EXPECT_EQ(d.getQuantity(), 0);
  d.addStock(3);
  EXPECT_EQ(d.getQuantity(), 3);
}