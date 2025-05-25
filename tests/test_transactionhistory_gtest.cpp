#include <gtest/gtest.h>
#include "TransactionHistory.h"
#include <sstream>

// Fixture for TransactionHistory tests
class TransactionHistoryTest : public ::testing::Test {
protected:
    TransactionHistory history{3};  // Start with small capacity to test resizing
};

TEST_F(TransactionHistoryTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(history.getSize(), 0);
    EXPECT_EQ(history.getCapacity(), 3);
}

TEST_F(TransactionHistoryTest, AddTransactionWorks) {
    history.addTransaction("Test transaction 1");
    EXPECT_EQ(history.getSize(), 1);
    EXPECT_EQ(history.getTransaction(0), "Test transaction 1");
}

TEST_F(TransactionHistoryTest, ArrayOperatorOverloading) {
    history.addTransaction("First");
    history.addTransaction("Second");
    
    // Test operator[] overloading
    EXPECT_EQ(history[0], "First");
    EXPECT_EQ(history[1], "Second");
}

TEST_F(TransactionHistoryTest, DynamicResizing) {
    // Add more transactions than initial capacity to test resizing
    history.addTransaction("Transaction 1");
    history.addTransaction("Transaction 2");
    history.addTransaction("Transaction 3");
    EXPECT_EQ(history.getCapacity(), 3);
    
    // This should trigger resize
    history.addTransaction("Transaction 4");
    EXPECT_EQ(history.getSize(), 4);
    EXPECT_EQ(history.getCapacity(), 6);  // Should double
    
    // Verify all data is preserved
    EXPECT_EQ(history[0], "Transaction 1");
    EXPECT_EQ(history[1], "Transaction 2");
    EXPECT_EQ(history[2], "Transaction 3");
    EXPECT_EQ(history[3], "Transaction 4");
}

TEST_F(TransactionHistoryTest, CopyConstructor) {
    history.addTransaction("Original transaction");
    
    TransactionHistory copy(history);
    EXPECT_EQ(copy.getSize(), 1);
    EXPECT_EQ(copy[0], "Original transaction");
    
    // Verify deep copy - changes to original don't affect copy
    history.addTransaction("New transaction");
    EXPECT_EQ(history.getSize(), 2);
    EXPECT_EQ(copy.getSize(), 1);
}

TEST_F(TransactionHistoryTest, AssignmentOperator) {
    history.addTransaction("Test transaction");
    
    TransactionHistory other(5);
    other = history;
    
    EXPECT_EQ(other.getSize(), 1);
    EXPECT_EQ(other[0], "Test transaction");
}

TEST_F(TransactionHistoryTest, StreamOperatorOverloading) {
    history.addTransaction("Transaction 1");
    history.addTransaction("Transaction 2");
    
    std::ostringstream oss;
    oss << history;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Transaction History") != std::string::npos);
    EXPECT_TRUE(output.find("Transaction 1") != std::string::npos);
    EXPECT_TRUE(output.find("Transaction 2") != std::string::npos);
    EXPECT_TRUE(output.find("Total Transactions: 2") != std::string::npos);
}

TEST_F(TransactionHistoryTest, BoundsChecking) {
    history.addTransaction("Test");
    
    // Valid access
    EXPECT_NO_THROW(history.getTransaction(0));
    
    // Invalid access should throw
    EXPECT_THROW(history.getTransaction(-1), std::out_of_range);
    EXPECT_THROW(history.getTransaction(1), std::out_of_range);
}

TEST_F(TransactionHistoryTest, ClearFunctionality) {
    history.addTransaction("Transaction 1");
    history.addTransaction("Transaction 2");
    EXPECT_EQ(history.getSize(), 2);
    
    history.clear();
    EXPECT_EQ(history.getSize(), 0);
} 