# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
SRC = main.cpp \
      CRegister.cpp \
      Change.cpp \
      Payment.cpp \
      SalesReport.cpp \
      Admin.cpp \
      Product.cpp \
      Snack.cpp \
      Drink.cpp \
      Alcoholic.cpp \
      TransactionHistory.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable name
TARGET = vending_machine

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)


.PHONY: all clean

# Google Test integration
GTEST_DIR = external/googletest
GTEST_INC = -I$(GTEST_DIR)/googletest/include -I$(GTEST_DIR)/googletest -I.
GTEST_SRCS = $(GTEST_DIR)/googletest/src/gtest-all.cc $(GTEST_DIR)/googletest/src/gtest_main.cc
TEST_SRCS = tests/test_snack_gtest.cpp \
            tests/test_drink_gtest.cpp \
            tests/test_alcoholic_gtest.cpp \
            tests/test_payment_gtest.cpp \
            tests/test_cregister_gtest.cpp \
            tests/test_change_gtest.cpp \
            tests/test_admin_gtest.cpp \
            tests/test_product_gtest.cpp \
            tests/test_salesreport_gtest.cpp \
            tests/test_transactionhistory_gtest.cpp

.PHONY: test
test:
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -pthread \
	  $(GTEST_SRCS) $(TEST_SRCS) \
	  Admin.cpp Product.cpp Snack.cpp Drink.cpp Alcoholic.cpp TransactionHistory.cpp SalesReport.cpp Payment.cpp CRegister.cpp Change.cpp \
	  -o test_runner
	./test_runner
