#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <memory>
#include "CRegister.h"
#include "Admin.h"
#include "Product.h"

Admin::Admin(std::vector<std::unique_ptr<Product>>& inventory,
             SalesReport& salesData,
             CRegister& cashRegister,
             const std::string& inventoryFile,
             const std::string& adminLogFile)
    : pInventory(inventory),
      pSalesData(salesData),
      pCashRegister(cashRegister),
      pInventoryFile(inventoryFile),
      pAdminLogFile(adminLogFile) {}

void Admin::saveInventory() const {
    std::ofstream out(pInventoryFile);
    if (!out) {
        std::cerr << "ERROR: could not write " << pInventoryFile << "\n";
        return;
    }
    for (const auto& item : pInventory) {
        float priceFloat = item->getPrice() / 100.0f;
        out << item->getCode() << ','
            << item->getName() << ','
            << std::fixed << std::setprecision(2) << priceFloat << ','
            << item->getQuantity() << '\n';
    }
}

void Admin::removeItem(int code) {
    auto it = std::find_if(pInventory.begin(), pInventory.end(),
        [&](const std::unique_ptr<Product>& i){ return i->getCode() == code; });
    if (it == pInventory.end()) {
        std::cout << "Invalid code. No item removed.\n";
        return;
    }
    pInventory.erase(it);
    saveInventory();
    std::cout << "Item removed.\n";
}

void Admin::showSalesReport() const {
    std::cout << "Cash Register Balance: $"
              << std::fixed << std::setprecision(2)
              << (pCashRegister.getBalance() / 100.0f) << "\n\n";
    std::cout << "Total Sales: $"
              << std::fixed << std::setprecision(2)
              << pSalesData.getTotalSales() << "\n\n";
    std::cout << "Items sold:\n";
    for (auto& p : pSalesData.getItemsSold()) {
        int code = p.first, qty = p.second;
        auto it = std::find_if(pInventory.begin(), pInventory.end(),
            [&](const std::unique_ptr<Product>& i){ return i->getCode() == code; });
        std::string name = (it != pInventory.end() ? (*it)->getName() : "Unknown");
        std::cout << "  " << name << " (code " << code << "): " << qty << "\n";
    }
    std::cout << "\n-- Raw Purchase Log --\n";
    std::ifstream logIn(pAdminLogFile);
    if (!logIn) {
        std::cout << "  <no purchases logged yet>\n";
    } else {
        std::string line;
        while (std::getline(logIn, line)) {
            std::cout << "  " << line << "\n";
        }
    }
}

void Admin::setItemPrice(int code, int newPriceCents) {
    auto it = std::find_if(pInventory.begin(), pInventory.end(),
        [&](std::unique_ptr<Product>& i){ return i->getCode() == code; });
    if (it == pInventory.end()) {
        std::cout << "Invalid code. Price not updated.\n";
        return;
    }
    (*it)->setPrice(newPriceCents);
    saveInventory();
    std::cout << "Price updated.\n";
}

void Admin::restockItem(int code, int quantity) {
    auto it = std::find_if(pInventory.begin(), pInventory.end(),
        [&](std::unique_ptr<Product>& i){ return i->getCode() == code; });
    if (it == pInventory.end()) {
        std::cout << "Invalid code. Stock not updated.\n";
        return;
    }
    (*it)->addStock(quantity);
    saveInventory();
    std::cout << "Stock updated.\n";
}
