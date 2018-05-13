////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqNewton.h

#ifndef EqNewtonH
#define EqNewtonH

#include "Equation.h"

class Place;
class RealTriplet;

class EqNewton : public Equation {
 public:
  EqNewton(std::string name,std::string variableName,Thing& thing,int nNode=0);

  //virtual void apply(std::map<Place,int>& unknownIndices) { myReportError("EqNewton::apply(unknownIndices)"); }
  virtual void apply() { myReportError("EqNewton::apply(unknownIndices)"); }
  virtual void buildJacobianResidue(RealTriplet& jacobian,std::vector<double>& residue,const std::map<Place,int>& unknownIndices);
  virtual void collectUnknownIndices(std::map<Place,int>& unknownIndices);
  //void collectUnknownIndicesSemiconductor(std::map<Place,int>& unknownIndices);
  virtual void compareUnknownIndices(const Place& place);
  virtual void copy_old();
  virtual int getRow(const Place& place);
  SolveType getSolveType() { return NEWTON; }
  virtual void prepare(int iNewton=0);
  virtual void referTo(std::vector<Equation*>& otherEquations) { }
  virtual void restore(); 
  virtual void showDebug() { }
  virtual void setUnknownIndices(std::map<Place,int>& unknownIndices);
  virtual void showUnknownIndices();
  virtual void showUnknownIndices(std::map<Place,int>& unknownIndices);
  /*
  virtual double update(std::vector<double>& solution,
			std::map<Place,int>& unknownIndices,
			bool& valid);
  */
  virtual double update(std::vector<double>& solution,
			std::map<Place,int>& unknownIndices,
			double xref,
			bool& valid);
  virtual double update(std::vector<double>& solution,
			std::map<Place,int>& unknownIndices,
			std::vector<double>& xref,
			bool& valid);
  /*
  virtual double updateSemiconductor(std::vector<double>& solution,
				     std::map<Place,int>& unknownIndices,
				     double xref,
				     bool& valid);  
  */

 protected:
  Balance& getBalance(const int& row) {
    std::pair< std::map<int,Balance>::iterator,bool > r;
    r = _balances.insert(std::pair<int,Balance>(row,Balance()));
    return (r.first)->second;
  }

  std::map<int,Balance> _balances; 
  std::string _variableName;
  VariableId _variableId;
  std::string _variable_old1Name;
  VariableId _variable_old1Id;
  std::string _variable_old2Name;
  VariableId _variable_old2Id;

  std::map<Place,int>* _unknownIndices;

  // It has a member variable.
  Field& _field;
};

#endif
