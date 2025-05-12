#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <map>

class SalesData {
private:
    float mTotalSales;
    std::map<std::string,int> mItemsSold;

public:
    SalesData();

    // Record a sale: add price to total and increment count for this code
    void recordSale(const std::string& code, float price);

    // Get total revenue
    float getTotalSales() const;

    // Get map of code → quantity sold
    const std::map<std::string,int>& getItemsSold() const;
};

#endif // SALES_DATA_H
