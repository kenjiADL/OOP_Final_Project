#include "Drink.h"
#include <iomanip>
#include <sstream>

using namespace std;

// Constructor implementation
Drink::Drink(int code, string name, int priceCents, int qty, bool isDiet)
    : Product(code, name, priceCents, qty), diet(isDiet) {}

// describe() method implementation
string Drink::describe() const {
  ostringstream oss;
  oss << fixed << setprecision(2)
      << (static_cast<float>(getPrice()) / 100.0f);
  return getName() + (diet ? " (diet drink)" : " (drink)") + " – $" + oss.str();
}

// isDiet() method implementation
bool Drink::isDiet() const { return diet; }