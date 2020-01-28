#include <iostream>
#include <string>
#include <regex>
#include "calculator.h"

using namespace std;

int main()
{
  //TODO start using iomanip for precision numbers and to not have num.000000
  //TODO start using string.insert and string.erase instead of just modifying string.replace
  //TODO keep answer through equations to keep modifying answer if you type in ANS-(new equation)
  //TODO replace a result that is 0 with nothing, do not insert 0 or 0.0000
  
  cout << "-------------------------------------------------------------" << endl;
  cout << "Welcome to my basic calculator! (work in progress)" << endl;
  cout << "Please enter an equation or type \"exit\" to close the program." << endl;
  cout << "-------------------------------------------------------------" << endl;

  string uInput = "";
  BasicCalc *calc = new BasicCalc;
  
  //Begin main loop
  while(uInput != "exit")
  {
    cout << endl << "Input: ";
    getline(cin, uInput);

    //If the user doesn't enter exit, actualy enters something, and it is an equation, proceed to solving
    if(uInput != "exit")
    {
      if(uInput != "")
      {
        uInput = regex_replace(uInput, regex(" "), "");
        if(Valid::isEquation(uInput))
        {
          calc->solve(uInput);

          //Check to see if equation can be parsed into a number then do that. If it can't, output error
          if(Valid::isDouble(uInput))
            cout << "Answer: " << stof(uInput) << endl;
          else
            cout << "Error. (See steps below)" << endl;
        
          //Output steps taken to get the answer
          calc->printSteps();
        }
        else
          cout << "Invalid equation. Try again." << endl;
      }
      else
        cout << "You gotta enter something... come on!" << endl;
    }
    else
      cout << "Thanks for using my calculator!" << endl;
  }

  delete calc;
  calc = nullptr;

  return 0;
}
