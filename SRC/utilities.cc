////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// utilities.cc

#include "utilities.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

std::string myDoubleToString(double number)
{
  std::ostringstream ss;
  ss << number;
  return ss.str();
}

std::string myIntToString(int number)
{
  std::ostringstream ss;
  ss << number;
  return ss.str();
}

std::string myIntToString(int number,int digit)
{
  std::ostringstream ss;
  ss << std::setw(digit) << std::setfill('0') << number;
  return ss.str();
}

void myReport(const std::string& message) {
  std::cout << message << "\n";
  std::cout.flush();
}

void myReportError(const std::string& message) {
  std::cout << "Error: " << message << "\n";
  std::cout.flush();
  exit(1);
}
