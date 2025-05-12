#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Product.h"
#include "SalesReport.h"
#include "CRegister.h"

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Product.h"
#include "SalesReport.h"
#include "CRegister.h"

/**
 * @class Admin
 * @brief Controller for vending machine administration tasks, such as managing inventory,
 *        pricing, restocking, and viewing sales reports.
 */
class Admin {
 public:
  Admin(std::vector<std::unique_ptr<Product>>& inventory,
        SalesReport& salesData,
        CRegister& cashRegister,
        const std::string& inventoryFile,
        const std::string& adminLogFile);

  /**
   * @brief Remove a product from the inventory by code and update the inventory file.
   * @param code The unique code identifying the product to remove.
   */
  void removeItem(int code);

  /**
   * @brief Display the cash register balance, total sales, items sold, and raw purchase log.
   */
  void showSalesReport() const;

  /**
   * @brief Update the price of an item and persist changes to the inventory file.
   * @param code The code of the product to update.
   * @param newPriceCents The new price in cents (must be non-negative).
   */
  void setItemPrice(int code, int newPriceCents);

  /**
   * @brief Add more stock to an existing product and save the updated inventory.
   * @param code The code of the product to restock.
   * @param quantity Number of units to add to the current stock.
   */
  void restockItem(int code, int quantity);

 private:
  std::vector<std::unique_ptr<Product>>& pInventory;
  SalesReport& pSalesData;
  CRegister& pCashRegister;
  std::string pInventoryFile;
  std::string pAdminLogFile;

  // Write the current inventory vector back into the CSV file.
  void saveInventory() const;
};
