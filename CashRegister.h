#ifndef CASHREGISTER_H
#define CASHREGISTER_H

// Handles incoming payments and change dispensing in the machine.
class CashRegister
{
public:
    CashRegister();

    // Adds the specified amount to the register's balance.
    void addPayment(float amount);

    // Calculates and returns change; deducts it from the balance.
    float dispenseChange(float amount);

private:
    float mBalance;
};

#endif // CASHREGISTER_H
