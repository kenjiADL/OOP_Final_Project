#include <gtest/gtest.h>
#include "Item.h"

TEST(ItemTest, QuantityManipulation) {
    Item i(1, "Test", 100, 2);
    EXPECT_EQ(i.getQuantity(), 2);
    i.reduceQuantity();
    EXPECT_EQ(i.getQuantity(), 1);
    i.addStock(3);
    EXPECT_EQ(i.getQuantity(), 4);
}

TEST(ItemTest, PriceSetting) {
    Item i(1, "Test", 100, 2);
    EXPECT_EQ(i.getPrice(), 100);
    i.setPrice(150);
    EXPECT_EQ(i.getPrice(), 150);
}