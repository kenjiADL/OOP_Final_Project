#include "Alcoholic.h"
#include <sstream>
#include <iomanip>

// Constructor implementation
Alcoholic::Alcoholic(int code, std::string name, int priceCents, int qty, bool isDiet)
    : Drink(code, name, priceCents, qty, isDiet) {}

// describe() method implementation
std::string Alcoholic::describe() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << (static_cast<float>(getPrice()) / 100.0f);
    return getName()
         + (isDiet() ? " (diet alcoholic drink)" : " (alcoholic drink)")
         + " – $" + oss.str();
}

// requiresAgeVerification() method implementation
bool Alcoholic::requiresAgeVerification() const {
    return true;
} 