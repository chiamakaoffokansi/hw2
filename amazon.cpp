#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "util.h"
#include "mydatastore.h"
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
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
    productSectionParser->addProductParser(new ProductBookParser);//not even reaching book part
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
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
      //need to add commands here !!!
          else if( cmd == "ADD"){
            //do we error check fro the username
            string u_name;
            int ind;

            if(ss>>u_name>>ind){ //diff conditionals to make it work
              ds.addCart(u_name, hits[ind-1]);
              //cout<<ds.dump()<<endl;
            }
            else{
              cout<<"Invalid Request"<<endl; //conditional check fail
            }
          }
          else if( cmd == "BUYCART"){
            string u_name;

            if(ss>>u_name){//only parsing uname bc its th eonly parameter
              ds.buyCart(u_name);
            }
            else{
              cout<<"Invalid Username"<<endl;
            }
          }
          else if( cmd == "VIEWCART" ){
            string u_name;

            if(ss>>u_name){ //parsing in the uname only since only parameter
              ds.viewCart(u_name);
            }
            else{
              cout<<"Invalid Username"<<endl;
            }
          }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    //clear mem here

    vector<Product*> productAccess = ds.getProducts();
    vector<User*> userAccess = ds.getAccounts();

    for(unsigned int i=0; i<productAccess.size(); i++){
      delete productAccess[i];
    }
    for(unsigned int i=0; i<userAccess.size(); i++){
      delete userAccess[i];
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