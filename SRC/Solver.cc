////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Solver.cc

#include "Solver.h"
#include "Law.h"
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
  // Determine what to do
  analyzeLaw();

  // Remember the initial status

  // Actually solve 
  myReport("===  Solution procedure for Law " + _law->getName() + " ===");

  getInitsFromThings();

  double step = _initialStep;
  double progress = 0.0;
  int count = 0;
  
  // For solveEq  
  if (_doZero) {
    myReport("===============");
    myReport("Progress = " + myDoubleToString(progress));
    myReport("===============");  
    applyGoalsToThings(progress);
    
    bool valid = true;
    double totalError = _law->solve(valid,_argList);
    
    if (valid && totalError<1.0) {
      _law->postprocess();

      // After calling the solve routine  
      plot(_plotPrefix,count);
      count++;
      //record(_recordFileName);
      writeBook();
    } else {
      myReportError("Solver::folllowLaw(), dozero is a failure.");
    }

    // No break for _doZero
  }
  
  while (progress<1.0) {
    // Before calling the solve routine
    progress += step;
    if ( progress > (1.0-1e-9) ) progress = 1.0;    
    myReport("===============");
    myReport("Progress = " + myDoubleToString(progress));
    myReport("===============");  
    applyGoalsToThings(progress);
    
    bool valid = true;
    double totalError = _law->solve(valid,_argList);
    //std::cout << "totalError = " << totalError << "\n";
    if (valid && totalError<1.0) {
      _law->postprocess();

      // After calling the solve routine 
      plot(_plotPrefix,count);
      count++;
      //record(_recordFileName);
      writeBook();

      step *= _increment;
      if (step>_maxStep) step = _maxStep;
    } else {
      myReport("Solver::folllowLaw(), unsuccessful Newton iteration.");
      _law->restore();
      myReportError("Solver::folllowLaw(), unsuccessful Newton iteration.");
      progress -= step;
      step /= _decrement;
      if (step<_minStep) myReportError("Solver::folllowLaw(), too small step.");
    }

    // Break
    /*
    bool mustBreak = (_breakcriteria.size()>0) ? true : false;
    for (int ii=0; ii<_breakcriteria.size(); ++ii) {
      Book* book = _history->getBook(_bookName);
      if ( !(book->checkCriterion(_breakcriteria[ii])) ) {
	std::cout << "BREAK: The condition #" << ii << " is NOT satisfied.\n";
	mustBreak = false; 
      } else {
	std::cout << "BREAK: The condition #" << ii << " is satisfied.\n";
      }
    }
   
    if (mustBreak) {
      myReport("BREAK: All conditions are satisfied.");
      break;
    }
    */
  }
  
  myReport("===  End of solution procedure ===");
  myReport(" ");  
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
