////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Variable.h

#ifndef VariableH
#define VariableH

//#include "Mesh.h"

#include <vector>
#include <iostream>
#include <string>
#include "VariableId.h"
#include "utilities.h"

class Variable {
 public:
 Variable(std::string name, int n, int m=1, int l=1) // 3D, no specification for _variableId
   : _name(name), _contents(std::vector<double>(n*m*l,0.0)), 
    _inner_ii(n), _inner_jj(m), _inner_kk(l)
  {
    _coefficientForPlot = 1.0;
    //myReport(name + "'s contents size is " + myIntToString(_contents.size()) + ".");
  }
  virtual ~Variable() {}
  
  virtual double& operator[](int ii) { return _contents[ii]; }
  virtual double& operator()(int ii,int jj=0,int kk=0) { return _contents[(ii*_inner_jj+jj)*_inner_kk+kk]; }
  double getCoefficientForPlot() { return _coefficientForPlot; }
  int getInnerSize() const { return _inner_ii*_inner_jj*_inner_kk; }
  int getInnerSize()       { return _inner_ii*_inner_jj*_inner_kk; }
  std::string getName() { return _name; }
  int getSize() const { return _contents.size(); }
  int getSize()       { return _contents.size(); }
  void resize(int n, int m=1, int l=1) {
    if (!(getSize()==n*m*l && _inner_ii==n && _inner_jj==m && _inner_kk==l)) {
      _contents.resize(n*m*l,0.0);
      _inner_ii = n;
      _inner_jj = m;
      _inner_kk = l;
    }
  }
  VariableId getId() { return _variableId; }
  void set(const double org) {
    for (int ii=0; ii<getSize(); ++ii) _contents[ii] = org;
  }
  void set(Variable& org) {
    if (getSize()==org.getSize()) {
      for (int ii=0; ii<getSize(); ++ii) _contents[ii] = org[ii];
    } else {
      myReportError("Variable::set(org) : Variable size should be the same.");
    }
  }
  void setCoefficientForPlot(double coefficientForPlot) {
    _coefficientForPlot = coefficientForPlot;
  }
  void show() {
    myReport("Variable::show()");
    std::cout << this->getSize() << " elements.\n";
    //myReport("It has " + myIntToString(_contents.size()) + " elements.");
    /*
    for (int ii=0; ii<_contents.size(); ++ii) {
      std::cout << _contents[ii] << "\n";
    }
    */
    myReport("Variable::show()");
  }

 protected:
  std::string _name;
  std::vector<double> _contents;
  int _inner_ii; // size of first  dimension
  int _inner_jj; // size of second dimension
  int _inner_kk; // size of third  dimension
  VariableId _variableId;
  double _coefficientForPlot;
};

#endif
