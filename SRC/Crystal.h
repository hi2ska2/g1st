/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Crystal.h

#ifndef CrystalH
#define CrystalH

#include "Thing.h"

class Crystal : public Thing {
 public:
  Crystal(const std::string& name);
  virtual void set(ArgList* argList);
  void setLatticeBasis(ArgList* argList);  
  void setLatticeVector(ArgList* argList);  

 private:
  double _latticeConstant;
  // _latticeVector
  // _latticeBasis
  std::vector<Atom*> _latticeBasis;
};

#endif
