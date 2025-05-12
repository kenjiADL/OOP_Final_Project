#ifndef ITEM_H
#define ITEM_H

#include <string>

// Represents a single product in the vending machine.
class Item {
public:
    // Constructs an Item with an alphanumeric code (e.g. "A1"), name, price, and starting quantity.
    Item(const std::string &code,
         const std::string &name,
         float price,
         int quantity);

    // Accessors
    const std::string &getCode()     const;
    const std::string &getName()     const;
    float               getPrice()   const;
    int                 getQuantity()const;

    // Mutators
    void reduceQuantity();          // decrement stock by one
    void setPrice(float newPrice);  // update the unit price
    void setQuantity(int newQty);   // update the stock level

private:
    std::string mCode;
    std::string mName;
    float       mPrice;
    int         mQuantity;
};

#endif // ITEM_H
