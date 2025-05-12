#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <ctime>

#include "Item.h"
#include "CashRegister.h"
#include "Payment.h"
#include "SalesData.h"
#include "PaymentMethod.h"

static const std::string INVENTORY_FILE   = "inventory.txt";
static const std::string ADMIN_LOG_FILE   = "purchase_history.txt";
static const std::string ADMIN_TRIGGER    = "S";
static const std::string SECRET_PASSWORD  = "admin123";

// 20% off between 16:00–18:00
bool isHappyHour() {
    using namespace std::chrono;
    auto now    = system_clock::now();
    time_t t    = system_clock::to_time_t(now);
    tm localTm  = *std::localtime(&t);
    return (localTm.tm_hour >= 16 && localTm.tm_hour < 18);
}

// Overwrite inventory.txt with current stock
void saveInventory(const std::vector<Item>& inv) {
    std::ofstream out(INVENTORY_FILE);
    if (!out) {
        std::cerr << "ERROR: cannot write " << INVENTORY_FILE << "\n";
        return;
    }
    for (const auto& it : inv) {
        out << it.getCode()   << ' '
            << it.getName()   << ' '
            << it.getPrice()  << ' '
            << it.getQuantity()
            << '\n';
    }
}

// Append one purchase record
void logPurchase(const std::string& code,
                 const std::string& name,
                 float totalCost)
{
    std::ofstream log(ADMIN_LOG_FILE, std::ios::app);
    if (!log) {
        std::cerr << "ERROR: cannot write " << ADMIN_LOG_FILE << "\n";
        return;
    }
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%F %T", std::localtime(&t));
    log << code << ' '
        << name << ' '
        << totalCost << ' '
        << buf << '\n';
}

int main() {
    // --- Load inventory ---
    std::vector<Item> inventory;
    {
        std::ifstream in(INVENTORY_FILE);
        if (!in) {
            std::cerr << "Failed to open " << INVENTORY_FILE << "\n";
            return 1;
        }
        std::string code, name;
        float price;
        int qty;
        while (in >> code >> name >> price >> qty) {
            inventory.emplace_back(code, name, price, qty);
        }
    }

    SalesData    salesData;
    CashRegister cashRegister;

    // --- Display as ASCII table ---
    std::cout
      << "+------+------------------+--------+-----+\n"
      << "| Code | Name             | Price  | Qty |\n"
      << "+------+------------------+--------+-----+\n";
    for (const auto& it : inventory) {
        std::cout
          << "| " << std::setw(4) << it.getCode()   << " "
          << "| " << std::setw(16)<< it.getName()   << " "
          << "| " << std::setw(6)
                   << std::fixed<<std::setprecision(2)
                   << it.getPrice()                 << " "
          << "| " << std::setw(3) << it.getQuantity() << " |\n";
    }
    std::cout
      << "+------+------------------+--------+-----+\n\n";

    // --- Prompt for code or admin ---
    std::string input;
    std::cout 
      << "Enter item code to purchase ("
      << ADMIN_TRIGGER << " for admin): ";
    std::cin >> input;

    // --- Admin flow ---
    if (input == ADMIN_TRIGGER) {
        std::cout << "Enter secret password: ";
        std::string pw; std::cin >> pw;
        if (pw == SECRET_PASSWORD) {
            while (true) {
                std::cout
                  << "\n-- Admin Menu --\n"
                  << "1) Set item price\n"
                  << "2) Change stock\n"
                  << "3) Exit admin\n"
                  << "Select option: ";
                int opt; std::cin >> opt;

                if (opt == 1) {
                    std::cout << "Enter code to change price: ";
                    std::string code; std::cin >> code;
                    auto it = std::find_if(
                        inventory.begin(), inventory.end(),
                        [&](auto &i){ return i.getCode() == code; }
                    );
                    if (it == inventory.end()) {
                        std::cout << "Code not found.\n";
                    } else {
                        std::cout << "Current price: $"
                                  << it->getPrice()
                                  << "\nNew price: $";
                        float np; std::cin >> np;
                        it->setPrice(np);
                        saveInventory(inventory);
                        std::cout << "Price updated.\n";
                    }
                }
                else if (opt == 2) {
                    std::cout << "Enter code to change stock: ";
                    std::string code; std::cin >> code;
                    auto it = std::find_if(
                        inventory.begin(), inventory.end(),
                        [&](auto &i){ return i.getCode() == code; }
                    );
                    if (it == inventory.end()) {
                        std::cout << "Code not found.\n";
                    } else {
                        std::cout << "Current quantity: "
                                  << it->getQuantity()
                                  << "\nNew quantity: ";
                        int nq; std::cin >> nq;
                        it->setQuantity(nq);
                        saveInventory(inventory);
                        std::cout << "Stock updated.\n";
                    }
                }
                else if (opt == 3) {
                    break;
                }
                else {
                    std::cout << "Invalid option; enter 1, 2, or 3.\n";
                }
            }
        } else {
            std::cout << "Incorrect password.\n";
        }
        return 0;
    }

    // --- Customer flow ---
    auto it = std::find_if(
        inventory.begin(), inventory.end(),
        [&](const Item& i){ return i.getCode() == input; }
    );
    if (it == inventory.end() || it->getQuantity() == 0) {
        std::cout << "Invalid code or out of stock.\n";
        return 0;
    }

    // Payment method selection
    int pm = 0;
    while (true) {
        std::cout << "Payment method (1=Cash, 2=Card): ";
        if (!(std::cin >> pm) || (pm != 1 && pm != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 or 2.\n";
            continue;
        }
        break;
    }
    PaymentMethod method = (pm == 2 ? PaymentMethod::Card : PaymentMethod::Cash);

    // Calculate price + discount + surcharge
    float itemPrice = it->getPrice();
    if (isHappyHour()) {
        std::cout << "*** Happy Hour! 20% off! ***\n";
        itemPrice *= 0.80f;
    }
    float surcharge = (method == PaymentMethod::Card ? 0.25f : 0.0f);
    float totalCost = itemPrice + surcharge;

    // Show card charge if card
    if (method == PaymentMethod::Card) {
        std::cout << "Card charged (including surcharge): $"
                  << std::fixed << std::setprecision(2)
                  << totalCost << "\n";
    }

    // Handle payment input
    float paidAmount = 0.0f;
    if (method == PaymentMethod::Cash) {
        while (true) {
            std::cout << "Enter payment amount: ";
            if (!(std::cin >> paidAmount) || paidAmount < totalCost) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Need at least $"
                          << std::fixed << std::setprecision(2)
                          << totalCost << "\n";
                continue;
            }
            break;
        }
    } else {
        // For card, treat paidAmount = totalCost
        paidAmount = totalCost;
    }

    // Finalize sale
    cashRegister.addPayment(totalCost);
    it->reduceQuantity();
    std::cout << "(Item dispensed)\n";
    salesData.recordSale(input, totalCost);
    logPurchase(input, it->getName(), totalCost);
    saveInventory(inventory);

    // Simple change = paidAmount - totalCost
    float changeAmt = paidAmount - totalCost;
    std::cout << "Change returned: $"
              << std::fixed << std::setprecision(2)
              << changeAmt << "\n";

    std::cout << "\nThank you for your purchase!\n";
    return 0;
}
