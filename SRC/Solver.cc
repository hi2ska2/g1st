////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Solver.cc

#include "Solver.h"
#include "utilities.h"

Solver::Solver(Law* law,World* world,History* history,ArgList* argList)
  : _law(law), 
    _world(world), 
    _history(history),
    _argList(argList) 
{ 
  if (!_law) myReportError("Solver::Solver(law,world,history,argList)");

  //_iteration = _argList->lookup("iteration",12); 
  _initialStep = _argList->lookup("initialstep",0.01); 
  _minStep = _argList->lookup("minstep",1e-3);
  _maxStep = _argList->lookup("maxstep",1e-1);
  _increment = _argList->lookup("increment",2.0);
  _decrement = _argList->lookup("decrement",2.0);
  //_plotFileName = _argList->lookup("plot",std::string("noname"));
  if (_argList->doesExist("plot")) {
    _doPlot = true;
    //myReportError("Solver::Solver(law,world,history,argList)");
  } else {
    _doPlot = false;
  }
  _plotPrefix = _argList->lookup("plotprefix",std::string("noname"));
  _plotCount = _argList->doesExist("plotcount");
  _recordFileName = _argList->lookup("record",std::string("noname")); 
  _bookName = _argList->lookup("book",std::string("book"));
  _matrixSolverName = argList->lookup("matrixsolver",std::string("umfpack"));
  _doZero = _argList->doesExist("dozero"); 
  _inits.clear();
  _goals.clear();
  _breakcriteria.clear();
}

Solver::~Solver()
{
}

void Solver::addBreakcriterion(ArgList* argListForBreakcriteria)
{
  // Empty implementation
}

void Solver::addGoal(ArgList* argListForGoals) {
  // Empty implementation
}

void Solver::analyzeLaw()
{
  // Empty implementation
}

void Solver::applyGoalsToThings(double progress)
{
  // Empty implementation
}

void Solver::followLaw() 
{
  // Empty implementation
}

void Solver::getInitsFromThings()
{
  // Empty implementation
}

void Solver::plot(std::string plotFileName) {
  // Empty implementation
}

void Solver::plot(std::string plotPrefix,int count) {
  // Empty implementation
}

void Solver::record(const std::string& recordFileName,bool clearFlag) {
  // Empty implementation  
}

void Solver::writeBook() {
  // Empty implementation
}
