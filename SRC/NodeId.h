/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// NodeId.h

// A NodeId is NOT an Id.

#ifndef NodeIdH
#define NodeIdH

#include "Id.h"
#include "utilities.h"

#include <map>

class NodeId {
 public:
  NodeId(const Id& id) { _ids.clear(); _ids.push_back(id); }
  int getSize() const { return _ids.size(); }
  int getSize()       { return _ids.size(); }
 private:
  std::vector<Id> _ids;
};

inline bool operator==(const NodeId& lhs,const NodeId& rhs) { 
  if (lhs.getSize()==rhs.getSize())
    ;
    /*
    if (lhs.getRegionId()==rhs.getRegionId())
      return (lhs.getId()==rhs.getId()); 
    else return false;
    */
  else return false;   
}
inline bool operator< (const NodeId& lhs,const NodeId& rhs) { 
  if (lhs.getSize()==rhs.getSize())
    ;
    /*
    if (lhs.getRegionId()==rhs.getRegionId())
      return (lhs.getId()< rhs.getId());
    else return (lhs.getRegionId()<rhs.getRegionId());
    */
  else return (lhs.getSize()<rhs.getSize());
}

#endif
