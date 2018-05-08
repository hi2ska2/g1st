////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Philosophy.h

#ifndef PhilosophyH
#define PhilosophyH

#include "Law.h"

class Philosophy {
 public:
  Philosophy() : _currentLaw(NULL) {}
  
  Law* addLaw(Law* law) {
    _laws.push_back(law);
    _currentLaw = law;
    return _currentLaw;
  }
  Law* getCurrentLaw() { return _currentLaw; }
  Law* getLaw(std::string& name) { 
    for (int ii=0; ii<_laws.size(); ++ii) {
      if (name==_laws[ii]->getName()) {
	return _laws[ii]; 
      }
    }
    return NULL;
  }
  Law* setCurrentLaw(Law* law) { _currentLaw = law; }
  
  void init() { 
    for (int ii=0; ii<_laws.size(); ++ii) delete _laws[ii];
    _laws.clear(); 
  }
  void followLaws() {
    for (int ii=0; ii<_laws.size(); ++ii) ; 
  }
  
 private:
  std::vector<Law*> _laws; // Top-level Laws
  Law* _currentLaw; // Top-level Laws and subLaws
};

#endif
