////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Law.cc

#include "Law.h"

#include <limits>
#include "Stopwatch.h"

extern Stopwatch jacobianTime;
extern Stopwatch solveTime;

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
  double totalError;

  for (int iNewton=0; iNewton<_iteration; ++iNewton) {
    myReport("Newton iteration = " + myIntToString(iNewton));

    totalError = 0.0;

    //////////////
    // _sublaws //
    //////////////

    for (int ii=0; ii<_sublaws.size(); ++ii) {
      double error = _sublaws[ii]->solve(valid,solverArgList);
      if (!valid) return std::numeric_limits<double>::max();
      if (error>totalError) totalError = error;
    }

    ////////////////
    // _equations //
    ////////////////
    
    if (_equations.size()==0) {
      std::cout << "          totalError = " << totalError << "\n";
      if (totalError<1.0) { 
	//myReport("Converged");  
	break; 
      }       
      continue; 
    }
    
    setUnknownIndices();
    //std::cout << "After setUnknownIndices, " << &_unknownIndices << "\n";
    
    Stopwatch stopwatch;
  
    // In this case, NEWTON equations are coupled.
    bool hasNewton(false);
    
    stopwatch.reset();
    stopwatch.start();

    jacobianTime.start();
    
    for (int iEq=0; iEq<_equations.size(); ++iEq) {
      if (_equations[iEq]->getSolveType()==NEWTON) { // NEWTON	
	hasNewton = true;
	EqNewton* eq(static_cast<EqNewton*>(_equations[iEq]));
	//eq->showUnknownIndices();
	//myReport(eq->getName());
	eq->prepare(iNewton); 	
	eq->apply();	
      } else if (_equations[iEq]->getSolveType()==EVAL) { // EVAL
	EqEval* eq(static_cast<EqEval*>(_equations[iEq]));
	myReport(eq->getName());
	eq->evaluate();
      } else if (_equations[iEq]->getSolveType()==EIGEN) { // EIGEN
	EqEigen* eq(static_cast<EqEigen*>(_equations[iEq]));
	eq->getEigenValue();
	//myReportError("Law::solve(iteration)");
      }
    }
    myReport("All equations are applied.");
    //std::cout << "applied it, " << _unknownIndices.size() << "\n";
    
    if (!hasNewton) continue;
    
    //
    //
    //
    
    buildJacobianResidue();

    jacobianTime.lap();

    stopwatch.stop();
    std::cout << "Jacobian build time: " << stopwatch.elapse() << " [sec].\n";
    std::cout << "_residue's size is " << _residue.size() << "\n";
    
    /*
    for (int ii=0; ii<_residue.size(); ++ii) {	
      std::cout << "_residue[" << ii << "] = " << _residue[ii] << ", _solution = " << _solution[ii] << "\n";
    } 
    */
    /*
    if (iNewton==0) {
      for (int ii=0; ii<_residue.size(); ++ii) {	
	std::cout << _residue[ii] << "\n";
      }     
    }
    */
    
    stopwatch.reset();
    stopwatch.start();

    solveTime.start();

    //_jacobian.printMATLAB("jacobian" + myIntToString(iNewton)); 
    //_jacobian.printMATLAB("jacobian" + myIntToString(iNewton),_residue);     
    _jacobian.solve(_residue,_solution,solverArgList);

    solveTime.lap();

    stopwatch.stop();
    std::cout << "Matrix solve time: " << stopwatch.elapse() << " [sec].\n";
    /*
    for (int ii=0; ii<_residue.size(); ++ii) {
      std::cout << "ii = " << ii << ", _residue = " << _residue[ii] << ", _solution = " << _solution[ii] << "\n";
    }
    */
    myReport("Solution is obtained.");

    _jacobian.printMATLAB("jacobian" + myIntToString(iNewton),_residue,_solution);    
    
    double error = update(valid);
    if (!valid) return std::numeric_limits<double>::max();
    if (error>totalError) totalError = error;
      
    /////////////////
    // Newton plot //
    /////////////////
          
    for (int iEq=0; iEq<_equations.size(); ++iEq) {
      Equation* eq(_equations[iEq]);
      eq->newtonPlot(iNewton);
    } 
         
    //std::cout << "          totalError = " << totalError << "\n";
    if (totalError<1.0) { 
      //myReport("Converged");  
      break; 
    }    
  }
  
  if (_ignore) totalError = 0.0;

  return totalError; 
}

double Law::update(bool& valid)
{

}
