////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqEigen.cc

#include "EqEigen.h"

#include "numericalsolvers.h"

EqEigen::EqEigen(std::string name,std::string variableName,Thing& thing)
  : Equation(name,thing),
    _variableName(variableName)
{
}

void EqEigen::collectUnknownIndices(std::map<Place,int>& unknownIndices)
{
}

void EqEigen::collectUnknownIndicesSemiconductor(std::map<Place,int>& unknownIndices)
{
  // Empty implementation
}

// test 
void EqEigen::getEigenValue() {
  //myReportError("EqEigen::getEigenValue()");
  // actually solve the eigenvalue problem

  apply();

  solveEigenValue(_aMatrix,_bMatrix,_eigenvalues,_eigenvectors,_nEigen);

  postprocess();
}

int EqEigen::getRow(const Place& place)
{
  std::map<Place,int>::iterator thePair =  (*_unknownIndices).find(place);
  if (thePair == (*_unknownIndices).end()) {
    myReport("EqEigen::getRow(place)");
    place.show();;
    //compareUnknownIndices(place);
    myReportError("EqEigen::getRow(place)");
  }
  return thePair->second;
}

void EqEigen::setUnknownIndices(std::map<Place,int>& unknownIndices) {
  _unknownIndices = &unknownIndices;

  //showUnknownIndices();
}

void EqEigen::showUnknownIndices() {     
  myReport("EqEigen::showUnknownIndices()");
  std::cout << "_name = " << _name << ", _unknownIndices = " << _unknownIndices << "\n";
  for (std::map<Place,int>::iterator it=(*_unknownIndices).begin(); it!=(*_unknownIndices).end(); ++it) {
    (it->first).show();
    std::cout << "   Its index is " << it-> second << "\n";
  }
}
