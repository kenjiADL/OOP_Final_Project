#include <gtest/gtest.h>
#include "Admin.h"
#include "Snack.h"
#include "SalesReport.h"
#include "CRegister.h"

TEST(AdminTest, ConstructAdmin) {
    std::vector<std::unique_ptr<Product>> inventory;
    inventory.emplace_back(std::make_unique<Snack>(1, "TestSnack", 150, 10));
    SalesReport report;
    CRegister reg;
    Admin admin(inventory, report, reg, "inventory.txt", "log.txt");
    SUCCEED();  // Just testing construction
}