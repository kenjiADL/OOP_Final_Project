#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

/**
 * @brief Abstract base for all vending-machine products.
 */
class Product {
public:
  Product(int code, std::string name, int priceCents, int qty);
  virtual ~Product() = default;

  /// Returns a human-readable description including name and price.
  virtual std::string describe() const = 0;

  int getCode() const;
  int getPrice() const;
  int getQuantity() const;

  /**
   * @brief Returns the product's name.
   */
  const std::string& getName() const;

  void reduceQuantity();
  void addStock(int q);
  void setPrice(int p);

protected:
  int code;
  std::string name;
  int price;     // in cents
  int quantity;
};

#endif // PRODUCT_H