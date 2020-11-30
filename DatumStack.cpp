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
#include <iostream>
#include <string>

using namespace std;
/*
   Purpose: Default constructor
Parameters: None
   Returns: Empty stack
*/
DatumStack::DatumStack()
{
 //nothing to be done as vectors self initalizes
}
/*
   Purpose: Array constructor
Parameters: Array of type Datum, integer specifying array size
   Returns: Stack with array elements
*/
DatumStack::DatumStack(Datum arr[], int arrSize)
{
   for (int i = 0; i < arrSize; i++){
     theStack.push_back(arr[i]);
   }
}
/*
   Purpose: Copy Constructor
Parameters: Datum Stack to be copied
   Returns: DatamStack type identical to that in the parameters
*/
DatumStack & DatumStack::operator=(DatumStack &other){
  DatumStack temp = other;
  if (this == &temp) {
     return *this;
  }
  if (temp.isEmpty()) {
     theStack.clear();
  } else {
     theStack.clear();
     for (int i = 0; i < (int)temp.theStack.size(); i++){
       theStack.push_back(temp.theStack[i]);
     }
  }
  return *this;
}
/*
   Purpose: Destructor. Recycles the dynamically allocated memory containing
            the data.
Parameters: none
  Returns: void
 */
DatumStack::~DatumStack()
{
    clear();
}
/*
   Purpose: Evaluates weather the stack is empty or note
Parameters: None
   Returns: Bool true if stack is empty, false otherwise
*/
bool DatumStack::isEmpty()
{
  if (theStack.size() == 0){
    return true;
  }
  return false;
}
/*
   Purpose: Deletes all the elements present in the stack
Parameters: None
   Returns: None
*/
void DatumStack::clear()
{
  theStack.clear();
}
/*
   Purpose: Evaluates the current size of the stack
Parameters: None
   Returns: Type integer representing the number of elements in the stack
*/
int DatumStack::size()
{
  return theStack.capacity();
}
/*
   Purpose: To retrieve the frontal data element of the stack
Parameters: None
   Returns: Type Datum of the first element stored in the stack
*/
Datum DatumStack::top()
{
  if (isEmpty()){
    throw runtime_error("empty_stack");
  }
  return theStack.back();
}
/*
   Purpose: To delete the frontal data element of the stack
Parameters: None
   Returns: None
*/
void DatumStack::pop()
{
  if (isEmpty()){
    throw runtime_error("empty_stack");
  }
  theStack.pop_back();
}
/*
   Purpose: To retrieve the frontal data element of the stack
Parameters: None
   Returns: Type Datum of the first element stored in the stack
*/
void DatumStack::push(Datum element)
{
  theStack.push_back(element);
}
/*
   Purpose: To retrieve an element at a specific index within the stack
Parameters: Integer index position
   Returns: Type Datum of the element stored in the stack
*/
Datum DatumStack::dataAt(int index)
{
  if (index > (int)size() )
  {
    string message = "index (" + std::to_string(index) + ") not in range [0.."
    + std::to_string((int)theStack.size()) + ")";
    throw range_error(message);
  }
  else{
    return theStack[index];
  }
}
