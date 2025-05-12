#pragma once
#include "Product.h"
#include <sstream>
#include <iomanip>

/**
 * @brief A snack item in the vending machine.
 */
 class Snack : public Product {
 public:
   Snack(int code, std::string name, int priceCents, int qty)
     : Product(code, std::move(name), priceCents, qty) {}
 std::string describe() const override {
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(2)
          << (static_cast<float>(getPrice()) / 100.0f);
      return name + " (snack) – $" + oss.str();
  }
 };