#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <map>
#include "datastore.h"

class MyDataStore : public DataStore{
  public:
    MyDataStore() {}
    ~MyDataStore() {}//now has constructor and deconstructor

    void addProduct(Product* prod); 
    void addUser(User* u);

    std::vector<Product*> getProducts();
    std::vector<User*> getAccounts();
 
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    
    void dump(std::ostream& ofile);

    void addCart(std::string u_name, Product* item);
    void viewCart(std::string u_name);
    void buyCart(std::string u_name);


  private:
    std::vector<Product*> products_; //keeping products in this 
    std::vector<User*> accounts_; //keeping users

    std::map<std::string, std::set<Product*>> prod_storage; //need to access the index of the keys we'll be using
    std::map<std::string, User*> users_; //need to access the index of the keys we'll be using
    std::map<std::string, std::vector<Product*>> shop_cart; //user cart

};

#endif