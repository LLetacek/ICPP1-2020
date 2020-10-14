#include "Object.h"

#define DEFAULT_POSITION_X 0
#define DEFAULT_POSITION_Y 0

Object::Object(int id) 
	: Object(id, DEFAULT_POSITION_X, DEFAULT_POSITION_Y) {}

Object::Object(int id, double x, double y) 
	:	m_id((id!=-1)?id:throw "Object: id -1 nelze pouzit"),
		m_x(x), 
		m_y(y) {}

Object::~Object() {}

int Object::GetId() const {
	return m_id;
}

double Object::GetX() const {
	return m_x;
}

double Object::GetY() const {
	return m_y;
}

void Object::SetX(double x) {
	m_x = x;
}

void Object::SetY(double y) {
	m_y = y;
}