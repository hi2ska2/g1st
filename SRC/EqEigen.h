////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqEigen.h

#ifndef EqEigenH
#define EqEigenH

#include "Equation.h"

class EqEigen : public Equation {
 public:
  EqEigen(std::string name,std::string variableName,Thing& thing);

  virtual void apply() = 0;
  virtual void collectUnknownIndices(std::map<Place,int>& unknownIndices);
  virtual void collectUnknownIndicesSemiconductor(std::map<Place,int>& unknownIndices);
  virtual int getRow(const Place& place);
  SolveType getSolveType() { return EIGEN; }
  void getEigenValue();
  virtual void setUnknownIndices(std::map<Place,int>& unknownIndices);
  virtual void showUnknownIndices();

 protected:
  Triplet<double> _aMatrix;
  Triplet<double> _bMatrix;
  std::vector<double> _eigenvalues;
  std::vector<double> _eigenvectors;
  int _nEigen;

  std::string _variableName;
  VariableId _variableId;

  std::map<Place,int>* _unknownIndices;
};

#endif
