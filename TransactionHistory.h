#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

#include <string>
#include <iostream>
#include <vector>
#include "Payment.h"

/**
 * @brief Manages a dynamic array of transaction records using raw pointers
 * This class demonstrates raw dynamic memory allocation as required by the rubric
 */
class TransactionHistory {
public:
    /**
     * @brief Constructor that initializes with a given capacity
     * @param initialCapacity Initial size of the dynamic array
     */
    explicit TransactionHistory(int initialCapacity = 10);
    
    /**
     * @brief Copy constructor (deep copy)
     */
    TransactionHistory(const TransactionHistory& other);
    
    /**
     * @brief Assignment operator (deep copy)
     */
    TransactionHistory& operator=(const TransactionHistory& other);
    
    /**
     * @brief Destructor that frees dynamically allocated memory
     */
    ~TransactionHistory();
    
    /**
     * @brief Add a new transaction record
     * @param transaction The transaction string to add
     */
    void addTransaction(const std::string& transaction);
    
    /**
     * @brief Get the number of transactions stored
     */
    int getSize() const;
    
    /**
     * @brief Get the current capacity of the array
     */
    int getCapacity() const;
    
    /**
     * @brief Access transaction by index (with bounds checking)
     * @param index The index of the transaction to retrieve
     * @return Reference to the transaction string
     */
    const std::string& getTransaction(int index) const;
    
    /**
     * @brief Operator overloading for array-like access
     * @param index The index to access
     * @return Reference to the transaction string
     */
    const std::string& operator[](int index) const;
    
    /**
     * @brief Operator overloading for displaying all transactions
     */
    friend std::ostream& operator<<(std::ostream& os, const TransactionHistory& history);
    
    /**
     * @brief Clear all transactions and reset the array
     */
    void clear();

    TransactionHistory(const std::string& historyFile);
    void addTransaction(const Payment& payment);
    void saveToFile() const;
    void loadFromFile();

private:
    std::string* transactions;  // Raw pointer to dynamic array
    int size;                   // Current number of transactions
    int capacity;               // Current capacity of the array
    
    /**
     * @brief Resize the internal array when capacity is exceeded
     */
    void resize();
    
    /**
     * @brief Helper function for deep copying
     */
    void copyFrom(const TransactionHistory& other);

    std::vector<Payment> pTransactions;
    std::string pHistoryFile;
};

#endif // TRANSACTION_HISTORY_H 