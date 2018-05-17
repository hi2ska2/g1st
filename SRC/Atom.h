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

  int get_nMeshPoint();
  int get_nProton();

 private:  
  AtomType::Type _type;
  int _nProton;
  int _nMeshPoint;

  // Mesh, which is a vector
  std::vector<double> _mesh; // Actually, it is not a mesh object.
};

#endif
