#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  //template beign used here, if onlogn it will 
  //prob be a for loop, conditional i that leads to 
  //another for loop
  std::set<T> prod;

 for(typename std::set<T>::iterator j = s1.begin(); j!=s1.end(); j++){
  if(s2.find(*j)!=s2.end()){
    prod.insert(*j);
  }
 }
  return prod;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
std::set<T> prod;

  for(typename std::set<T>::iterator i = s1.begin(); i!=s1.end(); i++){
    prod.insert(*i);
  }

  for(typename std::set<T>::iterator x = s1.begin(); x!=s1.end(); x++){
    prod.insert(*x);
  }

  return prod;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
