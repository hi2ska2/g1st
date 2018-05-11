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

#include "EqEigen.h"

class EqAllElectron : public EqEigen {
 public:
  EqAllElectron(Thing& thing);

  void apply();
};

#endif

