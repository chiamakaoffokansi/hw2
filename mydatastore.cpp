#include "mydatastore.h"
#include "product.h"
#include "util.h"

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

void MyDataStore::addProduct(Product* p){
  
  std::map<std::string, std::set<Product*>> keymap;
  set<string> buff=p->keywords(); //will be checking out for the keywords

  for(set<string>::iterator i=buff.begin(); i!=buff.end();++i){
    if(prod_storage.find(*i)!=prod_storage.end()){ 
      prod_storage[*i].insert(p); //inserting the new product in
    }
    else{
      prod_storage.insert(pair<string, set<Product*>>(*i, set<Product*>{p}));
    }
  }
  products_.push_back(p);
}//having toruble storing products

void MyDataStore::addUser(User* u){
  accounts_.push_back(u); //pushback for accounts
  users_.insert(pair<string,User*>(u->getName(),u)); //will then have users insert in the pair
}

void MyDataStore::buyCart(string u_name){//not storing orectly 
  if(users_.find(u_name)==users_.end()){
    cout<<"Invalid username"<<endl; //validity check
    return;
  }

  User *u = users_[u_name]; //declaring here

  vector<Product*> cart = shop_cart[u_name];
  vector<Product*> new_cart;

  for(unsigned int i = 0; i<cart.size(); i++){
    if((cart[i]->getQty()>0)&&(u->getBalance()>cart[i]->getPrice())){
      cart[i]->subtractQty(1);
      u->deductAmount(cart[i]->getPrice()); //finding the balance of the cart here and deduction 
    }
    else{
      new_cart.push_back(cart[i]); //otherwise a new cart with index will be pushed back
    }
  }
  cart.clear(); //empties cart
  if(new_cart.size()>0){
    shop_cart[u_name]=new_cart;
  }
  else{
    shop_cart[u_name]=cart;
  }
}

void MyDataStore::viewCart(string u_name){
  if(users_.find(u_name)==users_.end()){
    cout<<"Invalid username"<<endl;
    return;
  }

  int c_total =0;
  vector<Product*> buff = shop_cart[u_name];

  for(unsigned int i=0; i<buff.size(); i++){  //will ensure that what is added and shown in cart will never out index max
    c_total++;
    cout<<"Item: "<<c_total<<endl;
    cout<<buff[i]->displayString()<<endl; //stringifying it so it can be displayed
  }
}

void MyDataStore::addCart(string u_name, Product* item){//could be facing toruble here
  if(users_.find(u_name)==users_.end()|| item == nullptr){
    cout<<"Invalid username"<<endl;
    return;
  }

  if(shop_cart.find(u_name)==shop_cart.end()){
    vector<Product*> u_cart;
    u_cart.push_back(item); //makes new allocated space for the cart
    shop_cart.insert(pair<string, vector<Product*>>(u_name, u_cart));
  }
  else{
    shop_cart[u_name].push_back(item);
  }
}

std::vector<Product*>MyDataStore::search(std::vector<std::string>& terms, int type){
    
    set<Product*> res_fin; //final result here
    bool prim = true;

    if(type==0){

      for(unsigned int i=0;i<terms.size(); i++){
        
        string buffer = convToLower(terms[i]);

        std::map<std::string, std::set<Product*>>::iterator it1 = prod_storage.find(buffer);

        if(it1!=prod_storage.end()){
          if(!prim){ 
            res_fin=setIntersection(res_fin,prod_storage[buffer]);
          }
          else{
            prim=false; //if not true then boolean false and will make the set result point to second
            res_fin=it1->second;
          }
        }
      }

    }
    else if(type==1){
      for(unsigned int i=0; i<terms.size(); i++){
        string buffer = convToLower(terms[i]); //want to convert the rest of search to lower case

        std::map<std::string, std::set<Product*>>::iterator it2 = prod_storage.find(buffer);

        if(it2!=prod_storage.end()){
          if(!prim){
            res_fin=setUnion(res_fin,prod_storage[buffer]);
          }
          else{
            prim=false; //boolean false if conditions not met
            res_fin=it2->second;
          }
        }
      }
    }
    vector<Product*> res (res_fin.begin(),res_fin.end());
    return res;
}

void MyDataStore::dump(std::ostream& of){
  of<<"<products>"<<endl;

  for(unsigned int x = 0;x<products_.size();x++){
    products_[x]->dump(of);
  }
  of<<"</products>"<<endl;
  of<<"<users>"<<endl;

  for(std::map<string, User*>::iterator u = users_.begin(); u!= users_.end(); u++){
    u->second->dump(of);
  }
  of<<"</users>"<<endl;
}

vector<Product*> MyDataStore::getProducts(){
  return products_; //accessor functions
}

vector<User*> MyDataStore::getAccounts(){
  return accounts_; //accessor functions
}
