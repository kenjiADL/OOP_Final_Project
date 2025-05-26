#include "Snack.h"
#include <sstream>
#include <iomanip>

// Constructor implementation
Snack::Snack(int code, std::string name, int priceCents, int qty)
    : Product(code, name, priceCents, qty) {}

// describe() method implementation
std::string Snack::describe() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << (static_cast<float>(getPrice()) / 100.0f);
    return getName() + " (snack) – $" + oss.str();
}
