#include "book.h"
#include "util.h"

#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

Book::Book(const std::string name, double price, int qty, const std::string author,
      const std::string isbn) : Product("book", name, price, qty), author_(author), isbn_(isbn){ //want to add additional parameters to problem

        author_ = author;
        isbn_ = isbn; //acccesing priv variables with get variables 
}

std::string Book::get_a() const{
  return author_; //accessor functions
} //check here

std::string Book::get_isbn() const{
  return isbn_; //accessor functions
}

  std::set<std::string> Book::keywords() const{
      std::set<std::string> keywords = parseStringToWords(getName()+" "+author_); //will display the author and allow matching

      return keywords;
  }

  std::string Book::displayString() const{
    std::stringstream ss;

    ss<<std::fixed<<std::setprecision(2)<<price_;
    std:: string price_n=ss.str();
    
    std::string fin;

    fin += getName(); fin += "\n"; //want to essentially start with a string that is built and added with space for eahc new element within stirng
    fin += "Author: "; 
    fin += author_; fin+= " ";  //+space here
    fin += "ISBN: "; fin += isbn_; fin +="\n";
    fin += price_n; fin+=" "; fin+=std::to_string(getQty()); fin += " left.";

    return fin;
  }

  void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" 
    << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl; //format for dumping order of elements 
}