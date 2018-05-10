/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Place.h

#ifndef PlaceH
#define PlaceH

#include "Id.h"
#include "NodeId.h"

class Place {  
 public:
 Place(const ThingId& thingId,const VertexId& vertexId,
       const VariableId& variableId,const int inner=0) 
   : _thingId(thingId), _nodeId(vertexId), _variableId(variableId), _inner(inner) { }
 Place(const ThingId& thingId,const EdgeId& edgeId,
       const VariableId& variableId,const int inner=0) 
   : _thingId(thingId), _nodeId(edgeId), _variableId(variableId), _inner(inner) { }
 Place(const ThingId& thingId,const FaceId& faceId,
       const VariableId& variableId,const int inner=0) 
   : _thingId(thingId), _nodeId(faceId), _variableId(variableId), _inner(inner) { }
 Place(const ThingId& thingId,const ShapeId& shapeId,
       const VariableId& variableId,const int inner=0) 
   : _thingId(thingId), _nodeId(shapeId), _variableId(variableId), _inner(inner) { }

  const int& getInner() const { return _inner; }
  const NodeId& getNodeId() const { return _nodeId; }
  const ThingId& getThingId() const { return _thingId; }
  const VariableId& getVariableId() const { return _variableId; }
  void show() const { 
    std::cout << "Place::show()\n";
    std::cout << "   _thingId.getId(): " << _thingId.getId() << "\n"; 
    //std::cout << "   _nodeId.getType(): " << _nodeId.getType() << "\n";
    //std::cout << "   _nodeId.getRegionId().getId(): " << _nodeId.getRegionId().getId() << "\n";
    //std::cout << "   _nodeId.getId(): " << _nodeId.getId() << "\n";
    std::cout << "   _variableId.getId(): " << _variableId.getId() << "\n";
    std::cout << "   _inner: " << _inner << "\n";
  }

 private:
  const ThingId& _thingId;
  const NodeId _nodeId;
  const VariableId& _variableId;
  const int _inner;
};
 
inline bool operator==(const Place& lhs,const Place& rhs) {
  if (lhs.getThingId()==rhs.getThingId())
    if (lhs.getNodeId()==rhs.getNodeId())
      if (lhs.getVariableId()==rhs.getVariableId())
	return (lhs.getInner()==rhs.getInner());
      else false; 
    else false; 
  else false; 
}
inline bool operator< (const Place& lhs,const Place& rhs) {     
  if (lhs.getThingId()==rhs.getThingId())
    if (lhs.getNodeId()==rhs.getNodeId())
      if (lhs.getVariableId()==rhs.getVariableId())
	return (lhs.getInner()<rhs.getInner());
      else return (lhs.getVariableId()<rhs.getVariableId()); 
    else return (lhs.getNodeId()<rhs.getNodeId()); 
  else return (lhs.getThingId()<rhs.getThingId()); 
}

#endif
