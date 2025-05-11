#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>
#include <chrono>
#include <ctime>

#include "Item.h"
#include "CashRegister.h"
#include "Payment.h"
#include "Change.h"
#include "SalesData.h"
#include "PaymentMethod.h"

static const std::string INVENTORY_FILE   = "inventory.txt";
static const std::string ADMIN_LOG_FILE   = "purchase_history.txt";
static const std::string SECRET_PASSWORD  = "admin123";
static const std::string ADMIN_TRIGGER    = "S";

// write out the updated inventory
void saveInventory(const std::vector<Item>& inventory) {
    std::ofstream out(INVENTORY_FILE);
    if (!out) {
        std::cerr << "ERROR: could not write " << INVENTORY_FILE << "\n";
        return;
    }
    for (auto& item : inventory) {
        out << item.getCode()   << ' '
            << item.getName()   << ' '
            << item.getPrice()  << ' '
            << item.getQuantity() << '\n';
    }
}

// append a single purchase record
void logPurchase(int code,
                 const std::string& name,
                 float totalCost)
{
    std::ofstream log(ADMIN_LOG_FILE, std::ios::app);
    if (!log) {
        std::cerr << "ERROR: could not write " << ADMIN_LOG_FILE << "\n";
        return;
    }
    // timestamp
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    // line format: code name totalCost YYYY-MM-DD HH:MM:SS
    char buf[32];
    std::strftime(buf, sizeof(buf), "%F %T", std::localtime(&t));
    log << code << ' '
        << name << ' '
        << totalCost << ' '
        << buf << '\n';
}

int main() {
    // load inventory (fixed file, not user-selectable)
    std::vector<Item> inventory;
    {
        std::ifstream in(INVENTORY_FILE);
        if (!in) {
            std::cerr << "Failed to open " << INVENTORY_FILE << "\n";
            return 1;
        }
        int code, qty;
        std::string name;
        float price;
        while (in >> code >> name >> price >> qty) {
            inventory.emplace_back(code, name, price, qty);
        }
    }

    SalesData    salesData;
    CashRegister cashRegister;

    // welcome & list
    std::cout << "Welcome to the Vending Machine Simulator!\n\n";
    std::cout << "Available Items:\n";
    for (auto& it : inventory) {
        std::cout
            << it.getCode() << ": "
            << it.getName() << " ($" << it.getPrice()
            << ") x" << it.getQuantity() << "\n";
    }
    std::cout << "\n";

    // single-purchase loop
    std::string input;
    std::cout << "Enter item code to purchase ("
              << ADMIN_TRIGGER << " for admin): ";
    std::cin >> input;

    // admin view
    if (input == ADMIN_TRIGGER) {
        std::cout << "Enter secret password: ";
        std::string pw;
        std::cin >> pw;
        if (pw == SECRET_PASSWORD) {
            std::cout << "\n-- Admin View --\n\nInventory:\n";
            for (auto& it : inventory) {
                std::cout
                    << it.getCode() << ": "
                    << it.getName() << " ($" << it.getPrice()
                    << ") x" << it.getQuantity() << "\n";
            }
            std::cout << "\nPurchase Log:\n";
            std::ifstream logIn(ADMIN_LOG_FILE);
            if (!logIn) {
                std::cout << "  <no purchases logged yet>\n";
            } else {
                std::string line;
                while (std::getline(logIn, line)) {
                    std::cout << "  " << line << "\n";
                }
            }
        } else {
            std::cout << "Incorrect password.\n";
        }
        return 0;
    }

    // parse code
    int code = 0;
    try {
        size_t pos;
        code = std::stoi(input, &pos);
        if (pos != input.size()) throw std::invalid_argument("");
    } catch (...) {
        std::cout << "Invalid code entry.\n";
        return 0;
    }

    // find item
    auto it = std::find_if(
        inventory.begin(), inventory.end(),
        [&](const Item& i){ return i.getCode() == code; }
    );
    if (it == inventory.end() || it->getQuantity() == 0) {
        std::cout << "Invalid code or out of stock.\n";
        return 0;
    }

    // choose payment method
    std::cout << "Payment method (1 = Cash, 2 = Card): ";
    int pm; std::cin >> pm;
    PaymentMethod method =
        (pm == 2 ? PaymentMethod::Card : PaymentMethod::Cash);

    // compute surcharge & payment
    float surcharge    = (method == PaymentMethod::Card ? 0.25f : 0.0f);
    float itemPrice    = it->getPrice();
    float totalCost    = itemPrice + surcharge;
    Payment payment(0.0f, method);

    if (method == PaymentMethod::Cash) {
        std::cout << "Enter payment amount: ";
        float amt; std::cin >> amt;
        payment = Payment(amt, method);
        if (payment.getChargedAmount() < totalCost) {
            std::cout << "Insufficient funds.\n";
            return 0;
        }
    } else {
        // card: no prompt, just set base amount = price
        payment = Payment(itemPrice, method);
    }

    // complete the sale
    cashRegister.addPayment(totalCost);
    it->reduceQuantity();
    salesData.recordSale(code, totalCost);
    logPurchase(code, it->getName(), totalCost);
    saveInventory(inventory);

    // dispense change
    float changeAmt = cashRegister.dispenseChange(
        payment.getChargedAmount() - totalCost
    );
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
