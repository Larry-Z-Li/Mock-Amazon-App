#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
           const std::string isbn, const std::string author): Product::Product(category, name, price, qty),
           isbn_(isbn),
           author_(author)
{

}

Book::~Book()
{

}

std::string Book::getISBN() const
{
    return isbn_;
}

std::string Book::getAuthor() const
{
    return author_;
}

set<string> Book::keywords() const
{
    set<string> newSet = parseStringToWords(name_);     //Name
    newSet.insert(isbn_);                                //ISBN
    set<string> temp = parseStringToWords(author_);
    newSet = setUnion(newSet,temp);                   //Author Name
    return newSet;
}

std::string Book::displayString() const
{
    return name_  + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + doubleToPrice(price_) + "  "
    + to_string(qty_) + " left.";
}


/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}




