#include "CashRegister.h"

// Initializes the register with zero balance.
CashRegister::CashRegister()
    : mBalance(0.0f) {}

void CashRegister::addPayment(float amount)
{
    mBalance += amount;
}

float CashRegister::dispenseChange(float amount)
{
    if (amount > mBalance)
    {
        amount = mBalance;
    }
    mBalance -= amount;
    return amount;
}