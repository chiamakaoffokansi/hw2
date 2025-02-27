#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
//this a template may be needed here 

std::set<string> keywords;

std::string word = convToLower(rawWords);
std::stringstream ss;
std::string search;

std::string s_chopped;
std::string e_chopped;

while(word.length()>1){ //conditional for searches, if more than 1 it will run

  ss<<word;

  while(ss>>search){

    if (search.length()>1){
      for(unsigned int i=0; i<search.length(); i++){ //will run for length of the word
        if(!ispunct(search[i])){
          s_chopped+=search[i];
        }
        else{
          for(unsigned int z = i+1; z<search.length(); z++){
            e_chopped+=search[z]; //combining the two
          }
          break;
        }
      }
      if(s_chopped.length()>e_chopped.length()){
        keywords.insert(s_chopped);
      }
      else{
        keywords.insert(e_chopped); 
      }
      s_chopped.clear(); //clearing the start chopped of the word
      e_chopped.clear(); //clearing end chopped of thw word
    }
    search.clear(); //clearing search after process entirely 
  }
}
  
  return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
