#include "Product.h"

using namespace std;

// Constructor implementation
Product::Product(int code, string name, int priceCents, int qty)
    : code(code), name(name), price(priceCents), quantity(qty) {}

// Getter implementations
int Product::getCode() const {
    return code;
}

int Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

const string& Product::getName() const {
    return name;
}

// Method implementations
void Product::reduceQuantity() {
    if (quantity > 0) {
        --quantity;
    }
}

void Product::addStock(int q) {
    quantity += q;
}

void Product::setPrice(int p) {
    price = p;
}