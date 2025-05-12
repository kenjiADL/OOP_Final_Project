#include <gtest/gtest.h>
#include "Payment.h"
#include "PaymentMethod.h"

TEST(PaymentTest, CashNoSurcharge) {
    Payment p(100, PaymentMethod::Cash);
    EXPECT_EQ(p.getAmount(), 100);
    EXPECT_EQ(p.getMethod(), PaymentMethod::Cash);
    EXPECT_EQ(p.getChargedAmount(), 100);
}

TEST(PaymentTest, CardWithSurcharge) {
    Payment p(100, PaymentMethod::Card);
    EXPECT_EQ(p.getAmount(), 100);
    EXPECT_EQ(p.getMethod(), PaymentMethod::Card);
}