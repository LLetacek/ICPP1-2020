#define _USE_MATH_DEFINES

#include <cmath>
#include "MovingObject.h"

#define DEFAULT_ANGLE 0

MovingObject::MovingObject(int id) 
	:	Object(id), 
		m_angleOfRotation(DEFAULT_ANGLE) {}

MovingObject::MovingObject(int id, double x, double y) 
	: MovingObject(id, x, y, DEFAULT_ANGLE) {}

MovingObject::MovingObject(int id, double x, double y, double angle) 
	:	Object(id, x, y),
		m_angleOfRotation(std::fmod(angle, 2*M_PI)) {}

MovingObject::~MovingObject() {}

double MovingObject::GetAngleOfRotation() const {
	return m_angleOfRotation;
}
void MovingObject::SetAngleOfRotation(double angle) {
	m_angleOfRotation = std::fmod(angle, 2 * M_PI);
}
