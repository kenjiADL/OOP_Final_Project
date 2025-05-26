#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "Product.h"
#include "SalesReport.h"
#include "CRegister.h"

using namespace std;

/**
 * @brief Admin interface for the vending machine
 * 
 * Handles inventory management, sales reports, and pricing.
 */
class Admin {
public:
    // Custom exceptions
    class InvalidCodeException : public runtime_error {
        using runtime_error::runtime_error;
    };
    
    class InvalidQuantityException : public runtime_error {
        using runtime_error::runtime_error;
    };

    // Constructor takes references to required components and file paths
    Admin(vector<unique_ptr<Product>>& inventory,
          SalesReport& salesData,
          CRegister& cashRegister,
          const string& inventoryFile,
          const string& adminLogFile);

    // Remove a product from inventory
    void removeItem(int code);

    // Display sales report
    void showSalesReport() const;

    // Update item price (throws InvalidCodeException if code not found)
    void setItemPrice(int code, int newPriceCents);

    // Restock item (throws InvalidCodeException/InvalidQuantityException)
    void restockItem(int code, int quantity);

    // Get current inventory size
    size_t getInventorySize() const;

    // Check if product code exists
    bool hasProduct(int code) const;

private:
    vector<unique_ptr<Product>>& inventory;  // Reference to inventory
    SalesReport& salesData;                 // Reference to sales data
    CRegister& cashRegister;               // Reference to cash register
    const string inventoryFile;            // File paths are immutable
    const string adminLogFile;

    // Find product by code (returns nullptr if not found)
    Product* findProduct(int code) const;

    // Save current inventory state to CSV file
    bool saveInventory() const;
};

#endif // ADMIN_H
