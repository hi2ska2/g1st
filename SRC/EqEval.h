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
  EqEval(std::string name,Thing& thing);

  virtual void evaluate() { myReportError("EqEval::evaluate()"); } 
  SolveType getSolveType() { return EVAL; }

 protected:
  // It has a member variable.
  Field& _field; 
};

#include "EqHydrogen.h"

#endif
