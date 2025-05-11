#include "Payment.h"

// Constructs a Payment with amount and method.
Payment::Payment(float amount, PaymentMethod method) : mAmount(amount), mMethod(method) {}

float Payment::getAmount() const
{
    return mAmount;
}

PaymentMethod Payment::getMethod() const
{
    return mMethod;
}

float Payment::getChargedAmount() const
{
    if (mMethod == PaymentMethod::Card)
    {
        return mAmount + CARD_SURCHARGE;
    }
    return mAmount;
}