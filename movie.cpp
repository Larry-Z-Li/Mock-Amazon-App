#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre,
                   const std::string rating):
        Product::Product(category, name, price, qty),
        genre_(genre),
        rating_(rating)
{

}

Movie::~Movie()
{

}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> newSet = parseStringToWords(name_);   //Name
    newSet.insert(convToLower(genre_));                      //Genre
    return newSet;
}

std::string Movie::displayString() const
{
    return name_  + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + doubleToPrice(price_) + " "
           + to_string(qty_) + " left.";
}


/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}



