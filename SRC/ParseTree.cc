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

  ///////////
  // thing //
  ///////////
  
  if (_name.compare("thing")==0) {
    std::string thingType = specLookup("type",std::string("atom"));
    std::string thingName = specLookup("name",std::string("atom"));
    Thing* selected = NULL;
    if      (thingType=="atom"   ) selected = theWorld->addThing( new Atom(thingName) );
    else if (thingType=="crystal") ;
    else myReportError(thingType + " is not a known thing type.");
    
    bodyAction();    
  }

  /////////////////
  // thing->atom //
  /////////////////

  else if (_name.compare("atom")==0 &&
	   callerName.compare("thing")==0) {
    Atom* atom = static_cast<Atom*>(theWorld->getCurrentThing());

    atom->set((ArgList*)_spec);
  }

  ////////////////////
  // thing->crystal //
  ////////////////////

  else if (_name.compare("crystal")==0 &&
	   callerName.compare("thing")==0) {
    Crystal* crystal = static_cast<Crystal*>(theWorld->getCurrentThing());

    crystal->set((ArgList*)_spec);

    bodyAction();
  }
  else if (_name.compare("latticevector")==0 &&
	   callerName.compare("crystal")==0) {
    Crystal* crystal = static_cast<Crystal*>(theWorld->getCurrentThing());

    crystal->setLatticeVector((ArgList*)_spec);
  }
  else if (_name.compare("latticebasis")==0 &&
	   callerName.compare("crystal")==0) {
    Crystal* crystal = static_cast<Crystal*>(theWorld->getCurrentThing());

    crystal->setLatticeBasis((ArgList*)_spec);
  }

  /////////
  // law //
  /////////

  else if (_name.compare("law")==0) {
  }

  ///////////
  // solve //
  ///////////

  else if (_name.compare("solve")==0) {
  }  

  ///////////
  // ERROR //
  ///////////  

  else {
    std::string message = 
      _name + std::string(" is not a valid Stmt name.");
    myReportError(message);
  }   
}

