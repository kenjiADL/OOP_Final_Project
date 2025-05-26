#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

#include <string>
#include <iostream>
#include <vector>
#include "Payment.h"

using namespace std;

/**
 * @brief Records vending machine transactions
 * 
 * Stores and manages transaction history using dynamic memory.
 */
class TransactionHistory {
public:
    // Initialize with given capacity (default 10)
    explicit TransactionHistory(int initialCapacity = 10);
    
    // Deep copy constructor
    TransactionHistory(const TransactionHistory& other);
    
    // Deep copy assignment
    TransactionHistory& operator=(const TransactionHistory& other);
    
    // Clean up memory
    ~TransactionHistory();
    
    // Load from history file
    explicit TransactionHistory(const string& historyFile);

    // Add new transaction record
    void addTransaction(const string& transaction);
    void addTransaction(const Payment& payment);
    
    // Get current transaction count
    int getSize() const;
    
    // Get array capacity
    int getCapacity() const;
    
    // Get transaction by index (with bounds check)
    const string& getTransaction(int index) const;
    
    // Array access operator
    const string& operator[](int index) const;
    
    // Print all transactions
    friend ostream& operator<<(ostream& os, const TransactionHistory& history);
    
    // Clear all transactions and optionally reduce capacity
    void clear(bool shrink = false);

    // Save/load from file
    bool saveToFile() const;
    bool loadFromFile();

    // Optimize memory usage
    void shrinkToFit();

private:
    string* transactions;       // dynamic array
    int size;                  // current count
    int capacity;              // total space
    string pHistoryFile;       // file path for persistence

    // Grow array when full
    void resize(int newCapacity);
    // Helper for deep copy
    void copyFrom(const TransactionHistory& other);
};

#endif // TRANSACTION_HISTORY_H 