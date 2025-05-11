#include "Change.h"
#include <vector>
#include <cmath>

// Constructs a Change and computes the breakdown into denominations.
Change::Change(float amount)
{
    int cents = static_cast<int>(std::round(amount * 100));
    std::vector<int> denominations = {100, 50, 20, 10, 5};
    for (int coin : denominations)
    {
        int count = cents / coin;
        if (count > 0)
        {
            mChangeBreakdown[coin] = count;
            cents -= coin * count;
        }
    }
}

std::map<int, int> Change::getChangeBreakdown() const
{
    return mChangeBreakdown;
}
