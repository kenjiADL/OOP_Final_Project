#include "TransactionHistory.h"
#include <stdexcept>
#include <iomanip>

// Constructor
TransactionHistory::TransactionHistory(int initialCapacity) 
    : size(0), capacity(initialCapacity) {
    if (capacity <= 0) {
        capacity = 10;  // Default minimum capacity
    }
    transactions = new std::string[capacity];  // Raw dynamic allocation
}

// Copy constructor (deep copy)
TransactionHistory::TransactionHistory(const TransactionHistory& other) 
    : transactions(nullptr), size(0), capacity(0) {
    copyFrom(other);
}

// Assignment operator (deep copy)
TransactionHistory& TransactionHistory::operator=(const TransactionHistory& other) {
    if (this != &other) {  // Self-assignment check
        delete[] transactions;  // Free existing memory
        copyFrom(other);
    }
    return *this;
}

// Destructor
TransactionHistory::~TransactionHistory() {
    delete[] transactions;  // Free dynamically allocated memory
    transactions = nullptr;
}

// Add a new transaction
void TransactionHistory::addTransaction(const std::string& transaction) {
    if (size >= capacity) {
        resize();  // Expand array if needed
    }
    transactions[size] = transaction;
    size++;
}

// Get transaction by index with bounds checking
const std::string& TransactionHistory::getTransaction(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Transaction index out of range");
    }
    return transactions[index];
}

// Operator overloading for array-like access
const std::string& TransactionHistory::operator[](int index) const {
    return getTransaction(index);  // Reuse bounds checking
}

// Operator overloading for stream output
std::ostream& operator<<(std::ostream& os, const TransactionHistory& history) {
    os << "=== Transaction History ===\n";
    os << "Total Transactions: " << history.size << "\n";
    os << "Array Capacity: " << history.capacity << "\n";
    os << "Memory Usage: " << (history.capacity * sizeof(std::string)) << " bytes\n\n";
    
    for (int i = 0; i < history.size; i++) {
        os << std::setw(3) << (i + 1) << ". " << history.transactions[i] << "\n";
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

// Clear all transactions
void TransactionHistory::clear() {
    size = 0;  // Reset size (don't need to clear strings, just reset counter)
}

// Private helper: Resize the array when capacity is exceeded
void TransactionHistory::resize() {
    int newCapacity = capacity * 2;  // Double the capacity
    std::string* newTransactions = new std::string[newCapacity];  // Allocate new array
    
    // Copy existing data to new array
    for (int i = 0; i < size; i++) {
        newTransactions[i] = transactions[i];
    }
    
    delete[] transactions;  // Free old array
    transactions = newTransactions;
    capacity = newCapacity;
}

// Private helper: Deep copy from another TransactionHistory
void TransactionHistory::copyFrom(const TransactionHistory& other) {
    size = other.size;
    capacity = other.capacity;
    transactions = new std::string[capacity];  // Allocate new array
    
    // Copy all transactions
    for (int i = 0; i < size; i++) {
        transactions[i] = other.transactions[i];
    }
} 