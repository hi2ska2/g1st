/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Thing.h

#ifndef ThingH
#define ThingH

#include "ParseTree.h"
#include "Field.h"
//#include "Id.h"

#include "utilities.h"

namespace ThingType {
  enum Type { CRYSTAL, ATOM };
};

class Thing {
 public:
  Thing(const std::string& name,ThingType::Type type);

  bool checkType(ThingType::Type type);
  std::string getName();
  
  virtual Field* getField() { return _field; } 
  //virtual bool isInitialized() = 0;
  
 protected:
  std::string _name;
  ThingType::Type _type;
  Field* _field;
  //Id _thingId;
};

#include "Atom.h"
#include "Crystal.h"
//#include "Lumped.h"

#endif
