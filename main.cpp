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
#include "Alcoholic.h"
#include "Admin.h"
#include "CRegister.h"
#include "Payment.h"
#include "Change.h"
#include "SalesReport.h"
#include "PaymentMethod.h"
#include "TransactionHistory.h"

using namespace std;

// Show all items with their codes, descriptions, and quantities.
static void printInventory(const vector<unique_ptr<Product>>& inventory) {
    for (const auto& p : inventory) {
        cout << p->getCode() << ": "
                  << p->describe()
                  << " x" << p->getQuantity() << "\n";
    }
}

static const string kInventoryFile   = "inventory.txt";
static const string kAdminLogFile   = "purchase_history.txt";
static const string kSecretPassword  = "admin123";
static const string kAdminTrigger    = "S";

// Save the current inventory to the file so changes are persistent.
void saveInventory(const vector<unique_ptr<Product>>& inventory) {
    ofstream out(kInventoryFile);
    if (!out) {
        cerr << "ERROR: could not write " << kInventoryFile << "\n";
        return;
    }
    for (const auto& item : inventory) {
        float priceFloat = item->getPrice() / 100.0f;
        string type;
        if (dynamic_cast<Alcoholic*>(item.get())) {
            type = "alcoholic";
        } else if (dynamic_cast<Drink*>(item.get())) {
            type = "drink";
        } else {
            type = "snack";
        }
        out << item->getCode()   << ','
            << item->getName()     << ','
            << type << ','
            << fixed << setprecision(2) << priceFloat << ','
            << item->getQuantity() << '\n';
    }
}

// Append a purchase entry to the admin log with timestamp.
void logPurchase(int code,
                 const string& name,
                 float totalCost)
{
    ofstream log(kAdminLogFile, ios::app);
    if (!log) {
        cerr << "ERROR: could not write " << kAdminLogFile << "\n";
        return;
    }
    // Get current time for the log entry.
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

    // Log format: code, item name in quotes, cost, and timestamp YYYY-MM-DD HH:MM:SS.
    char buf[32];
    strftime(buf, sizeof(buf), "%F %T", localtime(&t));
    log << code << ' ' << '"' << name << '"' << ' ' << totalCost << ' ' << buf << '\n';
}

int main() {
    // Load inventory from the default file (not user-configurable).
    vector<unique_ptr<Product>> inventory;
    {
        ifstream in(kInventoryFile);
        if (!in) {
            cerr << "Failed to open " << kInventoryFile << "\n";
            return 1;
        }
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            int code = stoi(token);
            getline(ss, token, ',');
            string name = token;
            getline(ss, token, ',');
            string type = token;
            getline(ss, token, ',');
            float priceFloat = stof(token);
            int priceCents = static_cast<int>(round(priceFloat * 100));
            getline(ss, token, ',');
            int qty = stoi(token);

            if (type == "alcoholic") {
                bool isDiet = name.find("Diet") != string::npos;
                inventory.emplace_back(make_unique<Alcoholic>(code, name, priceCents, qty, isDiet));
            } else if (type == "drink") {
                bool isDiet = name.find("Diet") != string::npos;
                inventory.emplace_back(make_unique<Drink>(code, name, priceCents, qty, isDiet));
            } else {
                inventory.emplace_back(make_unique<Snack>(code, name, priceCents, qty));
            }
        }
    }

    SalesReport    salesData;
    // Load previous sales from log to build up totals.
    salesData.loadFromLog(kAdminLogFile);
    CRegister cashRegister;
    
    // Create transaction history using raw dynamic memory allocation
    TransactionHistory* transactionHistory = new TransactionHistory(5);
    // Greet the user and display available items.
    cout << "Welcome to the Vending Machine Simulator!\n\n";
    cout << "Available Items:\n";
    printInventory(inventory);
    cout << "\n";

    // single-purchase loop
    string input;
    cout << "Enter item code to purchase ("
              << kAdminTrigger << " for admin): ";
    cin >> input;

    // Enter admin mode if triggered and authenticated.
    if (input == kAdminTrigger) {
        cout << "Enter secret password: ";
        string pw;
        cin >> pw;
        if (pw == kSecretPassword) {
            Admin admin(inventory, salesData, cashRegister, kInventoryFile, kAdminLogFile);
            bool done = false;
            while (!done) {
                cout << "\n-- Admin Menu --\n"
                          << "1) Remove Item\n"
                          << "2) Show Sales Report\n"
                          << "3) Set Item Price\n"
                          << "4) Restock Item\n"
                          << "5) Show Transaction History\n"
                          << "6) Exit Admin\n"
                          << "Select option: ";
                int opt;
                cin >> opt;
                switch (opt) {
                    case 1: {
                        cout << "Enter code to remove: ";
                        int code; cin >> code;
                        admin.removeItem(code);
                        break;
                    }
                    case 2:
                        admin.showSalesReport();
                        break;
                    case 3: {
                        cout << "Enter code to update price: ";
                        int code; cin >> code;
                        cout << "Enter new price (e.g. 1.50): ";
                        float p; cin >> p;
                        admin.setItemPrice(code, static_cast<int>(round(p * 100)));
                        break;
                    }
                    case 4: {
                        cout << "Enter code to restock: ";
                        int code; cin >> code;
                        cout << "Enter quantity to add: ";
                        int qty; cin >> qty;
                        admin.restockItem(code, qty);
                        break;
                    }
                    case 5:
                        // Show transaction history using operator overloading
                        cout << *transactionHistory;
                        break;
                    case 6:
                        done = true;
                        break;
                    default:
                        cout << "Invalid option.\n";
                }
            }
        } else {
            cout << "Incorrect password.\n";
        }
        // Clean up dynamic memory before exiting
        delete transactionHistory;
        return 0;
    }

    // Convert input into item code, handling errors.
    int code = 0;
    try {
        size_t pos;
        code = stoi(input, &pos);
        if (pos != input.size()) throw invalid_argument("");
    } catch (...) {
        cout << "Invalid code entry.\n";
        delete transactionHistory;  // Clean up before exit
        return 0;
    }

    // Locate the item by its code and check stock.
    auto it = find_if(
        inventory.begin(), inventory.end(),
        [&](const unique_ptr<Product>& i){ return i->getCode() == code; }
    );
    if (it == inventory.end() || (*it)->getQuantity() == 0) {
        cout << "Invalid code or out of stock.\n";
        delete transactionHistory;  // Clean up before exit
        return 0;
    }

    // Check if this is an alcoholic drink and verify age
    Alcoholic* alcoholicItem = dynamic_cast<Alcoholic*>(it->get());
    if (alcoholicItem) {
        cout << "This is an alcoholic beverage. Are you 18 years of age or older? (y/n): ";
        char ageResponse;
        cin >> ageResponse;
        if (ageResponse != 'y' && ageResponse != 'Y') {
            cout << "Sorry, you must be 18 years or older to purchase alcoholic beverages.\n";
            delete transactionHistory;  // Clean up before exit
            return 0;
        }
    }

    // Ask customer for payment method: cash or card.
    cout << "Payment method (1 = Cash, 2 = Card): ";
    int pm; cin >> pm;
    PaymentMethod method =
        (pm == 2 ? PaymentMethod::Card : PaymentMethod::Cash);

    // Calculate payment amount in cents.
    int itemPriceCents = (*it)->getPrice();
    Payment payment(0, method);

    if (method == PaymentMethod::Cash) {
        cout << "Enter payment amount: ";
        float amtInput; cin >> amtInput;
        int amtCents = static_cast<int>(round(amtInput * 100));
        payment = Payment(amtCents, method);
        if (payment.getChargedAmount() < itemPriceCents) {
            cout << "Insufficient funds.\n";
            delete transactionHistory;  // Clean up before exit
            return 0;
        }
    } else {
        // card: set base amount = price, surcharge will be added automatically
        payment = Payment(itemPriceCents, method);
        cout << "Card payment processed. Amount charged: $" 
                  << fixed << setprecision(2) 
                  << (payment.getChargedAmount() / 100.0f) 
                  << " (includes $0.25 surcharge)\n";
    }

    // Process the sale: update cash, stock, sales data, and log.
    if (payment.getMethod() == PaymentMethod::Cash) {
        cashRegister.addPayment(payment.getChargedAmount());
    }
    (*it)->reduceQuantity();
    // Record the actual charged amount (including surcharge for cards)
    salesData.recordSale(code, payment.getChargedAmount());
    logPurchase(code, (*it)->getName(), payment.getChargedAmount() / 100.0f);
    saveInventory(inventory);

    // Add transaction to history using dynamic memory
    string transactionRecord = "Item: " + (*it)->getName() + 
                                   ", Price: $" + to_string(payment.getChargedAmount() / 100.0f) +
                                   ", Method: " + (payment.getMethod() == PaymentMethod::Cash ? "Cash" : "Card");
    transactionHistory->addTransaction(transactionRecord);

    // Calculate and dispense change in coins (only for cash payments).
    if (payment.getMethod() == PaymentMethod::Cash) {
        int changeDue = payment.getAmount() - itemPriceCents;
        int changeAmt = cashRegister.dispenseChange(changeDue);
        Change change(changeAmt);
        // Using operator overloading for displaying change
        cout << change;
    }

    cout << "\nThank you for your purchase!\n";
    
    // Clean up dynamically allocated memory before program ends
    delete transactionHistory;
    return 0;
}
