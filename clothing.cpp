#include "clothing.h"
#include "util.h"

#include <ostream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


Clothing::Clothing(const std::string name, double price, int qty, 
      const std::string size, const std::string brand)
      : Product("clothing", name, price, qty), size_(size), brand_(brand){ //adding the 
        size_=size; //accessing private variables
        brand_=brand;
}

//Clothing::~Clothing(){}

      std::string Clothing::get_s() const{
        return size_; //accessor functions
      }

      std::string Clothing::get_b() const{
        return brand_; //accesor functions
      }


    std::set<std::string> Clothing::keywords() const{
      std::set<std::string> keywords = parseStringToWords(getName()+" "+brand_); //will combine the stringified words with the brand afterwards

      return keywords;
  }

  std::string Clothing::displayString() const{
    std::stringstream ss;

    ss<<std::fixed<<std::setprecision(2)<<price_; //fixed pricepoint setting
    std:: string price_n=ss.str();
    
    std::string fin;

    fin += getName(); 
    fin += "\n"; //display of stirng that starts as one string and will be aded to others.
    fin += "Size: ";
    fin += size_; fin+= " "; //display of stirng that starts as one string and will be aded to others.
    fin += "Brand: ";
    fin += brand_; fin +="\n";
    fin += price_n; fin+=" "; fin+=std::to_string(getQty());
    fin += " left.";

    return fin;
  }

  void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" 
    << qty_ << "\n" << size_ << "\n" << brand_ << std::endl; //format for dumping order of elements
}