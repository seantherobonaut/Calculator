#include "calculator.h"

double BasicCalc::mathAdd(double num1, double num2)
{
  return num1+num2;
}
double BasicCalc::mathMult(double num1, double num2)
{
  return num1*num2;
}
double BasicCalc::mathDivide(double num1, double num2)
{
  return num1/num2;
}
void BasicCalc::solve(std::string &input)
{
  //Convert all -- to + and - to +-
  this->fixNegatives(input);

  //Record initial state of equation
  this->log.push_back(input);
        
  //Pass string to solve by reference through order of operations
  solveMultiplicationDivision(input);
  solveAdditionPosNeg(input);
}
//solve * and /
void BasicCalc::solveMultiplicationDivision(std::string &equation)
{
  char opChar = '\0';
  std::string operand1 = "";
  std::string operand2 = "";
  unsigned startPos=0;
  unsigned opPos=0;
  unsigned endPos=0;
  double result = 0;

  for(unsigned i=0; i<equation.size(); i++)
  {
    this->fixNegatives(equation);

    if(equation[i] == '*' || equation[i] == '/')
    {
      //set the operator sign and get the position it occured in
      opChar = equation[i];
      opPos=i;
     
      //find the starting position of the inner equation delimited by +-*/
      for(int ii=i-1; ii>-1 && (equation[ii]!='+' && equation[ii]!='*' && equation[ii]!='/'); ii--)
        startPos=ii;
     
      //find the ending position of the inner equation delimited by +-*/
      for(int ii=i+1; ii<(int)equation.size() && (equation[ii]!='+' && equation[ii]!='*' && equation[ii]!='/'); ii++)
        endPos=ii;
      
      //set string operands from equation
      operand1 = equation.substr(startPos, (opPos-startPos));
      operand2 = equation.substr((opPos+1), (endPos-opPos));
      
      //check to make sure the numbers are valid before solving any equations
      if(Valid::isDouble(operand1) && Valid::isDouble(operand2))
      {
        //do the math
        if(opChar == '*')
          result = this->mathMult(stof(operand1),stof(operand2));
        
        if(opChar == '/')
          result = this->mathDivide(stof(operand1),stof(operand2));
        
        //first replace the space with nothing...then insert the solution
        std::string inserted = std::to_string(result);

        equation.replace(startPos, (endPos+1)-startPos, "");
        equation.replace(startPos,0,inserted);   
        
        //reset the iteration position to the beginning of the number inserted
        i = startPos;
        
        //record changes
        this->log.push_back(equation);
      }
    }        
  }  
}
//Solve + and -
void BasicCalc::solveAdditionPosNeg(std::string &equation)
{
  char opChar = '\0';
  std::string operand1 = "";
  std::string operand2 = "";
  unsigned startPos=0;
  unsigned opPos=0;
  unsigned endPos=0;
  double result = 0;

  for(unsigned i=0; i<equation.size(); i++)
  {
    this->fixNegatives(equation);

    if(equation[i] == '+')
    {
      //set the operator sign and get the position it occured in
      opChar = equation[i];
      opPos=i;
     
      //find the starting position of the inner equation delimited by +-*/

      for(int ii=i-1; ii>-1 && (equation[ii]!='+' && equation[ii]!='*' && equation[ii]!='/'); ii--)
        startPos=ii;
     
      //find the ending position of the inner equation delimited by +-*/
      for(int ii=i+1; ii<(int)equation.size() && (equation[ii]!='+' && equation[ii]!='*' && equation[ii]!='/'); ii++)
        endPos=ii;
      
      //set string operands from equation
      operand1 = equation.substr(startPos, (opPos-startPos));
      operand2 = equation.substr((opPos+1), (endPos-opPos));
      
      //check to make sure the numbers are valid before solving any equations
      if(Valid::isDouble(operand1) && Valid::isDouble(operand2))
      {
        //do the math
        if(opChar == '+')
          result = this->mathAdd(stof(operand1),stof(operand2));
        
        //first replace the space with nothing...then insert the solution
        std::string inserted = std::to_string(result);

        equation.replace(startPos, (endPos+1)-startPos, "");
        equation.replace(startPos,0,inserted);
        
        //reset the iteration position to the beginning of the number inserted
        i = startPos;
        
        //record changes
        this->log.push_back(equation);
      }
    }        
  }
}
void BasicCalc::fixNegatives(std::string &equation)
{
  equation = regex_replace(equation, std::regex("--"), "+");

  char character = '\0';

  for(unsigned i=0; i<equation.size(); i++)
  {
    if(equation[i] == '-' && i!=0)
    {
      //find position of character right before the negative sign
      character = equation[i-1];
    
      //if logic goes here (to see how many times it finds duplicates or skips them log each time it finds a minus sign)
      if(character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9')
      {
        equation.replace(i,0,"+");
        
        //reset the iteration position to the beginning of the number inserted
        i++;
      }
    }        
  }
}
void BasicCalc::printSteps()
{
  for(int i=0; i<this->log.size(); i++)
    std::cout << "Step" << i+1 << ": " << log[i] << std::endl;

  this->log.clear();
}
