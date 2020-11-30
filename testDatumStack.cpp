/*
 *  COMP 15 Project 1 - CalcYouLater
 *
 *
 *  PURPOSE: Defines the stack implementation
 *
 *  Modified By: Anesu Gavhera
 *           On: 10/1/2020
 */

#include "DatumStack.h"
#include "parser.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  DatumStack stack1;
  //isEmpty()
  if (stack1.isEmpty()){
    cout << "Empty Stack";
  }
  else{
    cout << "Not empty";
  }
  //clear()
  Datum val1(5);
  Datum val2("anesu");
  stack1.push(val1);
  stack1.push(val2);
  stack1.clear();
  if (stack1.isEmpty()){
    cout << "Empty Stack" << endl;
  }
  else{
    cout << "Not empty" << endl;
  }
  //size()
  stack1.push(val1);
  stack1.push(val2);
  cout << "Size must be 2: " << stack1.size() << endl;
  //top() and pop()
  Datum val3 = stack1.top();
  stack1.pop();
  Datum val4 = stack1.top();
  if (val3.toString() != val2.toString() or val4.toString() != val1.toString()){
    cout << "Problem here" << endl;
  }
  else{
    cout << "Matching Vales" << endl;
  }
  //array Constructor
  Datum thisArray[] = {val1, val2, val3, val4};
  DatumStack stack2(thisArray, 4);
  for (int i = 0; i < (int)stack2.size(); i++){
    cout << stack2.top().toString() << endl;
    stack2.pop();
  }
  //parseRString
    string anesu = parseRString(cin);
    cout << anesu;
    return 0;
}
