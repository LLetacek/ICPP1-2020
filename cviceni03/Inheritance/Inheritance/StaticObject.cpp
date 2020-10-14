#include "StaticObject.h"

StaticObject::StaticObject(int id, TypeOfObsticle type) :	Object(id),
															m_obsticleType(type) {}

StaticObject::StaticObject(int id, double x, double y, TypeOfObsticle type) 
	:	Object(id, x, y),
		m_obsticleType(type) {}


StaticObject::~StaticObject() {}

TypeOfObsticle StaticObject::GetObsticleType() const {
	return m_obsticleType;
}
