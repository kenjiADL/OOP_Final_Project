#include "Item.h"

// Constructor
Item::Item(const std::string &code,
           const std::string &name,
           float price,
           int quantity)
  : mCode(code)
  , mName(name)
  , mPrice(price)
  , mQuantity(quantity)
{ }

// Accessors
const std::string &Item::getCode()     const { return mCode; }
const std::string &Item::getName()     const { return mName; }
float               Item::getPrice()   const { return mPrice; }
int                 Item::getQuantity()const { return mQuantity; }

// Reduce stock by one
void Item::reduceQuantity() {
    if (mQuantity > 0) --mQuantity;
}

// Change the unit price
void Item::setPrice(float newPrice) {
    mPrice = newPrice;
}

// Set the stock level
void Item::setQuantity(int newQty) {
    mQuantity = newQty;
}
