#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <queue>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "datastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);




int main(int argc, char *argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if (cmd == "AND") {                             //AND
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            } else if (cmd == "OR") {                       //OR
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            } else if (cmd == "QUIT") {                     //QUIT
                string filename;
                if (ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if (cmd == "ADD") {                        //ADD
                string userName;
                int search_hit_number;
                if (!(ss >> userName)) {
                    cout << "Invalid request" << endl;
                }
                else if (!(ss >> search_hit_number)) {
                    cout << "Invalid request" << endl;
                }
                else if (search_hit_number > hits.size()) {
                    cout << "Invalid request" << endl;
                }
                else
                {
                    userName = convToLower(userName);
                    set<User *>::iterator itr = ds.getUserSet().begin();
                    while (itr != ds.getUserSet().end()) {                                         //First finds user
                        if ((*itr)->getName() == userName) {
                            (*itr)->getCart().push_back(hits.at(search_hit_number - 1));        //Adds into the cart
                            break;
                        }
                        itr++;
                    }
                    if (itr == ds.getUserSet().end()) {                                             //User not found
                        cout << "Invalid request" << endl;
                    }
                }
            }
            else if ( cmd == "VIEWCART")                  //VIEWCART
            {
                string userName;
                if(!(ss >> userName))
                {
                    cout << "Invalid response" << endl;
                }
                else
                {
                    userName = convToLower(userName);
                    set<User*>::iterator itr = ds.getUserSet().begin();
                    while (itr != ds.getUserSet().end())
                    {
                        if((*itr)->getName() == userName)                                           //First finds user
                        {
                            vector<Product*>::iterator cartItr = (*itr)->getCart().begin();
                            int itemNum = 1;
                            for(int i = 0; i < (*itr)->getCart().size(); i++)                       //Displays each product
                            {

                                cout << "Item "  << itemNum << endl;
                                cout << (*cartItr)->displayString() << endl;
                                cartItr++;
                                itemNum++;
                            }
                            break;
                        }
                        itr++;
                    }
                    if(itr == ds.getUserSet().end())                                                //User not found
                    {
                        cout << "Invalid username" << endl;
                    }
                }
            }
            else if ( cmd == "BUYCART")
            {
                string userName;
                if(!(ss >> userName))
                {
                    cout << "Invalid response" << endl;
                }
                else
                {
                    userName = convToLower(userName);
                    set<User*>::iterator itr = ds.getUserSet().begin();
                    while (itr != ds.getUserSet().end())
                    {
                        if((*itr)->getName() == userName)                               //Found user
                        {
                            vector<Product*>::iterator cartItr = (*itr)->getCart().begin();
                            while(cartItr != (*itr)->getCart().end())                   //Iterating through items in cart
                            {
                                //If price is too high or quantity is 0, do nothing
                                if((*cartItr)->getQty() == 0 || (*cartItr)->getPrice() > (*itr)->getBalance())
                                {
                                    cartItr++;
                                }
                                else                                                    //Subtract quantity, deduct account amount
                                {
                                    (*cartItr)->subtractQty(1);
                                    (*itr)->deductAmount((*cartItr)->getPrice());
                                    (*itr)->getCart().erase(cartItr);           //iterator will point to next item
                                }
                            }
                            break;
                        }
                        itr++;
                    }
                    if(itr == ds.getUserSet().end())
                    {
                        cout << "Invalid username" << endl;
                    }
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        cout << "No results found!" << endl;
        return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
