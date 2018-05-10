////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// VariableId.h

#ifndef VariableIdH
#define VariableIdH

#include "Id.h"

class VariableId : public Id {
 public:
 VariableId(int id=-1) : Id(IdType::VARIABLE,id) { }
  
  friend bool operator==(const VariableId& lhs,const VariableId& rhs) { return lhs.getId()==rhs.getId(); }
  friend bool operator< (const VariableId& lhs,const VariableId& rhs) { return lhs.getId()< rhs.getId(); }
};

#endif
