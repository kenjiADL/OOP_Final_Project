#ifndef CREGISTER_H
#define CREGISTER_H

// Manages the machine's cash: accepts payments and dispenses change.
class CRegister
{
 public:
  CRegister();

  // Add the given amount of cents to the cash balance.
  void addPayment(int amountCents);

  // Compute how much change to return (in cents) and subtract it from the balance.
  int dispenseChange(int amountCents);

  // Return the current cash balance in cents.
  int getBalance() const;

 private:
  int pBalanceCents;
};

#endif // CREGISTER_H
