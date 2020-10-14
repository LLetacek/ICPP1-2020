#pragma once
#ifndef _STATIC_OBJECT_H
#define _STATIC_OBJECT_H

#include "Object.h"
#include "TypeOfObstacle.h"

class StaticObject : public Object {
public:
	StaticObject(int id, TypeOfObsticle type);
	StaticObject(int id, double x, double y, TypeOfObsticle type);
	~StaticObject();
	TypeOfObsticle GetObsticleType() const;
private:
	TypeOfObsticle m_obsticleType;
};

#endif // !_STATIC_OBJECT_H
