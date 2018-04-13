/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Crystal.cc

#include "Crystal.h"

#include "utilities.h"

Crystal::Crystal(const std::string& name)
  : Thing(name,ThingType::CRYSTAL)
{
  _latticeConstant = 1.0; // 1 m
  // _latticeVector
  _latticeBasis.clear();
  
}

void Crystal::set(ArgList* argList)
{
  if (argList->doesExist("latticeconstant")) {
    _latticeConstant = argList->lookup("latticeconstant",1.0);
  }
}

void Crystal::setLatticeVector(ArgList* argList)
{
  //myReportError("Crystal::setLatticeVector(argList)");
}

void Crystal::setLatticeBasis(ArgList* argList)
{
  //myReportError("Crystal::setLatticeBasis(argList)");
}
