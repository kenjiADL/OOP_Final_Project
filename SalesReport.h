#pragma once

#include <string>
#include <map>

// Tracks total sales and quantities sold per item.
class SalesReport
{
 public:
  // Initializes sales totals.
  SalesReport();

  // Returns total revenue.
  float getTotalSales() const;

  // Returns map of item code to quantity sold.
  const std::map<int, int>& getItemsSold() const;

  // Records a sale for given item code and price.
  void recordSale(int code, float price);
  // Load historical sales from the log file.
  void loadFromLog(const std::string& logFile);

 private:
  float pTotalSales;
  std::map<int, int> pItemsSold;
};