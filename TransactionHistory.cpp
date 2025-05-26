#include "TransactionHistory.h"
#include <stdexcept>
#include <iomanip>
#include <fstream>

using namespace std;

// Constructor
TransactionHistory::TransactionHistory(int initialCapacity) 
    : size(0), capacity(initialCapacity), pHistoryFile("transactions.txt") {
    if (capacity <= 0) {
        capacity = 10;  // Minimum size
    }
    transactions = new string[capacity];
}

// File-based constructor
TransactionHistory::TransactionHistory(const string& historyFile)
    : size(0), capacity(10), pHistoryFile(historyFile) {
    transactions = new string[capacity];
    loadFromFile();
}

// Deep copy constructor - needed for Rule of Three
TransactionHistory::TransactionHistory(const TransactionHistory& other) 
    : transactions(nullptr), size(0), capacity(0) {
    copyFrom(other);
}

// Assignment with self-assignment protection
TransactionHistory& TransactionHistory::operator=(const TransactionHistory& other) {
    if (this != &other) {
        delete[] transactions;
        copyFrom(other);
    }
    return *this;
}

// Destructor
TransactionHistory::~TransactionHistory() {
    delete[] transactions;
    transactions = nullptr;
}

// Add a new transaction
void TransactionHistory::addTransaction(const string& transaction) {
    if (size >= capacity) {
        resize(capacity * 2);  // Double the size
    }
    transactions[size++] = transaction;
}

void TransactionHistory::addTransaction(const Payment& payment) {
    string methodName = (payment.getMethod() == PaymentMethod::Cash) ? "Cash" : "Card";
    addTransaction("Payment: $" + to_string(payment.getAmount() / 100.0) + 
                  " - Method: " + methodName);
}

// Get transaction by index with bounds checking
const string& TransactionHistory::getTransaction(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Transaction index out of range");
    }
    return transactions[index];
}

// Operator overloading for array-like access
const string& TransactionHistory::operator[](int index) const {
    return getTransaction(index);  // Reuse bounds checking
}

// Operator overloading for stream output
ostream& operator<<(ostream& os, const TransactionHistory& history) {
    os << "=== Transaction History ===\n";
    os << "Total Transactions: " << history.size << "\n";
    
    for (int i = 0; i < history.size; i++) {
        os << setw(3) << (i + 1) << ". " << history.transactions[i] << "\n";
    }
    
    if (history.size == 0) {
        os << "No transactions recorded.\n";
    }
    
    return os;
}

// Getter implementations
int TransactionHistory::getSize() const {
    return size;
}

int TransactionHistory::getCapacity() const {
    return capacity;
}

// Clear all transactions with optional shrinking
void TransactionHistory::clear(bool shrink) {
    size = 0;
    if (shrink) {
        shrinkToFit();
    }
}

// Optimize memory usage
void TransactionHistory::shrinkToFit() {
    if (size < capacity) {
        resize(max(size, 10));  // Keep minimum capacity of 10
    }
}

// Save transactions to file
bool TransactionHistory::saveToFile() const {
    try {
        ofstream file(pHistoryFile);
        if (!file) {
            return false;
        }
        
        for (int i = 0; i < size; i++) {
            file << transactions[i] << "\n";
        }
        return true;
    }
    catch (...) {
        return false;
    }
}

// Load transactions from file
bool TransactionHistory::loadFromFile() {
    try {
        ifstream file(pHistoryFile);
        if (!file) {
            return false;
        }
        
        clear();  // Clear existing transactions
        string line;
        while (getline(file, line)) {
            addTransaction(line);
        }
        return true;
    }
    catch (...) {
        return false;
    }
}

// Private helper: Resize the array
void TransactionHistory::resize(int newCapacity) {
    if (newCapacity < size) {
        throw invalid_argument("New capacity cannot be smaller than current size");
    }
    
    string* newTransactions = new string[newCapacity];
    for (int i = 0; i < size; i++) {
        newTransactions[i] = transactions[i];
    }
    
    delete[] transactions;
    transactions = newTransactions;
    capacity = newCapacity;
}

// Private helper: Deep copy from another TransactionHistory
void TransactionHistory::copyFrom(const TransactionHistory& other) {
    size = other.size;
    capacity = other.capacity;
    pHistoryFile = other.pHistoryFile;
    transactions = new string[capacity];
    
    for (int i = 0; i < size; i++) {
        transactions[i] = other.transactions[i];
    }
} 