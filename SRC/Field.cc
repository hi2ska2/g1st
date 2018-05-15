////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Field.cc

#include "Field.h"

Field::Field()
{
}

bool Field::addVariableName(std::string variableName,VariableId& variableId)
{
  std::pair<VariableNameIter,bool> result = 
    _variableNames.insert(VariableNamePair(variableName
					   ,VariableId(_variableNames.size())
					   )
			  );
  if (result.second) { myReport(variableName + " is inserted."); } 
  //else               { myReport(variableName + " is found.");    }
  variableId = (result.first)->second;
  //myReport("variableId's id is " + myIntToString(variableId.getId()));
  return result.second;
}

Variable& Field::getArrayVariable(const std::string& variableName,int n,int m,int l)
{
  VariableId dummy;
  return getArrayVariable(variableName,dummy,n,m,l);
}

Variable& Field::getArrayVariable(const std::string& variableName,VariableId& variableId,int n,int m,int l)
{
  Variable* toBeInserted = NULL;
  if (addVariableName(variableName,variableId)) {
    toBeInserted = new Variable(variableName,n,m,l);
  } 
  addVariableName(variableName,variableId);
  std::pair<ArrayVariableIter,bool> result = 
    _arrayVariables.insert
    (ArrayVariablePair(variableId,toBeInserted) );
  return *((result.first)->second);
}
