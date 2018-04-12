/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Atom.cc

#include "Atom.h"

#include "utilities.h"

Atom::Atom(const std::string& name)
  : Thing(name,ThingType::ATOM)
{
}

void Atom::set(ArgList* argList)
{
  if (argList->doesExist("type")) {
    std::string type = argList->lookup("type",std::string("si"));
    if (type.compare("si")==0) _type = AtomType::SILICON;
    else myReportError("Atom::set(argList)");
  }
}
