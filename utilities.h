#pragma once

#include <string>

//Simple input validator
class Valid
{
  public:
    static bool isDouble(std::string);
    static bool hasSpaces(std::string);
    static bool isEquation(std::string);
};
