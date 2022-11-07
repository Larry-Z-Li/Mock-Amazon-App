#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size,
           const std::string brand):
           Product::Product(category, name, price, qty),
           size_(size),
           brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const
{
    return brand_;
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> newSet = parseStringToWords(name_);   //Name
    std::set<std::string> temp = parseStringToWords(brand_);    //Brand Name
    newSet = setUnion(newSet,temp);
    return newSet;
}

std::string Clothing::displayString() const
{
    return name_  + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + doubleToPrice(price_) + "  "
           + to_string(qty_) + " left.";
}


/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}



