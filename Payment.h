#ifndef PAYMENT_H
#define PAYMENT_H

#include "PaymentMethod.h"

// Represents a customer's payment, including method and surcharge logic.
class Payment
{
 public:
  // Constructs a payment with raw amount (in cents) and payment method.
  Payment(int amountCents, PaymentMethod method);

  // Returns the raw amount provided by the customer (in cents).
  int getAmount() const;

  // Returns the payment method (Cash or Card).
  PaymentMethod getMethod() const;

  // Returns the actual amounnt charged, including any card surcharge.
  int getChargedAmount() const;

 private:
  int pAmountCents;
  PaymentMethod pMethod;
};

#endif // PAYMENT_H