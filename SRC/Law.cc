////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Law.cc

#include "Law.h"

void Law::analyze(int indentation) 
{
  // Empty implementation
}

void Law::buildJacobianResidue() 
{

}

void Law::plot(const std::string& fileName)
{

}

void Law::plot(const std::string& filePrefix,bool appendCount,int count)
{

}

void Law::postprocess()
{

}

void Law::record(std::string fileName)
{

}

void Law::referTo()
{
  // Empty implementation
}

void Law::restore()
{

}

void Law::setUnknownIndices()
{ 

}

// _sublaws
// _equations
//double Law::solve(bool& valid,const std::string& matrixSolverName) // OBSOLUTE
double Law::solve(bool& valid,ArgList* solverArgList)
{ 
  myReportError("Law::solve(valid,solverArgList)");
}

double Law::update(bool& valid)
{

}
