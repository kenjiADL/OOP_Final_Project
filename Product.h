#pragma once
#include <string>

/**
 * @brief Abstract base for all vending-machine products.
 */
class Product {
public:
  Product(int code, std::string name, int priceCents, int qty)
    : code(code), name(std::move(name)), price(priceCents), quantity(qty) {}
  virtual ~Product() = default;

  /// Returns a human-readable description including name and price.
  virtual std::string describe() const = 0;

  int getCode() const    { return code; }
  int getPrice() const   { return price; }
  int getQuantity() const{ return quantity; }

  /**
   * @brief Returns the product’s name.
   */
  const std::string& getName() const { return name; }

  void reduceQuantity()  { if (quantity>0) --quantity; }
  void addStock(int q)   { quantity += q; }
  void setPrice(int p)   { price = p; }

protected:
  int code;
  std::string name;
  int price;     // in cents
  int quantity;
};