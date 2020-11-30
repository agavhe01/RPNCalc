/*
 *  COMP 15 Project 1 - CalcYouLater
 *
 *
 *  PURPOSE: Defines the parseRstring function that returns string
 *
 *  Modified By: Anesu Gavhera
 *           On: 10/1/2020
 */

#include "Datum.h"
#include "DatumStack.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

string parseRString(istream &input);

using namespace std;
int main()
{
  string anesu = parseRString(cin);
  cout << anesu;
  return 0;
}
/*parseRString()
   Purpose: Called after the intial curly brace has been input and recieves
            the rest of the RString as Input
Parameters: Input stream to be read from type iostream
   Returns: Rstring of type stringstream
     Notes: Function does not terminate until enough braces have been input
*/
string parseRString(istream &input){
  string returnString = "{ ";
  int braceCount = 1;
  bool isFinished = false;
  char aChar;
  while (!isFinished){
    cout << "Input ?";
    input >> aChar;
    returnString += aChar;
    returnString += " ";
    if (aChar == '{'){
      braceCount++;
    }
    if (aChar == '}'){
      braceCount--;
    }
    if (braceCount == 0){
      isFinished = true;
    }
  }
  return returnString;
}
