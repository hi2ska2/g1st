////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Equation.h

#ifndef EquationH
#define EquationH

#include <vector>

#include "ParseTree.h"
#include "Thing.h"
#include "Variable.h"
#include "Sparse.h"
#include "Balance.h"

// EVAL: Evaluating the given expression
// NEWTON: Newton-Raphson method
// EIGEN: Eigenvalue-eigenvector problem
enum SolveType { EVAL, NEWTON, EIGEN };
static std::string SolveTypeStrArray[] = {"EVAL", "NEWTON", "EIGEN"};

class Equation {
 public:
  Equation(std::string name,Thing& thing) 
    : _name(name), _thing(thing) { }
  
  virtual void copy_old() { }
  std::string getName() { return _name; }  
  virtual SolveType getSolveType() = 0;
  Thing& getThing() { return _thing; }
  bool isValid() { return true; /* return _thing.isInitialized(); */ }
  virtual void newtonPlot(int iNewton) { }
  virtual void plot(const std::string& fileName) { }
  virtual void postprocess() { /*myReport("Equation::postprocess()");*/ }
  virtual void referTo(std::vector<Equation*>& otherEquations) { }
  virtual void restore() { }
  virtual void setBodyArgList(ArgList* argList) { }
  virtual void showDebug() { }
  
 protected:
  std::string _name;
  //SolveType _solveType;
  Thing& _thing;
};

#endif
