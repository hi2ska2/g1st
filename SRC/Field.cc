////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Field.cc

#include "Field.h"

Variable& Field::getArrayVariable(const std::string& variableName,int n,int m,int l)
{
  VariableId dummy;
  return getArrayVariable(variableName,dummy,n,m,l);
}

Variable& Field::getArrayVariable(const std::string& variableName,VariableId& variableId,int n,int m,int l)
{
  // Empty implementation
}
