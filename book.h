#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <iostream>

class Book : public Product{//here is announcing as public with product
  public:

    Book(const std::string name, const double price, const int qty, const std::string author, const std::string isbn);
    //~Book(); //destructor here

    std::string get_a() const;
    std::string get_isbn() const;

         std::set<std::string> keywords() const;
         std::string displayString() const;
         void dump(std::ostream& os) const;

  private:
  std::string author_;
  std::string isbn_;

};

#endif
