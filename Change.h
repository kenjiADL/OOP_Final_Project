#pragma once

#include <map>

// Figure out how to split an amount in cents into coins.
class Change
{
 public:
  // Build a Change object to calculate coin counts for the given cents.
  explicit Change(int cents);

  // Get a map from coin values to their counts.
  std::map<int, int> getChangeBreakdown() const;

 private:
  std::map<int, int> pChangeBreakdown;
};
