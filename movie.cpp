#include "movie.h"
#include "util.h"

#include <ostream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


Movie::Movie(const std::string name, double price, int qty, 
      const std::string genre, const std::string rating)
      : Product("movie", name, price, qty), genre_(genre), rating_(rating){
        genre_=genre; //accessing the private memebrs
        rating_=rating; //looking for th eprivate members
}

//Movie::~Movie() {}

      std::string Movie::get_g() const{
        return genre_; //accessor functions
      }
      std::string Movie::get_r() const{
        return rating_; //accessor functions
      }


  std::set<std::string> Movie::keywords() const{
      std::set<std::string> keywords = parseStringToWords(getName()); 
      std::string genre = convToLower(genre_); //will convert the genre to lowercse
      keywords.insert(genre);

      return keywords;
  }

  std::string Movie::displayString() const{
   std::stringstream ss;

    ss<<std::fixed<<std::setprecision(2)<<price_; //set precision for decimals
    std:: string price_n=ss.str();
   
   std::string fin;

    fin += getName(); 
    fin += "\n";
    fin += "Genre: ";
    fin += genre_; fin+= " ";
    fin += "Rating: "; //display of stirng that starts as one string and will be aded to others.
    fin += rating_; fin +="\n";
    fin += price_n; fin+=" "; fin+=std::to_string(getQty());
    fin += " left.";

    return fin;
  }

  void Movie::dump(std::ostream& os) const
{
    Product::dump(os);

    os<<genre_<<std::endl; //format for dumping order of elements
    os<<rating_<<std::endl;
}