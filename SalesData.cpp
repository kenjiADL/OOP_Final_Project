#include "SalesData.h"

SalesData::SalesData()
  : mTotalSales(0.0f)
  , mItemsSold()
{}

void SalesData::recordSale(const std::string& code, float price) {
    mTotalSales += price;
    // increment existing or insert new
    auto it = mItemsSold.find(code);
    if (it != mItemsSold.end()) {
        it->second++;
    } else {
        mItemsSold[code] = 1;
    }
}

float SalesData::getTotalSales() const {
    return mTotalSales;
}

const std::map<std::string,int>& SalesData::getItemsSold() const {
    return mItemsSold;
}
