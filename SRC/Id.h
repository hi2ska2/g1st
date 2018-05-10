/////////////////////////////////////////////////
// G-1st                                       //
//                                             //
// Copyright 2018 Sung-Min Hong                //
//                                             //
// Please see LICENSE for license information. //
/////////////////////////////////////////////////

// Id.h

#ifndef IdH
#define IdH

#include <iostream>

#include "utilities.h"

namespace IdType {
  enum Type { NOTHING,
	      THING,
	      REGION,
	      VERTEX, EDGE, FACE, SHAPE,
	      VARIABLE };
};

class Id {
 public:
 Id(IdType::Type idType, int id=-1) : _idType(idType), _id(id) { }
  virtual bool isValid() { return (_idType>IdType::NOTHING) && (_id!=-1); }
  int getId()       { return _id; }
  const int getId() const { return _id; }
  void setId(int id) { _id = id; }
  void show() const { std::cout << _id << "\n"; }
  void show()       { std::cout << _id << "\n"; }
 private:
  IdType::Type _idType;
  int _id;
};

class ThingId : public Id {
 public: 
 ThingId(int id=-1) : Id(IdType::THING,id) { } 
};

class RegionId : public Id { 
 public: 
 RegionId(int id=-1) : Id(IdType::REGION,id) { } 
};
inline bool operator==(const RegionId& lhs,const RegionId& rhs) { return (lhs.getId()==rhs.getId());}
inline bool operator< (const RegionId& lhs,const RegionId& rhs) { return (lhs.getId()< rhs.getId());}

class VertexId : public Id {
 public: 
 VertexId(int id=-1) : Id(IdType::VERTEX,id) { }
};

class EdgeId : public Id {
 public: 
 EdgeId(int id=-1) : Id(IdType::EDGE,id) { }
};

class FaceId : public Id {
 public: 
 FaceId(int id=-1) : Id(IdType::FACE,id) { }
};

class ShapeId : public Id {
 public: 
 ShapeId(int id=-1) : Id(IdType::SHAPE,id) { }
};

#endif
