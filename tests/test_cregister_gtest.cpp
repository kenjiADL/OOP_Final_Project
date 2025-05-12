#include <gtest/gtest.h>
#include "CRegister.h"

TEST(CRegisterTest, AddPayment) {
    CRegister r;
    EXPECT_EQ(r.getBalance(), 0);
    r.addPayment(150);
    EXPECT_EQ(r.getBalance(), 150);
}

TEST(CRegisterTest, DispenseChange) {
    CRegister r;
    r.addPayment(200);
    int change = r.dispenseChange(75);
    EXPECT_EQ(change, 75);
    EXPECT_EQ(r.getBalance(), 125);
}

TEST(CRegisterTest, DispenseMoreThanBalance) {
    CRegister r;
    r.addPayment(50);
    int change = r.dispenseChange(100);
    EXPECT_EQ(change, 50);
    EXPECT_EQ(r.getBalance(), 0);
}