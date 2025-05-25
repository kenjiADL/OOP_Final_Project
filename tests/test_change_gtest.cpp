#include <gtest/gtest.h>
#include "Change.h"
#include <map>
#include <sstream>

TEST(ChangeTest, BreakdownCorrect) {
    Change c(185);
    auto breakdown = c.getChangeBreakdown();
    std::map<int,int> expected = {{100,1},{50,1},{20,1},{10,1},{5,1}};
    EXPECT_EQ(breakdown, expected);
}

TEST(ChangeTest, StreamOperatorOverloading) {
    Change c(67);
    std::ostringstream oss;
    oss << c;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Change returned:") != std::string::npos);
    EXPECT_TRUE(output.find("50c x 1 coins") != std::string::npos);
    EXPECT_TRUE(output.find("10c x 1 coins") != std::string::npos);
    EXPECT_TRUE(output.find("5c x 1 coins") != std::string::npos);
}

TEST(ChangeTest, AdditionOperatorOverloading) {
    Change c1(25);  // 25 cents
    Change c2(30);  // 30 cents
    
    Change combined = c1 + c2;  // Should be 55 cents total
    auto breakdown = combined.getChangeBreakdown();
    
    EXPECT_EQ(breakdown[50], 1);  // 50 cent coin
    EXPECT_EQ(breakdown[5], 1);   // 5 cent coin
}

TEST(ChangeTest, EqualityOperatorOverloading) {
    Change c1(67);
    Change c2(67);
    Change c3(50);
    
    EXPECT_TRUE(c1 == c2);   // Same breakdown
    EXPECT_FALSE(c1 == c3);  // Different breakdown
}