#include <gtest/gtest.h>
#include "Snack.h"

TEST(ProductTest, AccessorsWork) {
    Snack s(1, "Test", 150, 5);
    EXPECT_EQ(s.getName(), "Test");
    EXPECT_EQ(s.getPrice(), 150);
    EXPECT_EQ(s.getQuantity(), 5);
}