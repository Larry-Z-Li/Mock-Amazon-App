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
    std::set<std::string> newSet;

    std::set<std::string> temp = parseStringToWords(name_);   //Words in clothing name
    std::set<std::string>::iterator iter = temp.begin();
    for(int i = 0; i < temp.size(); i++)
    {
        newSet.insert(*iter);
        iter++;
    }

    temp = parseStringToWords(brand_);                        //Words in brand name
    iter = temp.begin();
    for(int i = 0; i < temp.size(); i++)
    {
        newSet.insert(*iter);
        iter++;
    }
    return newSet;                                                 //Size not a keyword
}

std::string Clothing::displayString() const
{
    return "Clothing name: " + name_ + ". Price:" + to_string(price_) + ". In stock: " + to_string(qty_)+
    + ". Size: " + size_ + ". Brand: " + brand_  + ".";
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



