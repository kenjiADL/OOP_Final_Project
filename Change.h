#ifndef CHANGE_H
#define CHANGE_H

#include <map>
#include <iostream>

using namespace std;

/**
 * @brief Handles coin change calculations
 * 
 * Breaks down amounts into available coin denominations.
 */
class Change
{
 public:
  // Creates change from cents amount
  explicit Change(int cents);

  // Gets coin breakdown
  const map<int, int>& getChangeBreakdown() const;

  // Display format
  friend ostream& operator<<(ostream& os, const Change& change);
  
  // Combines two change amounts
  Change operator+(const Change& other) const;
  
  // Compares coin breakdowns
  bool operator==(const Change& other) const;

 private:
  map<int, int> pChangeBreakdown;  // coin value to count
};

#endif // CHANGE_H
