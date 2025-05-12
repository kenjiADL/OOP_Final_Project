// Implementation of the Item class.
#include "Item.h"

Item::Item(int code, const std::string &name, int priceCents, int quantity)
    : pCode(code), pName(name), pPriceCents(priceCents), pQuantity(quantity) {}

int Item::getCode() const { return pCode; }
const std::string &Item::getName() const { return pName; }
int Item::getPrice() const { return pPriceCents; }
int Item::getQuantity() const { return pQuantity; }

void Item::reduceQuantity()
{
    if (pQuantity > 0)
        --pQuantity;
}

void Item::setPrice(int priceCents) {
    pPriceCents = priceCents;
}

void Item::addStock(int quantity) {
    pQuantity += quantity;
}