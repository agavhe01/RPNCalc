/*
 *
 *  COMP 15 PROJ 1 CALCYOULATER
 *
 *  RPNCalc.h
 *
 *  Implementation of the RPNCalc class.
 *
 *  Written by: Anesu Gavhera
 *          on: 10/9/20
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "RPNCalc.h"
#include "parser.h"
#include <string>

using namespace std;

/*  default constructor
   Purpose: initializes an empty stack
 Parameters: None
    Returns: none
*/
RPNCalc::RPNCalc(){
  //no need to do anything because vectors automatically initialze themselves
}
/*  destructor
   Purpose: recyles data
Parameters: none
   Returns: void
*/
RPNCalc::~RPNCalc(){
    //no need to do anything because vectors automatically recycle data
}
/*  run()
   Purpose: Main program interface
Parameters: None
   Returns: void
*/
void RPNCalc::run(){
    getCommands(cin);
    quit();
}
/*  getCommands()
    Purpose: Accepts commands for the calculator and diverts program to
             relevant functions
 Parameters: istream &input = input for running query
    Returns: none
*/
void RPNCalc::getCommands(istream &input){
    string command;
    int number;
    while (input >> command){
        if (gotInt(command,&number)){
            pushNumber(number);
        }
        else if (command == "mod"){
            operation(command);
        }
        else if (command == "<"){
            logicComparison(command);
        }
        else if (command == ">"){
            logicComparison(command);
        }
        else if (command == "<="){
            logicComparison(command);
        }
        else if (command == ">="){
            logicComparison(command);
        }
        else if (command == "=="){
            equalityComparison();
        }
        else if (command == "{"){
            pushRString(parseRString(input));
        }
        else if (command == "exec"){
            exec();
        }
        else if (command == "file"){
            file();
        }
        else if (command == "if"){
            checkIf();
        }
        else if (command == "quit"){
            break;
        }
        else if (command == "#t"){
            pushTrue();
        }
        else if (command == "#f"){
            pushFalse();
        }
        else if (command == "not"){
            isNot();
        }
        else if (command == "print"){
            print();
        }
        else if (command == "clear"){
            clear();
        }
        else if (command == "drop"){
            drop();
        }
        else if (command == "dup"){
            dup();
        }
        else if (command == "swap"){
            swap();
        }
        else if (command == "+"){
            operation(command);
        }
        else if (command == "*"){
            operation(command);
        }
        else if (command == "-"){
            operation(command);
        }
        else if (command == "/"){
            operation(command);
        }
        else if (command == "}"){
          //Ignore the close brace, parser misses it sometimes for some reason
        }
        else{
            cerr << command << ": unimplemented" << endl;
        }
    }
}
/*  operation()
   Purpose: Following the getCommands(), it decodes the operand and executes
             the mathematical operation
Parameters: Mathematical operand, type string
   Returns: void
*/
void RPNCalc::operation(string operand){
  try{
    Datum checkInt = thisStack.top();
    if ( !checkInt.isInt()){
      thisStack.pop();
      cerr << "Error: datum_not_int" << endl;
    }
    else if((int)thisStack.size() >= 2){
        Datum temp1 = thisStack.top();
        thisStack.pop();
        Datum temp2 = thisStack.top();
        thisStack.pop();
        if(temp1.isInt() and temp2.isInt()){
           if(operand == "/"){
              if (temp1.getInt() == 0){
                cerr << "Error: division by 0." << endl;
                thisStack.push(temp2);
              }
              else{
                  Datum result(division(temp2.getInt(), temp1.getInt()));
                  thisStack.push(result);
              }
           }
           if(operand == "*"){
               Datum result(multiplication(temp2.getInt(), temp1.getInt()));
               thisStack.push(result);
           }
            if(operand == "+"){
                Datum result(addition(temp2.getInt(), temp1.getInt()));
                thisStack.push(result);
            }
            if(operand == "mod"){
                if (temp1.getInt() == 0){
                   cerr << "Error: division by 0." << endl;
                   thisStack.push(temp2);
                }
                else{
                   Datum result(moduloDivision(temp2.getInt(),
                   temp1.getInt()));
                   thisStack.push(result);
                }
             }
             if(operand == "-"){
                   Datum result(subtraction(temp2.getInt(), temp1.getInt()));
                   thisStack.push(result);
             }
      }
       else{
         if (temp2.isInt()){
           thisStack.push(temp2);
         }
        cerr << "Error: datum_not_int" << endl;
       }
    }
    else{
      if (thisStack.size() > 0){ //fixes bug of removing element after error
        thisStack.pop();
      }
      cerr << "Error: empty_stack" << endl;
    }
  }
    catch (runtime_error&e){
       cerr << "Error: " << e.what() << endl;
    }
}
/*pushNumber()
   Purpose: Adds a number to the top of the stack1
Parameters: Number to be added, type integer
  Returns: None
*/
void RPNCalc::pushNumber(int number){
    thisStack.push(Datum(number));
}
/*  pushTrue
    Purpose: Adds a Datum true to the top of the stack1
 Parameters: None
    Returns: none
*/
void RPNCalc::pushTrue(){
    thisStack.push(Datum(true));
}
/*  pushFalse()
    Purpose: Adds a Datum true to the top of the stack1
 Parameters: None
    Returns: none
*/
void RPNCalc::pushFalse(){
    thisStack.push(Datum(false));
}
/* drop()
    Purpose: Removes the element at the top of the stack
 Parameters: None
    Returns: none
*/
void RPNCalc::drop(){
  try{
    thisStack.pop();
  }
  catch (runtime_error&e){
     cerr << "Error: " << e.what() << endl;
  }
}
/*clear()
   Purpose: Empties the stack and clears the CalcYouLater
Parameters: None
  Returns: none
*/
void RPNCalc::clear(){
    thisStack.clear();
}
/* print()
    Purpose: Prints the element at the top of the stack to cout
 Parameters: None
    Returns: none
*/
void RPNCalc::print(){
    try{
      if (thisStack.top().isInt()){
        cout << thisStack.top().getInt() << endl;
      }
      else if (thisStack.top().isBool()){
        if (thisStack.top().getBool()){
          cout << "#t" << endl;
        }
        else{
            cout << "#f" << endl;
        }
      }
      else if (thisStack.top().isRString()){
        cout << thisStack.top().getRString() << endl;
      }
    }
    catch (runtime_error&e){
      cerr << "Error: " << e.what() << endl;
    }
}
/* dup()
   Purpose: Duplicates the element at the top of the stack1
Parameters: None
   Returns: None
*/
void RPNCalc::dup(){
  try{
    Datum temp = thisStack.top();
    thisStack.push(temp);
   }
   catch (runtime_error&e){
      cerr << "Error: " << e.what() << endl;
   }
}
/*  swap()
    Purpose: Swaps the top two elements at the top of the stack1
Parameters: None
   Returns: None
*/
void RPNCalc::swap(){
   try{
     Datum temp1 = thisStack.top();
     thisStack.pop();
     Datum temp2 = thisStack.top();
     thisStack.pop();
     thisStack.push(temp1);
     thisStack.push(temp2);
   }
   catch (runtime_error&e){
      cerr << "Error: " << e.what() << endl;
  }
}
/*  quit()
   Purpose: Ends the CalcYouLater simulation
Parameters: None
   Returns: None
*/
void RPNCalc::quit(){
    cerr << "Thank you for using CalcYouLater." << endl;
}
/*  isNot
*  Purpose: If there is a boolean at the top of the stack, it inverts it
Parameters: None
   Returns: None
*/
void RPNCalc::isNot(){
  try{
    if(thisStack.top().isBool()){
        bool temp = thisStack.top().getBool();
        thisStack.pop();
        temp = !temp;
        thisStack.push(Datum(temp));
    }
    else{
      thisStack.pop();
      cerr << "Error: datum_not_bool" << endl;
    }
  }
  catch (runtime_error&e){
     cerr << "Error: " << e.what() << endl;
  }
}
/*  division()
   Purpose: Performs division
Parameters: Integer to be divided, integer which is the divisor
   Returns: Result of the division, type int
*/
int RPNCalc::division(int firstNum, int secondNum){
    int temp = firstNum / secondNum;
    return temp;
}
/*  multiplication()
   Purpose: Performs simple multiplication
Parameters: Integer to be multipled, integer which is the multiplier
   Returns: Result of the multiplication, type int
*/
int RPNCalc::multiplication(int firstNum, int secondNum){
    return (firstNum * secondNum);
}
/*  addition()
   Purpose: Performs addition
Parameters: Two integers to be added
   Returns: Result of the addition, type int
*/
int RPNCalc::addition(int firstNum, int secondNum){
    return (firstNum + secondNum);
}
/*  subtraction()
   Purpose: Performs subtraction
Parameters: Two integers, firstNum and secondNum to be
            subtracted from firstNum
   Returns: Result of the subtraction, type int
*/
int RPNCalc::subtraction(int firstNum, int secondNum){
    return (firstNum - secondNum);
}
/*  moduloDivision()
   Purpose: Performs moduloDivision
Parameters: Integer to be divided, integer which is the divisor
   Returns: Result of the moduloDivision, type int
*/
int RPNCalc::moduloDivision(int firstNum, int secondNum){
    return (firstNum % secondNum);
}
/*  pushRString()
   Purpose: Adds an RSTring to the top of the stack
Parameters: Rstring to be added, type toString
   Returns: void
*/
void RPNCalc:: pushRString(string RString){
    thisStack.push(Datum(RString));
}
/*  lessthan()
   Purpose: Performs < comparison
Parameters: Integers to be compared
   Returns: Result of the comparison in Boolean Type
*/
bool RPNCalc::lessThan(int firstNum, int secondNum){
    return (firstNum < secondNum);
}
/*  lessThanEqual()
   Purpose: Performs <= comparison
Parameters: Integers to be compared
   Returns: Result of the comparison in Boolean Type
*/
bool RPNCalc::lessThanEqual(int firstNum, int secondNum){
    return (firstNum <= secondNum);
}
/*  greaterThan()
   Purpose: Performs > comparison
Parameters: Integers to be compared
   Returns: Result of the comparison in Boolean Type
*/
bool RPNCalc::greaterThan(int firstNum, int secondNum){
    return (firstNum > secondNum);
}
/*  greaterThanEqual()
   Purpose: Performs >= comparison
Parameters: Integers to be compared
   Returns: Result of the comparison in Boolean Type
*/
bool RPNCalc::greaterThanEqual(int firstNum, int secondNum){
    return (firstNum >= secondNum);
}
/*  equals()
   Purpose: Performs == comparison
Parameters: Integers to be compared
   Returns: Result of the comparison in Boolean Type
*/
bool RPNCalc::equals(int firstNum, int secondNum){
    return (firstNum == secondNum);
}
/*  logicComparison()
   Purpose: Handles the input associated with logical comparisons
Parameters: String of the comparison operand to be executed
   Returns: Void
*/
void RPNCalc::logicComparison(string command){
  try{
    Datum checkInt = thisStack.top();
    if ( !checkInt.isInt()){
      thisStack.pop();
      cerr << "Error: datum_not_int" << endl;
    }
    else if(thisStack.size() >= 2){
      Datum temp1 = thisStack.top();
      thisStack.pop();
      Datum temp2 = thisStack.top();
      thisStack.pop();
      if(temp1.isInt() and temp2.isInt()){
          if(command == "<="){
              Datum temp(lessThanEqual(temp2.getInt(), temp1.getInt()));
              thisStack.push(temp);
          }
          if(command == "<"){
              Datum temp(lessThan(temp2.getInt(), temp1.getInt()));
              thisStack.push(temp);
          }
          if(command == ">"){
              Datum temp(greaterThan(temp2.getInt(), temp1.getInt()));
              thisStack.push(temp);
          }
          if(command == ">="){
              Datum temp(greaterThanEqual(temp2.getInt(), temp1.getInt()));
              thisStack.push(temp);
          }
          if(command == "=="){
              Datum temp(equals(temp2.getInt(), temp1.getInt()));
              thisStack.push(temp);
          }
      }
      else{
        if (temp2.isInt()){
           thisStack.push(temp2);
        }
        cerr << "Error: datum_not_int" << endl;
       }
    }
    else{
      if (thisStack.size() > 0){ //fixes bug of removing element after error
        thisStack.pop();
      }
      cerr << "Error: empty_stack" << endl;
    }
 }
  catch (runtime_error&e){
     cerr << "Error: " << e.what() << endl;
  }
}
/*  gotInt()
   Purpose: Checks to enure that the number entered is a valid integer
Parameters: string of input to check, int *resultis a pointer to an integer
            returned by ref.
   Returns: boolean type true if valid, false otherwise
*/
bool RPNCalc:: gotInt(string s, int *result){
        char extra;
        return sscanf(s.c_str(), " %d %c", result, &extra) == 1;
}
/*file()
   Purpose: Opens the file and executes commands from it. Filename is popped
            from stack1
Parameters: none
      Void: none
*/
void RPNCalc:: file(){
  try{
    if(thisStack.top().isRString()){
        string file = thisStack.top().getRString();
        thisStack.pop();
        file = file.substr(2, file.size() - 4);
        ifstream infile;
        infile.open(file);
        if(infile.fail()){
            cerr << "Unable to read " << file << endl;
        }
        getCommands(infile);
        infile.close();
    }
    else{
        cerr << "Error: file operand not rstring" << endl;
        thisStack.pop();
    }
 }
 catch (runtime_error&e){
     cerr << "Error: " << e.what() << endl;
 }
}
/*checkIf()
   Purpose: Performs the if-statement comparison of Datums on the stack.
            Returns runtime error if empty_stack, error if invalid data type.
Parameters: none
      Void: none
*/
void RPNCalc::checkIf(){
  try{
    if (thisStack.size() < 3){
      cerr << "Error: empty_stack" << endl;
      thisStack.clear();
    }
    else{
      Datum test3 = thisStack.top();
      thisStack.pop();
      Datum test2 = thisStack.top();
      thisStack.pop();
      Datum test1 = thisStack.top();
      thisStack.pop();
      if (!test1.isBool()){
        cerr << "Error: expected boolean in if test" << endl;
      }
      else if ( !test2.isRString() || !test3.isRString()){
        cerr << "Error:expected rstring in if branch" << endl;
      }
      else{
        if (test1.getBool()){
          thisStack.push(test2);
          exec();
        }
        else{
          thisStack.push(test3);
          exec();
        }
      }
    }
  }
  catch (runtime_error&e){
     cerr << "Error: " << e.what() << endl;
  }
}
/*exec()
   Purpose: Checks if item on stack is RString and executes the RString.
            Reports error otherwise: runtime(empty stack) & invalid data type.
Parameters: none
      Void: none
*/
void RPNCalc::exec(){
  try{
     if(thisStack.top().isRString()){
         string anRString = thisStack.top().getRString();
         anRString = anRString.substr( 2, anRString.size() - 4);
         thisStack.pop();
         stringstream input(anRString);
         getCommands(input);
     }
     else{
         cerr << "Error: cannot execute non rstring" << endl;
         thisStack.pop();
     }
  }
  catch (runtime_error&e){
      cerr << "Error: " << e.what() << endl;
  }
}
/*equalityComparison()
   Purpose: Performs == comparison for Datums of all data types
            Fixes bug that allows all types of Datum types to be
            compared.
*/
void RPNCalc::equalityComparison(){
  try{
    if ((int)thisStack.size() >= 2){
        Datum temp1 = thisStack.top();
        thisStack.pop();
        if (temp1.isRString()){//RSTRING COMPARISONS
           string temp3 = temp1.getRString();
           Datum checker = thisStack.top();
           thisStack.pop();
           if (checker.isRString()){
              string temp2 = checker.getRString();
              if (temp3.compare(temp2) == 0){
                 pushTrue();
              }
              else{
                pushFalse();
              }
           }
           else{
             pushFalse();
           }
         }
        else if (temp1.isBool()){//BOOLEAN COMPARISONS
           Datum temp4 = thisStack.top();
           thisStack.pop();
           if (temp4.isBool()){
             if (temp1.getBool() == temp4.getBool()){
               pushTrue();
             }
             else{
               pushFalse();
             }
           }
          else{
            pushFalse();
          }
        }
        else if (temp1.isInt()){//INTEGER COMPARISONS
           if (thisStack.top().isInt()){
           int temp5 = temp1.getInt();
           int temp6 = thisStack.top().getInt();
           thisStack.pop();
           if (temp5 == temp6){
             pushTrue();
           }
           else{
             pushFalse();
           }
         }
         else{
           thisStack.pop();
            pushFalse();
         }
        }
    }
  else{
      if (thisStack.size() > 0){ //fixes bug of removing element after error
        thisStack.pop();
      }
      cerr << "Error: empty_stack" << endl;
   }
 }
  catch (runtime_error&e){
     cerr << "Error: " << e.what() << endl;
  }
}
