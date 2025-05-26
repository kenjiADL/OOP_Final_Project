#ifndef CHANGE_H
#define CHANGE_H

#include <map>
#include <iostream>

// Figure out how to split an amount in cents into coins.
class Change
{
 public:
  // Build a Change object to calculate coin counts for the given cents.
  explicit Change(int cents);

  // Get a map from coin values to their counts.
  const std::map<int, int>& getChangeBreakdown() const;

  // Operator overloading for displaying change
  friend std::ostream& operator<<(std::ostream& os, const Change& change);
  
  // Operator overloading for adding two Change objects
  Change operator+(const Change& other) const;
  
  // Operator overloading for equality comparison
  bool operator==(const Change& other) const;

 private:
  std::map<int, int> pChangeBreakdown;
};

#endif // CHANGE_H
