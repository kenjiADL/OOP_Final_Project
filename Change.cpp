#include "Change.h"
#include <vector>

// Break down the given cents into coin denominations.
Change::Change(int cents)
{
    std::vector<int> denominations = {100, 50, 20, 10, 5};
    for (int coin : denominations)
    {
        int count = cents / coin;
        if (count > 0)
        {
            pChangeBreakdown[coin] = count;
            cents -= coin * count;
        }
    }
}

std::map<int, int> Change::getChangeBreakdown() const
{
    return pChangeBreakdown;
}

// Operator overloading for stream output
std::ostream& operator<<(std::ostream& os, const Change& change)
{
    os << "Change returned:\n";
    for (const auto& pair : change.pChangeBreakdown) {
        os << pair.first << "c x " << pair.second << " coins\n";
    }
    return os;
}

// Operator overloading for adding two Change objects
Change Change::operator+(const Change& other) const
{
    // Calculate total cents from both Change objects
    int totalCents = 0;
    
    // Add cents from this object
    for (const auto& pair : pChangeBreakdown) {
        totalCents += pair.first * pair.second;
    }
    
    // Add cents from other object
    for (const auto& pair : other.pChangeBreakdown) {
        totalCents += pair.first * pair.second;
    }
    
    // Return new Change object with combined total
    return Change(totalCents);
}

// Operator overloading for equality comparison
bool Change::operator==(const Change& other) const
{
    return pChangeBreakdown == other.pChangeBreakdown;
}
