#include "mydatastore.h"
#include "product.h"

using namespace std;

void MyDataStore::addProduct(Product *p)
{
    /**
     * Products are found by matching keywords.
     * One keyword can have multiple (i.e. vector of) products.
     * keyword pairs are thus formated by map<keyword,vector<Products*>>
     */

    set<string> keywords = p->keywords();                          //Adding keywords into keywordPair, matching product p
    set<string>::iterator itr = keywords.begin();
    while(itr!=keywords.end())
    {
        if(keywordPair.find(*itr) != keywordPair.end())         //keyword exists, insert into set of products matching keyword
        {
            keywordPair.find(*itr)->second.insert(p);

        }
        else                                                       //Otherwise, create new pair, initialize array with the product
        {
            set<Product*> temp;
            temp.insert(p);
            keywordPair.insert({(*itr), temp});
        }
        itr++;
    }
    productSet.insert(p);                                       //Finally add product into the store
}

void MyDataStore::addUser(User *u)
{
    userSet.insert(u);
}

vector<Product*> MyDataStore::search(vector<string> &terms, int type)
{
    set<Product*> results;
    bool matched = false;
    for(int i = 0; i < terms.size(); i++)
    {
        if(type == 1 && keywordPair.find(terms[i]) != keywordPair.end())        //OR: keyword matched
        {
            results = setUnion(results, keywordPair.find(terms[i])->second);
        }
        else if(type == 0 && keywordPair.find(terms[i]) != keywordPair.end())   //AND: keyword matched
        {
            if (!matched)                                                          //First match: to initialize results set
            {
                results = keywordPair.find(terms[i])->second;
                matched = true;
            }
            else                                                                   //Further matches: must have previous keywords
            {
                results = setIntersection(results, keywordPair.find(terms[i])->second);
            }
        }
    }

    vector<Product*> vectorResults;
    set<Product*>::iterator itr = results.begin();
    while(itr != results.end())                                                    //converting results set to vector for return value
    {
        vectorResults.push_back(*itr);
        itr++;
    }
    return vectorResults;
}

void MyDataStore::dump(std::ostream &ofile)
{
    ofile << "<products>" << endl;
    while(!productSet.empty())
    {
        (*productSet.begin())->dump(ofile);
        delete (*productSet.begin());
        productSet.erase(productSet.begin());
    }
    ofile << "</products>\n<users>" << endl;
    while(!userSet.empty())
    {
        (*userSet.begin())->dump(ofile);
        delete (*userSet.begin());
        userSet.erase(userSet.begin());
    }
    ofile << "</users>";
}

/**
 * The go-getters
 */

std::map<std::string, std::set<Product*>>& MyDataStore::getKeywordPair()
{
    return keywordPair;
}

std::set<Product*>& MyDataStore::getProductSet()
{
    return productSet;
}

std::set<User*>& MyDataStore::getUserSet()
{
    return userSet;
}