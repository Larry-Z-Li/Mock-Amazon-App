#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "product.h"
#include <queue>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    std::vector<Product*>& getCart();
    virtual void dump(std::ostream& os);

private:
    std::string name_;
    double balance_;
    int type_;
    std::vector<Product*> cart_;
};
#endif
