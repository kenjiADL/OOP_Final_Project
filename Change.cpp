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
