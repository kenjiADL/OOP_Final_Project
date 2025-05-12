#include <gtest/gtest.h>
#include "Change.h"
#include <map>

TEST(ChangeTest, BreakdownCorrect) {
    Change c(185);
    auto breakdown = c.getChangeBreakdown();
    std::map<int,int> expected = {{100,1},{50,1},{20,1},{10,1},{5,1}};
    EXPECT_EQ(breakdown, expected);
}