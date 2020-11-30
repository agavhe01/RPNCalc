/*
 *  COMP 15 Project 1 - CalcYouLater
 *
 *
 *  PURPOSE: Defines the stack implementation
 *
 *  Modified By: Anesu Gavhera
 *           On: 10/1/2020
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DatumStack
{
public:
  DatumStack();
  DatumStack(Datum arr[], int arrSize);
  ~DatumStack();
  DatumStack &operator=(DatumStack &other);
  bool isEmpty();
  void clear();
  int size();
  Datum top();
  void pop();
  void push(Datum element);
  
private:
  vector <Datum> theStack;
  Datum dataAt(int index);
};

#endif
