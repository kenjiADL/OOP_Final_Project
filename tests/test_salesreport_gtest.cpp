#include <gtest/gtest.h>
#include "SalesReport.h"

TEST(SalesReportTest, RecordAndRetrieve) {
    SalesReport report;
    report.recordSale(1, 150);
    EXPECT_FLOAT_EQ(report.getTotalSales(), 1.50);
    EXPECT_EQ(report.getItemsSold().at(1), 1);
}