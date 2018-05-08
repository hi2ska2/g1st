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
#include "Philosophy.h"
#include "History.h"
#include "Solver.h"

ParseTree* parse_tree;
World* theWorld = new World();
Philosophy* thePhilosophy = new Philosophy();
History* theHistory = new History();
Solver* theSolver = NULL;

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
    else if (thingType=="crystal") { myReportError("thing"); }
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
    std::string lawName = specLookup("name",std::string("law"    ));
    int iteration       = specLookup("iteration",12);
    bool ignore = specDoesExist("ignore"); 
    Law* cLaw = thePhilosophy->getCurrentLaw(); 
    Law* selected = NULL;
    if (cLaw) selected = cLaw->addSubLaw      ( new Law(lawName,iteration,ignore) );
    else      selected = thePhilosophy->addLaw( new Law(lawName,iteration,ignore) );
    thePhilosophy->setCurrentLaw(selected);
    bodyAction();
    selected->referTo();
    thePhilosophy->setCurrentLaw(cLaw);    
  }

  ///////////////////
  // law->equation //
  ///////////////////

  else if (_name.compare("equation")==0 &&
	   callerName.compare("law")==0) {
    std::string eqType = specLookup("type",std::string("equation"));
    std::string thingName = specLookup("thing",std::string("thing"));
    Thing& selThing(*(theWorld->getThing(thingName)));
    Law* cLaw = thePhilosophy->getCurrentLaw(); 
    Equation* selEq = NULL; 
    if (eqType.compare("allelectron")==0) {
      selEq = cLaw->addEquation( new EqAllElectron(selThing) );
    }    
  }  

  ///////////
  // solve //
  ///////////

  else if (_name.compare("solve")==0) {
    // spec
    std::string law = specLookup("law",std::string("law"));
    Law* selLaw = thePhilosophy->getLaw(law);    
    theSolver = new Solver(selLaw,theWorld,theHistory,(ArgList*)_spec);
     
    bodyAction();
    
    theSolver->followLaw();
    
    theSolver->clear();
    
    delete theSolver;
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

