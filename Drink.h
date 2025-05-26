#ifndef DRINK_H
#define DRINK_H

#include "Product.h"

/**
 * @brief A drink item, with an optional "diet" flag.
 */
class Drink : public Product {
public:
  Drink(int code, std::string name, int priceCents, int qty, bool isDiet);

  std::string describe() const override;
  bool isDiet() const;

private:
  bool diet;
};

#endif // DRINK_H