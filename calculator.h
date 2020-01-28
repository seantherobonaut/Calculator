#pragma once

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include "utilities.h"

class BasicCalc
{
  private:
    std::vector<std::string> log;
    double mathAdd(double, double);
    double mathMult(double, double);
    double mathDivide(double, double);
    void solveAdditionPosNeg(std::string &);
    void solveMultiplicationDivision(std::string &);
    void fixNegatives(std::string &);
  public:
    void solve(std::string &);
    void printSteps();
};
