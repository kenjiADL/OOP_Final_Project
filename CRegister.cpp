#include "CRegister.h"

// Start with an empty cash register (zero balance).
CRegister::CRegister()
    : pBalanceCents(0) {}

void CRegister::addPayment(int amountCents)
{
    pBalanceCents += amountCents;
}

int CRegister::dispenseChange(int amountCents)
{
    if (amountCents > pBalanceCents)
    {
        amountCents = pBalanceCents;
    }
    pBalanceCents -= amountCents;
    return amountCents;
}

int CRegister::getBalance() const {
    return pBalanceCents;
}