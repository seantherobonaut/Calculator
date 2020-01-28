#include "utilities.h"

//Valid class member functions
//Checks if string is a double
bool Valid::isDouble(std::string num)
{
  bool status = true;
  int numDecimals = 0;
  
  //If the number has a negative start the counter 1 digit later
  unsigned currentDigit = 0;
  if(num[0] == '-')
    currentDigit = 1;
    
  //Iterate through the string to see if it is a proper number
  while(currentDigit < num.size())
  {
    //check to make sure the string is nothing but numbers and decimals
    if(!isdigit(num[currentDigit]) && num[currentDigit] != '.')
      status = false;
    
    //check if there is more than one decimal
    if(num[currentDigit] == '.')
      numDecimals++;
    
    currentDigit++;
  }
  
  if(numDecimals > 1)
    status = false;

  return status;
}
//Checks if string contains spaces
bool Valid::hasSpaces(std::string input)
{
  bool status = false;
  for(unsigned i=0; i<input.size(); i++)
    if(input[i] == ' ')
      status = true;
      
  return status;
}
//Checks if string is a valid equation 
//TODO requre at least 1 operand, accept equations starting with negative numbers
bool Valid::isEquation(std::string input)
{
  bool status = true;
  bool checkChar;
  
  //check if the string contains only these characters
  char whitelist[] = {'+', '-', '*', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
  for(unsigned i=0; i<input.size(); i++)
  {
    //iterate through the list of chars and find matches
    checkChar = false;
    for(unsigned ii=0; ii<( sizeof(whitelist)/sizeof(whitelist[0]) ); ii++)
      if(input[i] == whitelist[ii])
        checkChar = true;   

    if(!checkChar)
      status = false;
  }

  //Check for any operands side by side in the equation
  unsigned counter = 0;
  bool valid = true;
  while(counter < input.size() && valid == true)
  {
    if(input[counter] == '+' || input[counter] == '-' || input[counter] == '*' || input[counter] == '/')
      if(input[counter+1] == '+' || input[counter+1] == '*' || input[counter+1] == '/')
        valid = false;
    
    counter++;
  }
  
  //Check for any operands at the very beginning or end of the equation
  if(input[0] == '+' || input[0] == '*' || input[0] == '/')
    valid = false;
  if(input[(input.size()-1)] == '+' || input[(input.size()-1)] == '-' || input[(input.size()-1)] == '*' || input[(input.size()-1)] == '/')    
    valid = false;
  
  //If anything is flagged as not valid, set status to false
  if(!valid)
    status = false;

  //TODO check equation syntax (allowed combinations)
  /*
    find the position of the first operand and check to see if there are any operands to the right
    special cases  --# +-# *-# /-#  ....ignore decimals for now
  */

  return status;
}
