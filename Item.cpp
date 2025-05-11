// File: Item.cpp
#include "Item.h"

Item::Item(int code, const std::string &name, float price, int quantity)
    : mCode(code), mName(name), mPrice(price), mQuantity(quantity) {}

int Item::getCode() const { return mCode; }
const std::string &Item::getName() const { return mName; }
float Item::getPrice() const { return mPrice; }
int Item::getQuantity() const { return mQuantity; }

void Item::reduceQuantity()
{
    if (mQuantity > 0)
        --mQuantity;
}
