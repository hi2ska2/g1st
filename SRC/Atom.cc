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
  // Mesh
  _mesh.clear();
  _nMeshPoint = 100; // A trial number
  // The distance must be assigned.

  _field = new Field();
}

void Atom::set(ArgList* argList)
{
  if (argList->doesExist("type")) {
    std::string type = argList->lookup("type",std::string("si"));
    if      (type.compare("al")==0) { _type = AtomType::ALUMINIUM; _nProton = 13; } // 13
    else if (type.compare("si")==0) { _type = AtomType::SILICON;   _nProton = 14; } // 14
    else myReportError("Atom::set(argList)");
  }
}

int Atom::get_nMeshPoint() { return _nMeshPoint; }

int Atom::get_nProton() { return _nProton; }
