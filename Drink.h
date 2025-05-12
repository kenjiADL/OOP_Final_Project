#pragma once

#include "Snack.h"
#include <sstream>
#include <iomanip>

/**
 * @brief A drink item, with an optional “diet” flag.
 */
 class Drink : public Snack {
 public:
   Drink(int code,
         std::string name,
         int priceCents,
         int qty,
         bool isDiet)
     : Snack(code, std::move(name), priceCents, qty),
       diet(isDiet) {}
  std::string describe() const override {
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(2)
          << (static_cast<float>(getPrice()) / 100.0f);
      return name
           + (diet ? " (diet drink)" : " (drink)")
           + " – $" + oss.str();
  }

 private:
   bool diet;
 };