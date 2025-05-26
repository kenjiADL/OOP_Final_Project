#include "Alcoholic.h"
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor implementation
Alcoholic::Alcoholic(int code, string name, int priceCents, int qty, bool isDiet)
    : Drink(code, name, priceCents, qty, isDiet) {}

// describe() method implementation
string Alcoholic::describe() const {
    ostringstream oss;
    oss << fixed << setprecision(2)
        << (static_cast<float>(getPrice()) / 100.0f);
    return getName()
         + (isDiet() ? " (diet alcoholic drink)" : " (alcoholic drink)")
         + " – $" + oss.str();
}

// requiresAgeVerification() method implementation
bool Alcoholic::requiresAgeVerification() const {
    return true;
} 