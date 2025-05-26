#ifndef SALES_REPORT_H
#define SALES_REPORT_H

#include <string>
#include <map>

using namespace std;

// Tracks total sales and quantities sold per item.
class SalesReport
{
 public:
  // Initializes sales totals.
  SalesReport();

  // Returns total revenue.
  float getTotalSales() const;

  // Returns map of item code to quantity sold.
  const map<int, int>& getItemsSold() const;

  // Records a sale for given item code and price in cents.
  void recordSale(int code, int priceCents);
  // Load historical sales from the log file.
  void loadFromLog(const string& logFile);

 private:
  int pTotalSalesCents;
  map<int, int> pItemsSold;
};

#endif // SALES_REPORT_H