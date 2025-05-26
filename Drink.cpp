#include "Drink.h"
#include <iomanip>
#include <sstream>

// Constructor implementation
Drink::Drink(int code, std::string name, int priceCents, int qty, bool isDiet)
    : Product(code, name, priceCents, qty), diet(isDiet) {}

// describe() method implementation
std::string Drink::describe() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2)
      << (static_cast<float>(getPrice()) / 100.0f);
  return getName() + (diet ? " (diet drink)" : " (drink)") + " – $" + oss.str();
}

// isDiet() method implementation
bool Drink::isDiet() const { return diet; }