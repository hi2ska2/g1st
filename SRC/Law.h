////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Law.h

#ifndef LawH
#define LawH

#include <string>
#include <map>

#include "Equation.h"
#include "EqNewton.h"
#include "EqEigen.h"

class Law {
 public:
 Law(std::string& name,int iteration,bool ignore)
   : _name(name), _iteration(iteration), _ignore(ignore) 
  {
    
  }
  
  Equation* addEquation(Equation* equation) { _equations.push_back(equation); return equation;  }
  Law* addSubLaw(Law* law) { _sublaws.push_back(law); return law; }
  void analyze(int indentation=3);
  std::string getName() { return _name; }
  double solve(bool& valid,ArgList* solverArgList); 
  void plot(const std::string& fileName);
  void plot(const std::string& filePrefix,bool appendCount,int count);
  void postprocess();
  void record(std::string recordFileName);
  void referTo();
  void restore();
  
 protected:
  std::string _name;
  std::vector<Law*> _sublaws;
  std::vector<Equation*> _equations;
  
  int _iteration;
  bool _ignore;
  
  // Following members are taken from Coupled.
  void buildJacobianResidue();
  void setUnknownIndices();
  double update(bool& valid);
  
  RealTriplet _jacobian;
  std::vector<double> _residue;
  std::vector<double> _solution;
  std::map<Place,int> _unknownIndices;
};

#endif
