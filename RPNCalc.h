/*
 *
 *  COMP 15 PROJ 1 CALCYOULATER
 *
 *  RPNCalc.h
 *
 *  Responsible for providing methods for calculation with
 *  a Datum Stack.
 *
 *
 *  Written by: Anesu Gavhera
 *          on: 10/17/20
 */

#include <iostream>
#include "DatumStack.h"

class RPNCalc{
    public:
        RPNCalc();
        ~RPNCalc();
        void run();
        void pushNumber(int number);
        void drop();
        void clear();
        void print();
        void dup();
        void swap();
        void quit();
        void logicComparison(string input);
        void exec();
        void file();
        void checkIf();
        void isNot();
    private:
        DatumStack thisStack;
        void pushRString(string RString);
        void operation(string input);
        void getCommands(istream &input);
        void pushTrue();
        void pushFalse();
        int addition(int firstNum, int secondNum);
        int multiplication(int firstNum, int secondNum);
        int subtraction(int firstNum, int secondNum);
        int division(int firstNum, int secondNum);
        int moduloDivision(int firstNum, int secondNum);
        bool gotInt(string s, int *result);
        bool lessThan(int firstNum, int secondNum);
        bool lessThanEqual(int firstNum, int secondNum);
        bool greaterThan(int firstNum, int secondNum);
        bool greaterThanEqual(int firstNum, int secondNum);
        bool equals(int firstNum, int secondNum);
        void equalityComparison();
};
