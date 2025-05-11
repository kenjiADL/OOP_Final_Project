#include "SalesData.h"

// Initializes revenue and counts to zero.
SalesData::SalesData()
    : mTotalSales(0.0f) {}

float SalesData::getTotalSales() const
{
    return mTotalSales;
}

const std::map<int, int> &SalesData::getItemsSold() const
{
    return mItemsSold;
}

void SalesData::recordSale(int code, float price)
{
    mTotalSales += price;
    mItemsSold[code] += 1;
}
