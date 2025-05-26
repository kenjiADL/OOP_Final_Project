#ifndef ALCOHOLIC_H
#define ALCOHOLIC_H

#include "Drink.h"

/**
 * @brief An alcoholic drink that requires age verification.
 */
class Alcoholic : public Drink {
public:
    Alcoholic(int code,
              std::string name,
              int priceCents,
              int qty,
              bool isDiet = false);

    std::string describe() const override;
    bool requiresAgeVerification() const;
};

#endif // ALCOHOLIC_H 