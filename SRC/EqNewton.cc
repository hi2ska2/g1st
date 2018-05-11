////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// EqNewton.cc

#include "EqNewton.h"

EqNewton::EqNewton(std::string name,std::string variableName,Thing& thing,int nNode) 
  : Equation(name,thing), 
    _variableName(variableName),
    _variable_old1Name(variableName+"_old1"),
    _variable_old2Name(variableName+"_old2")
{ 
  myReport("EqNewton::EqNewton(name,variableName,thing,nNode)");
  std::cout << "name = " << name << "\n";
  std::cout << "variableName = " << variableName << "\n";
  std::cout << "nNode = " << nNode << "\n";
  Field* field(_thing.getField()); 
  if (nNode>0) {
    field->getArrayVariable(_variableName     ,_variableId     ,nNode);
    field->getArrayVariable(_variable_old1Name,_variable_old1Id,nNode);
    field->getArrayVariable(_variable_old2Name,_variable_old2Id,nNode);
  }
  /*
  else if (field->hasMesh()) {
    field->getVertexNodeVariable(_variableName     ,_variableId     );   
    field->getVertexNodeVariable(_variable_old1Name,_variable_old1Id);   
    field->getVertexNodeVariable(_variable_old2Name,_variable_old2Id);   
  }
  */
  else myReportError("EqNewton::EqNewton(name,variableName,thing,nNode)");
}

void EqNewton::buildJacobianResidue(RealTriplet& jacobian,std::vector<double>& residue,const std::map<Place,int>& unknownIndices)
{

}

void EqNewton::collectUnknownIndices(std::map<Place,int>& unknownIndices)
{     

}

void EqNewton::collectUnknownIndicesSemiconductor(std::map<Place,int>& unknownIndices)
{

}

void EqNewton::compareUnknownIndices(const Place& place)
{

}

void EqNewton::copy_old() 
{

}

int EqNewton::getRow(const Place& place)
{

}

void EqNewton::prepare(int iNewton) {

}

void EqNewton::restore() 
{

}

void EqNewton::setUnknownIndices(std::map<Place,int>& unknownIndices)
{

}

void EqNewton::showUnknownIndices()
{     

}

void EqNewton::showUnknownIndices(std::map<Place,int>& unknownIndices)
{     

}

// NEW
double EqNewton::update(std::vector<double>& solution,
			std::map<Place,int>& unknownIndices,
			double xref,
			bool& valid) 
{
  // Empty implementation
}

// NEW
double EqNewton::update(std::vector<double>& solution,
			std::map<Place,int>& unknownIndices,
			std::vector<double>& xref,
			bool& valid) 
{   
  // Empty implementation
}

double EqNewton::updateSemiconductor(std::vector<double>& solution,
				     std::map<Place,int>& unknownIndices,
				     double xref,
				     bool& valid) 
{   
  // Empty implementation
}
