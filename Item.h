#pragma once

#include <string>

// A product in the vending machine with code, name, price, and stock.
class Item
{
 public:
  // Create a product with its selection code, display name, price in cents, and starting stock.
  Item(int code, const std::string &name, int priceCents, int quantity);

  // Getters:
  int getCode() const;
  const std::string &getName() const;
  int getPrice() const;
  int getQuantity() const;

  // Reduce the stock by one when sold.
  void reduceQuantity();

  // Update the item's price in cents.
  void setPrice(int priceCents);

  // Add more stock to the item.
  void addStock(int quantity);

 private:
  int pCode;
  std::string pName;
  int pPriceCents;
  int pQuantity;
};
