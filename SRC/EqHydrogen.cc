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

  Variable& hatree = _field.getArrayVariable("Hatree");

  // Electron
  Variable& electron = _field.getArrayVariable("Electron");

  for (int level=0; level<_atom.get_nProton(); ++level) {
  }
}
