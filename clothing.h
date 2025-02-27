#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <iostream>

class Clothing : public Product{
  public:
    Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
    ~Clothing(){} //destructor

    std::string get_s() const;
    std::string get_b() const;

    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

  private:
    std::string size_;
    std::string brand_;
};

#endif