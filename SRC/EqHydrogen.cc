////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqHydrogen.cc

#include "EqHydrogen.h"

EqHydrogen::EqHydrogen(Thing& thing)
  : EqEval("EqHydrogen",thing),
    _atom(static_cast<Atom&>(thing))
{
  if (thing.checkType(ThingType::ATOM)) {
    // Nothing to do
  }
  else {
    myReportError("EqHydrogen::EqHydrogen(thing)");
  }    
}

void EqHydrogen::evaluate()
{
  //myReportError("EqHydrogen::evaluate()");

  // Hatree

  Variable& hartree = _field.getArrayVariable("Hartree",_atom.get_nMeshPoint());
  for (int ir=0; ir<_atom.get_nMeshPoint(); ++ir) {
    hartree[ir] = -double(_atom.get_nProton())/double(ir+1);
    std::cout << hartree[ir] << "\n";
  }

  // Electron
  Variable& electron = _field.getArrayVariable("Electron",_atom.get_nMeshPoint());
  
  /*  
  for (int level=0; level<_atom.get_nProton(); ++level) {
    std::cout << "level = " << level << "\n";
    std::cout << electron[level] << "\n";
  }
  */
}
