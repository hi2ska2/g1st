/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Atom.h

#ifndef AtomH
#define AtomH

#include "Thing.h"

namespace AtomType {
  enum Type { ALUMINIUM, SILICON };
};

class Atom : public Thing {
 public:
  Atom(const std::string& name);
  virtual void set(ArgList* argList);

 private:
  AtomType::Type _type;
};

#endif
