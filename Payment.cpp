#include "Payment.h"

// Constructs a Payment with amount (in cents) and method.
Payment::Payment(int amountCents, PaymentMethod method)
    : pAmountCents(amountCents), pMethod(method) {}

int Payment::getAmount() const
{
    return pAmountCents;
}

PaymentMethod Payment::getMethod() const
{
    return pMethod;
}

int Payment::getChargedAmount() const
{
    if (pMethod == PaymentMethod::Card)
    {
        return pAmountCents + CARD_SURCHARGE_CENTS;
    }
    return pAmountCents;
}