#ifndef SNACK_H
#define SNACK_H

#include "Product.h"
#include <iomanip>
#include <sstream>

/**
 * @brief A snack item in the vending machine.
 */
class Snack : public Product {
public:
  Snack(int code, std::string name, int priceCents, int qty);
  std::string describe() const override;
};

#endif // SNACK_H