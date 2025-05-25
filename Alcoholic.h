#pragma once

#include "Drink.h"
#include <sstream>
#include <iomanip>

/**
 * @brief An alcoholic drink that requires age verification.
 */
class Alcoholic : public Drink {
public:
    Alcoholic(int code,
              std::string name,
              int priceCents,
              int qty,
              bool isDiet = false)
        : Drink(code, std::move(name), priceCents, qty, isDiet) {}

    std::string describe() const override {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2)
            << (static_cast<float>(getPrice()) / 100.0f);
        return name
             + (isDiet() ? " (diet alcoholic drink)" : " (alcoholic drink)")
             + " – $" + oss.str();
    }

    bool requiresAgeVerification() const { return true; }
}; 