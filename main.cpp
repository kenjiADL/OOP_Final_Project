#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <memory>
#include "Product.h"
#include "Snack.h"
#include "Drink.h"
#include "Admin.h"
#include "CRegister.h"
#include "Payment.h"
#include "Change.h"
#include "SalesReport.h"
#include "PaymentMethod.h"

// Show all items with their codes, descriptions, and quantities.
static void printInventory(const std::vector<std::unique_ptr<Product>>& inventory) {
    for (const auto& p : inventory) {
        std::cout << p->getCode() << ": "
                  << p->describe()
                  << " x" << p->getQuantity() << "\n";
    }
}

static const std::string kInventoryFile   = "inventory.txt";
static const std::string kAdminLogFile   = "purchase_history.txt";
static const std::string kSecretPassword  = "admin123";
static const std::string kAdminTrigger    = "S";

// Save the current inventory to the file so changes are persistent.
void saveInventory(const std::vector<std::unique_ptr<Product>>& inventory) {
    std::ofstream out(kInventoryFile);
    if (!out) {
        std::cerr << "ERROR: could not write " << kInventoryFile << "\n";
        return;
    }
    for (const auto& item : inventory) {
        float priceFloat = item->getPrice() / 100.0f;
        out << item->getCode()   << ','
            << item->getName()     << ','
            << priceFloat      << ','
            << item->getQuantity() << '\n';
    }
}

// Append a purchase entry to the admin log with timestamp.
void logPurchase(int code,
                 const std::string& name,
                 float totalCost)
{
    std::ofstream log(kAdminLogFile, std::ios::app);
    if (!log) {
        std::cerr << "ERROR: could not write " << kAdminLogFile << "\n";
        return;
    }
    // Get current time for the log entry.
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    // Log format: code, item name in quotes, cost, and timestamp YYYY-MM-DD HH:MM:SS.
    char buf[32];
    std::strftime(buf, sizeof(buf), "%F %T", std::localtime(&t));
    log << code << ' ' << '"' << name << '"' << ' ' << totalCost << ' ' << buf << '\n';
}

int main() {
    // Load inventory from the default file (not user-configurable).
    std::vector<std::unique_ptr<Product>> inventory;
    {
        std::ifstream in(kInventoryFile);
        if (!in) {
            std::cerr << "Failed to open " << kInventoryFile << "\n";
            return 1;
        }
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string token;
            std::getline(ss, token, ',');
            int code = std::stoi(token);
            std::getline(ss, token, ',');
            std::string name = token;
            std::getline(ss, token, ',');
            float priceFloat = std::stof(token);
            int priceCents = static_cast<int>(std::round(priceFloat * 100));
            std::getline(ss, token, ',');
            int qty = std::stoi(token);
            // For now, load all items as Snack; later you can dispatch to Drink based on data.
            inventory.emplace_back(
                std::make_unique<Snack>(code, name, priceCents, qty)
            );
        }
    }

    SalesReport    salesData;
    // Load previous sales from log to build up totals.
    salesData.loadFromLog(kAdminLogFile);
    CRegister cashRegister;
    // Greet the user and display available items.
    std::cout << "Welcome to the Vending Machine Simulator!\n\n";
    std::cout << "Available Items:\n";
    printInventory(inventory);
    std::cout << "\n";

    // single-purchase loop
    std::string input;
    std::cout << "Enter item code to purchase ("
              << kAdminTrigger << " for admin): ";
    std::cin >> input;

    // Enter admin mode if triggered and authenticated.
    if (input == kAdminTrigger) {
        std::cout << "Enter secret password: ";
        std::string pw;
        std::cin >> pw;
        if (pw == kSecretPassword) {
            Admin admin(inventory, salesData, cashRegister, kInventoryFile, kAdminLogFile);
            bool done = false;
            while (!done) {
                std::cout << "\n-- Admin Menu --\n"
                          << "1) Remove Item\n"
                          << "2) Show Sales Report\n"
                          << "3) Set Item Price\n"
                          << "4) Restock Item\n"
                          << "5) Exit Admin\n"
                          << "Select option: ";
                int opt;
                std::cin >> opt;
                switch (opt) {
                    case 1: {
                        std::cout << "Enter code to remove: ";
                        int code; std::cin >> code;
                        admin.removeItem(code);
                        break;
                    }
                    case 2:
                        admin.showSalesReport();
                        break;
                    case 3: {
                        std::cout << "Enter code to update price: ";
                        int code; std::cin >> code;
                        std::cout << "Enter new price (e.g. 1.50): ";
                        float p; std::cin >> p;
                        admin.setItemPrice(code, static_cast<int>(std::round(p * 100)));
                        break;
                    }
                    case 4: {
                        std::cout << "Enter code to restock: ";
                        int code; std::cin >> code;
                        std::cout << "Enter quantity to add: ";
                        int qty; std::cin >> qty;
                        admin.restockItem(code, qty);
                        break;
                    }
                    case 5:
                        done = true;
                        break;
                    default:
                        std::cout << "Invalid option.\n";
                }
            }
        } else {
            std::cout << "Incorrect password.\n";
        }
        return 0;
    }

    // Convert input into item code, handling errors.
    int code = 0;
    try {
        size_t pos;
        code = std::stoi(input, &pos);
        if (pos != input.size()) throw std::invalid_argument("");
    } catch (...) {
        std::cout << "Invalid code entry.\n";
        return 0;
    }

    // Locate the item by its code and check stock.
    auto it = std::find_if(
        inventory.begin(), inventory.end(),
        [&](const std::unique_ptr<Product>& i){ return i->getCode() == code; }
    );
    if (it == inventory.end() || (*it)->getQuantity() == 0) {
        std::cout << "Invalid code or out of stock.\n";
        return 0;
    }

    // Ask customer for payment method: cash or card.
    std::cout << "Payment method (1 = Cash, 2 = Card): ";
    int pm; std::cin >> pm;
    PaymentMethod method =
        (pm == 2 ? PaymentMethod::Card : PaymentMethod::Cash);

    // Calculate payment amount in cents.
    int itemPriceCents = (*it)->getPrice();
    Payment payment(0, method);

    if (method == PaymentMethod::Cash) {
        std::cout << "Enter payment amount: ";
        float amtInput; std::cin >> amtInput;
        int amtCents = static_cast<int>(std::round(amtInput * 100));
        payment = Payment(amtCents, method);
        if (payment.getChargedAmount() < itemPriceCents) {
            std::cout << "Insufficient funds.\n";
            return 0;
        }
    } else {
        // card: no prompt, just set base amount = price
        payment = Payment(itemPriceCents, method);
    }

    // Process the sale: update cash, stock, sales data, and log.
    if (payment.getMethod() == PaymentMethod::Cash) {
        cashRegister.addPayment(payment.getChargedAmount());
    }
    (*it)->reduceQuantity();
    salesData.recordSale(code, itemPriceCents / 100.0f); // keep float for log
    logPurchase(code, (*it)->describe(), itemPriceCents / 100.0f);
    saveInventory(inventory);

    // Calculate and dispense change in coins.
    int changeDue = payment.getAmount() - itemPriceCents;
    int changeAmt = cashRegister.dispenseChange(changeDue);
    Change change(changeAmt);
    std::cout << "Change returned:\n";
    for (auto& p : change.getChangeBreakdown()) {
        std::cout
            << p.first << "c x "
            << p.second << " coins\n";
    }

    std::cout << "\nThank you for your purchase!\n";
    return 0;
}
