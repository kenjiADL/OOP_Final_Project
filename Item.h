#ifndef ITEM_H
#define ITEM_H

#include <string>

// Represents a single item in the vending machine.
class Item
{
public:
    // Constructs an Item with a selection code, name, price, and quantity.
    Item(int code, const std::string &name, float price, int quantity);

    // Accessors:
    int getCode() const;
    const std::string &getName() const;
    float getPrice() const;
    int getQuantity() const;

    // Decrease stock by one after a sale.
    void reduceQuantity();

private:
    int mCode;
    std::string mName;
    float mPrice;
    int mQuantity;
};

#endif // ITEM_H
