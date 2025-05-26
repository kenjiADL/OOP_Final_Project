#include "Change.h"
#include <vector>

using namespace std;

// Available coin denominations in cents (largest to smallest)
vector<int> denominations = {100, 50, 20, 10, 5};

// Break down the given cents into coin denominations.
Change::Change(int cents)
{
    // Use greedy algorithm: start with largest coins possible
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

const map<int, int>& Change::getChangeBreakdown() const
{
    return pChangeBreakdown;
}

// Operator overloading for stream output
ostream& operator<<(ostream& os, const Change& change)
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
    // Sum up the total cents from both change objects
    int totalCents = 0;
    
    for (const auto& pair : pChangeBreakdown) {
        totalCents += pair.first * pair.second;
    }
    
    for (const auto& pair : other.pChangeBreakdown) {
        totalCents += pair.first * pair.second;
    }
    
    // Create new change object that will recalculate optimal coins
    return Change(totalCents);
}

// Operator overloading for equality comparison
bool Change::operator==(const Change& other) const
{
    return pChangeBreakdown == other.pChangeBreakdown;
}
