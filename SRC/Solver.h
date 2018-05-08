////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Solver.h

#ifndef SolverH
#define SolverH

#include <map>

#include "ParseTree.h"
//#include "Law.h"
//#include "World.h"
//#include "History.h"

class Law;
class World;
class History;

class Solver {
 public:
  Solver(Law* law,World* world,History* history,ArgList* argList);
  ~Solver();

  void addBreakcriterion(ArgList* argListForBreakcriteria);
  void addGoal(ArgList* argListForGoals);
  void clear() { 
    delete _argList;
    //_iteration = 0;
  }
  void followLaw();
  void plot(std::string plotFileName);
  void plot(std::string plotPrefix,int count);
  void record(const std::string& recordFileName,bool clearFlag=false); 
  //void setIteration(int iteration) { _iteration = iteration; }

 protected:
  Law* _law;
  World* _world;
  History* _history;
  ArgList* _argList;
  //int _iteration;
  bool _doPlot;
  bool _doZero;
  bool _plotCount;
  double _initialStep;
  double _minStep;
  double _maxStep;
  double _increment;
  double _decrement;
  std::map<std::pair<std::string,std::string>,double> _inits; // Currently, only double
  std::map<std::pair<std::string,std::string>,double> _goals; // Currently, only double
  //std::string _plotFileName;
  std::string _plotPrefix;
  std::string _recordFileName;
  std::string _bookName;
  std::string _matrixSolverName;
  std::vector<ArgList*> _breakcriteria;

  void analyzeLaw();
  void applyGoalsToThings(double progress);
  void getInitsFromThings(); // Implemented on January 5, 2017
  void writeBook();
};

#endif
