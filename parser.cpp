/*
 *  COMP 15 Project 1 - CalcYouLater
 *
 *
 *  PURPOSE: Defines the parseRstring function that returns string
 *
 *  Modified By: Anesu Gavhera
 *           On: 10/1/2020
 */

#include "parser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>

using namespace std;

string parseRString(istream &input){
  string returnString = "{ ";
  int braceCount = 1;
  bool isFinished = false;
  string aChar;
  while (!isFinished){
    input >> aChar;
    returnString += aChar;
    returnString += " ";
    if (aChar == "{"){
      braceCount++;
    }
    if (aChar == "}"){
      braceCount--;
    }
    if (braceCount == 0){
      isFinished = true;
    }
  }
  if (returnString[returnString.length()-1] == ' '){
     returnString.pop_back();
  }
  return returnString;
}
