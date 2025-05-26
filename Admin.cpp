#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <memory>
#include "CRegister.h"
#include "Admin.h"
#include "Product.h"

using namespace std;

Admin::Admin(vector<unique_ptr<Product>>& inventory,
             SalesReport& salesData,
             CRegister& cashRegister,
             const string& inventoryFile,
             const string& adminLogFile)
    : inventory(inventory),
      salesData(salesData),
      cashRegister(cashRegister),
      inventoryFile(inventoryFile),
      adminLogFile(adminLogFile) {}

bool Admin::saveInventory() const {
    ofstream out(inventoryFile);
    if (!out) {
        cerr << "ERROR: could not write " << inventoryFile << "\n";
        return false;
    }
    // Save as CSV: code,name,price,quantity
    for (const auto& item : inventory) {
        float priceFloat = item->getPrice() / 100.0f;
        out << item->getCode() << ','
            << item->getName() << ','
            << fixed << setprecision(2) << priceFloat << ','
            << item->getQuantity() << '\n';
    }
    return true;
}

void Admin::removeItem(int code) {
    auto it = find_if(inventory.begin(), inventory.end(),
        [&](const unique_ptr<Product>& i){ return i->getCode() == code; });
    if (it == inventory.end()) {
        throw InvalidCodeException("Product code " + to_string(code) + " not found");
    }
    inventory.erase(it);
    saveInventory();
    cout << "Item removed.\n";
}

void Admin::showSalesReport() const {
    // Show balance and totals
    cout << "Cash Register Balance: $"
              << fixed << setprecision(2)
              << (cashRegister.getBalance() / 100.0f) << "\n\n";
    cout << "Total Sales: $"
              << fixed << setprecision(2)
              << salesData.getTotalSales() << "\n\n";
    
    // Show items sold
    cout << "Items sold:\n";
    for (auto& p : salesData.getItemsSold()) {
        int code = p.first, qty = p.second;
        auto it = find_if(inventory.begin(), inventory.end(),
            [&](const unique_ptr<Product>& i){ return i->getCode() == code; });
        string name = (it != inventory.end() ? (*it)->getName() : "Unknown");
        cout << "  " << name << " (code " << code << "): " << qty << "\n";
    }

    // Show transaction log
    cout << "\n-- Raw Purchase Log --\n";
    ifstream logIn(adminLogFile);
    if (!logIn) {
        cout << "  <no purchases logged yet>\n";
    } else {
        string line;
        while (getline(logIn, line)) {
            cout << "  " << line << "\n";
        }
    }
}

void Admin::setItemPrice(int code, int newPriceCents) {
    Product* product = findProduct(code);
    if (!product) {
        throw InvalidCodeException("Product code " + to_string(code) + " not found");
    }
    if (newPriceCents < 0) {
        throw InvalidQuantityException("Price must be non-negative");
    }
    product->setPrice(newPriceCents);
    saveInventory();
    cout << "Price updated.\n";
}

void Admin::restockItem(int code, int quantity) {
    Product* product = findProduct(code);
    if (!product) {
        throw InvalidCodeException("Product code " + to_string(code) + " not found");
    }
    if (quantity < 0) {
        throw InvalidQuantityException("Quantity must be non-negative");
    }
    product->addStock(quantity);
    saveInventory();
    cout << "Stock updated.\n";
}

size_t Admin::getInventorySize() const {
    return inventory.size();
}

bool Admin::hasProduct(int code) const {
    return findProduct(code) != nullptr;
}

Product* Admin::findProduct(int code) const {
    auto it = find_if(inventory.begin(), inventory.end(),
        [&](const unique_ptr<Product>& i){ return i->getCode() == code; });
    return (it != inventory.end()) ? it->get() : nullptr;
}
