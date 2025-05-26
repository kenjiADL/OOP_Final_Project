#include "Snack.h"
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor implementation
Snack::Snack(int code, string name, int priceCents, int qty)
    : Product(code, name, priceCents, qty) {}

// describe() method implementation
string Snack::describe() const {
    ostringstream oss;
    oss << fixed << setprecision(2)
        << (static_cast<float>(getPrice()) / 100.0f);
    return getName() + " (snack) – $" + oss.str();
}
