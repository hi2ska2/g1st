////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqAllElectron.h

#ifndef EqAllElectronH
#define EqAllElectronH

#include "Equation.h"

class EqAllElectron : public Equation {
 public:
  EqAllElectron(Thing& thing);
  
  SolveType getSolveType() { return NEWTON; }
};

#endif

