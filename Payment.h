#ifndef PAYMENT_H
#define PAYMENT_H

#include "PaymentMethod.h"

// Represents a customer's payment, including method and surcharge logic.
class Payment
{
public:
    // Constructs a payment with raw amount and payment method.
    Payment(float amount, PaymentMethod method);

    // Returns the raw amount provided by the customer.
    float getAmount() const;

    // Returns the payment method (Cash or Card).
    PaymentMethod getMethod() const;

    // Returns the actual amount charged, including any card surcharge.
    float getChargedAmount() const;

private:
    float mAmount;
    PaymentMethod mMethod;
    static constexpr float CARD_SURCHARGE = 0.25f;
};

#endif // PAYMENT_H