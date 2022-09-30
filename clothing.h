#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing: public Product {
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size,
             const std::string brand);
    ~Clothing();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;

    /**
     * Accessors and mutators
     */

    /**
     * Variables from product.h
     *
     * double getPrice() const;
     * std::string getName() const;
     * int getQty() const;
     * void subtractQty(int num);
     */

    std::string getSize() const;
    std::string getBrand() const;

protected:
    /**
     * Variables from product.h
     *
     * std::string name_;
     * double price_;
     * int qty_;
     * std::string category_;
     */
    std::string size_;
    std::string brand_;
};
#endif