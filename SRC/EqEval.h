////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqEval.h

#ifndef EqEvalH
#define EqEvalH

#include "Equation.h"

class EqEval : public Equation {
 public:
 EqEval(std::string name,Thing& thing) : Equation(name,thing) { }

  virtual void evaluate() { myReportError("EqEval::evaluate()"); } 
  SolveType getSolveType() { return EVAL; }
};

#include "EqHydrogen.h"

#endif
