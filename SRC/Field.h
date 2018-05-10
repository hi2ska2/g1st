/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Field.h

#ifndef FieldH
#define FieldH

#include "ParseTree.h"
#include "Variable.h"
#include "Place.h"
#include <map>

//typedef std::pair<VariableId,Variable*>                ArrayVariablePair;
//typedef std::map<VariableId,Variable*>::iterator       ArrayVariableIter;
//typedef std::map<VariableId,Variable*>::const_iterator ArrayVariableIterC;

class Field {
 public:
  Field();

  void addPlotVariable(const std::string& variableName,double coefficientForPlot);

  bool findVariable(const std::string& variableName);
  //VertexNodeVariable& getVertexNodeVariable(const std::string& variableName,int n=1);
  //EdgeNodeVariable&   getEdgeNodeVariable  (const std::string& variableName,int n=1);
  //FaceNodeVariable&   getFaceNodeVariable  (const std::string& variableName,int n=1);
  //VertexNodeVariable& getVertexNodeVariable(const std::string& variableName,VariableId& variableId,int n=1);
  //EdgeNodeVariable&   getEdgeNodeVariable  (const std::string& variableName,VariableId& variableId,int n=1);
  //FaceNodeVariable&   getFaceNodeVariable  (const std::string& variableName,VariableId& variableId,int n=1);
  Variable& getArrayVariable(const std::string& variableName,int n=1,int m=1,int l=1);
  Variable& getArrayVariable(const std::string& variableName,VariableId& variableId,int n=1,int m=1,int l=1);
  double getVariableEntry(const std::string& variableName,const int& ii);
  void initialize() {   
    _isInitialized = true; 
  }
  bool isInitialized() { return _isInitialized; }

  int getPlotVariableSize() { return _plotVariables.size(); }
  std::string getPlotVariableName(int ii) const { return _plotVariables[ii];}

 protected:
  bool addVariableName(std::string variableName,VariableId& variableId);

  bool _isInitialized;
  //std::map<VariableId,VertexNodeVariable*> _vertexNodeVariables;
  //std::map<VariableId,EdgeNodeVariable*  > _edgeNodeVariables;
  //std::map<VariableId,FaceNodeVariable*  > _faceNodeVariables;
  //std::map<VariableId,ShapeNodeVariable* > _shapeNodeVariables;
  std::map<VariableId,Variable*          > _arrayVariables;
  std::map<std::string,VariableId> _variableNames; // For every variable

  std::vector<std::string> _plotVariables; // Introduced on 2018. 01. 24.

};

/*
typedef std::pair<std::string,VariableId> VariableNamePair;
typedef std::map<std::string,VariableId>::iterator       VariableNameIter;
typedef std::map<std::string,VariableId>::const_iterator VariableNameIterC;

typedef std::map<RegVar,Variable*>::iterator RegVarIter;
typedef std::map<std::string,int>::iterator StrIntIter;
*/

#endif
