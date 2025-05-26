#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

/**
 * @brief Base class for vending machine products
 * 
 * Common features for all product types.
 */
class Product {
public:
  // Initialize a product with its basic attributes
  Product(int code, string name, int priceCents, int qty);
  virtual ~Product() = default;

  // Each product type provides its own description
  virtual string describe() const = 0;

  // Basic getters for product attributes
  int getCode() const;
  int getPrice() const;
  int getQuantity() const;

  /**
   * @brief Returns the product's name.
   */
  const string& getName() const;

  // Stock management functions
  void reduceQuantity();
  void addStock(int q);
  void setPrice(int p);

protected:
  int code;
  string name;
  int price;     // in cents
  int quantity;
};

#endif // PRODUCT_H