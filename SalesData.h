#ifndef SALESDATA_H
#define SALESDATA_H

#include <map>

// Tracks total sales and quantities sold per item.
class SalesData
{
public:
    // Initializes sales totals.
    SalesData();

    // Returns total revenue.
    float getTotalSales() const;

    // Returns map of item code to quantity sold.
    const std::map<int, int> &getItemsSold() const;

    // Records a sale for given item code and price.
    void recordSale(int code, float price);

private:
    float mTotalSales;
    std::map<int, int> mItemsSold;
};

#endif // SALESDATA_H