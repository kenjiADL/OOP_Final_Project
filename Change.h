#ifndef CHANGE_H
#define CHANGE_H

#include <map>

// Calculates the breakdown of change into coin denominations.
class Change
{
public:
    // Constructs a Change object that computes breakdown for the given amount.
    Change(float amount);

    // Returns a map of coin value (in cents) to quantity.
    std::map<int, int> getChangeBreakdown() const;

private:
    std::map<int, int> mChangeBreakdown;
};

#endif // CHANGE_H
