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

  // Records a sale for given item code and price in cents.
  void recordSale(int code, int priceCents);
  // Load historical sales from the log file.
  void loadFromLog(const std::string& logFile);

 private:
  int pTotalSalesCents;
  std::map<int, int> pItemsSold;
};