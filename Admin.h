#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Product.h"
#include "SalesReport.h"
#include "CRegister.h"

class Admin {
 public:
  /**
   * @brief Construct an Admin controller for managing inventory and sales.
   * @param inventory Reference to the product inventory.
   * @param salesData Reference to the sales report manager.
   * @param cashRegister Reference to the cash register.
   * @param inventoryFile Path to the inventory CSV file.
   * @param adminLogFile Path to the purchase history log file.
   */
  Admin(std::vector<std::unique_ptr<Product>>& inventory,
        SalesReport& salesData,
        CRegister& cashRegister,
        const std::string& inventoryFile,
        const std::string& adminLogFile);

  /**
   * @brief Remove a product from inventory by its code and update the file.
   * @param code The selection code of the product to remove.
   */
  void removeItem(int code);

  /**
   * @brief Display cash balance, total sales, item counts sold, and raw log entries.
   */
  void showSalesReport() const;

  /**
   * @brief Update the price of a product and save changes.
   * @param code The selection code of the product.
   * @param newPriceCents The new price in cents.
   */
  void setItemPrice(int code, int newPriceCents);

  /**
   * @brief Add stock to a product and save changes.
   * @param code The selection code of the product.
   * @param quantity The amount of stock to add.
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
