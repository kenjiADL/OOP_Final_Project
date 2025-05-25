#include <gtest/gtest.h>
#include "Alcoholic.h"

// Fixture for Alcoholic tests
class AlcoholicTest : public ::testing::Test {
protected:
    Alcoholic beer{12, "Beer", 350, 10, false};
    Alcoholic dietWine{15, "Diet Wine", 850, 5, true};
};

TEST_F(AlcoholicTest, DescribeFormatsCorrectly) {
    EXPECT_EQ(beer.describe(), "Beer (alcoholic drink) – $3.50");
    EXPECT_EQ(dietWine.describe(), "Diet Wine (diet alcoholic drink) – $8.50");
}

TEST_F(AlcoholicTest, RequiresAgeVerification) {
    EXPECT_TRUE(beer.requiresAgeVerification());
    EXPECT_TRUE(dietWine.requiresAgeVerification());
}

TEST_F(AlcoholicTest, InheritsFromDrink) {
    EXPECT_FALSE(beer.isDiet());
    EXPECT_TRUE(dietWine.isDiet());
}

TEST_F(AlcoholicTest, QuantityModifiesCorrectly) {
    EXPECT_EQ(beer.getQuantity(), 10);
    beer.reduceQuantity();
    EXPECT_EQ(beer.getQuantity(), 9);
    beer.addStock(5);
    EXPECT_EQ(beer.getQuantity(), 14);
} 