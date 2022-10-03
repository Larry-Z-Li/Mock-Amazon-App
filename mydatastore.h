#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore{
public:
    MyDataStore() { }
    ~MyDataStore() { }

    /**
     * Adds a product to the data store and adds keywords to keywordMap
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    /**
     * Returns keyword pairs
     */
    std::map<std::string, std::set<Product*>>& getKeywordPair();

    /**
     * Returns product set
     */

    std::set<Product*>& getProductSet();

    /**
     * Returns user set
     */
    std::set<User*>& getUserSet();


private:

    std::map<std::string, std::set<Product*>> keywordPair;
    std::set<Product*> productSet;
    std::set<User*> userSet;
};

