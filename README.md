A. TITLE AND AUTHOR NAME
 Comp15
 PROJ1 : CalcYouLater
 Anesu Gavhera
 09/22/2020

B. PROGRAM PURPOSE
 The purpose of this project is to simulate a calculator in C++ using classes
 and object oriented programming paradigms. The CalcYouLater accepts simple
 arithmetic operations and comparisons in RPN notation, and is able to read
 commands from an input file entered as a command line parameter or within the
 program interface.


C. ACKNOWLEDGEMENTS FOR HELP RECEIVED DURING PROGRAMMING
 ** Tufts University Comp15 staff
   ~  for initial draw up of Datum.h class implementing the data structure in
      which operands and operators for this CalcYouLater are stored.
   ~  for providing the gotInt() function within RPN.h

D. FILES PROVIDED
 DatumStack.h -> intializes the DatumStack class and its methods/variables.
 DatumStack.cpp -> defines the methods and functions associated with the
                  DatumStack class.
 Datum.h -> programmed by Tufts University Comp15 staff and defines the data
            structure in which operands and operators are stored.
 main.cpp -> declares an instance of the CalcYouLater and initalizes
             the running of the CalcYouLater.
 parser.cpp -> defines the methods and code associated with the parseRString
              function. FUNCTION DOES NOT TERMINATE UNTIL ENOUGH BRACES
              ARE INSERTED WITHIN AN RSTRING.
 RPNCalc.h -> declares the members and functions for the CalcYouLater
              uses the stack class from DatumStack as a temporary storage for
              operands.
RPNCalc.cpp -> defines the member functions for the CalcYouLater intialized in
               RPNCalc.h
 parser.h -> initializes the parseRString function
 
 testDatumStack.cpp -> testing the DatumStack class and parseRString function
                       declared in the parser.h and parser.cpp files.
 README -> ** THIS CURRENTLY OPEN FILE **

Files used to provide commands to the CalcYouLater program during testing:
 testArithmetic.cylc -> targets mathematical operations (+ - / mod * ) and
                        errors associated invalid data types and insufficient
                        operands.
 testExec.cylc       -> targets the exec() function by providing commands
                        as RStrings and operating on them. Also includes cases
                        that target errors associated invalid data types
                        and insufficient operands
 testFile.cylc       -> targets the file() function by providing filenames
                        within RStrings and reading commands from them.
                        Includes invalid data types and fake files to test
                        test errors.
 testIf.cylc         -> targets the if() function and comparison arithmetic
                        operations ( > < <= >= == ) with various data types



E. COMPILATION
 Program compiled using the following makefile:
   CXX      = clang++
   CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
   LDFLAGS  = -g3

   INCLUDES = $(shell echo *.h)

   CalcYouLater: DatumStack.o Datum.o parser.o RPNCalc.o main.o
     ${CXX} ${LDFLAGS} $^ -o $@

   testDatumStack: DatumStack.o Datum.o parser.o testDatumStack.cpp
     ${CXX} ${LDFLAGS} $^ -o $@

   %.o: %.cpp ${INCLUDES}
     ${CXX} ${CXXFLAGS} -c -o $@ $<

   %.cylc:  %.cyl
     ./cylc $^

   .PHONY: clean
   clean:
     rm -f ${EXECS} *.o *.dSYM./

 make CalcYouLater
     generates an executable called CalcYouLater which provides the main user
     interface for the RPN calculator. Derives its main() from main.cpp
 make testDatumStack
     resulted in the generation of an executable called testDatumStack
     where I ran the test for the class by creating a rogue instance of the
     classes and using the member functions to modify the instances.

F. DATA STRUCTUES USED
 The class feature of C++ object oriented programming was used.
 These classes were used to create a stack data structure called DatumStack.
 This stack accepts elements of type Datum (int, bool, RString) and stores them
 in a last-in-first-out queue. STD vectors were used to implement the stack
 because they are self expanding with near-perfect member functions that rarely
 cause segmentation and logic error faults. As a result less time was used
 troubleshooting bugs.

G. TESTING
 CalcYouLater was tested by executing it with *.cylc that target
 all test cases of specific member functions within the CalcYouLater. Towards
 the end of each .cylc file, I specifically target the different
 errors associated with the these functions, as well attempting to execute the
 functions with different combinations of invalid data types. These files were
 executed with my program and the provided program, then the outputs were diff
 compared to find latent bugs within RPNCalc.h

 The DatumStack class was tested by declaring rogue instances of lists within
 the main and running the member functions on them. The parseRString function
 was tested within the same main program.
