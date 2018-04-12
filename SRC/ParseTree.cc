////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// ParseTree.cc

#include "ParseTree.h"

#include "World.h"

ParseTree* parse_tree;
World* theWorld = new World();

void Program::action(ParseTree* caller) {
  myReport("Program starts.");
  
  if (_stmtList) _stmtList->action(this);

  //
  //theHistory->epilogue();

  myReport("Program ends.");
}

void StmtList::action(ParseTree* caller) {  
  if (_stmtList) _stmtList->action(caller);
  if (_stmt)     _stmt->action(caller);
}

void Stmt::action(ParseTree* caller) {
  std::string callerName;
  if (caller) {
    callerName = static_cast<Stmt*>(caller)->getName();
    myReport(_name + " was called by " + callerName + ".");
  } else myReport(_name + " was called.");

  if (_name.compare("thing")==0) {
    std::string thingType = specLookup("type",std::string("atom"));
    std::string thingName = specLookup("name",std::string("atom"));
    Thing* selected = NULL;
    if      (thingType=="atom"   ) selected = theWorld->addThing( new Atom(thingName) );
    else if (thingType=="crystal") ;
    else myReportError(thingType + " is not a known thing type.");
    
    bodyAction();    
  }
}

