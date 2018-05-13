////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqEval.cc

#include "EqEval.h"

EqEval::EqEval(std::string name,Thing& thing)
  : Equation(name,thing),
    _field(*(_thing.getField()))
{
  
}
