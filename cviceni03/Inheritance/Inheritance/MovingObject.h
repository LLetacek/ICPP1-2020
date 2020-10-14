#pragma once
#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"

class MovingObject : public Object {
public:
	MovingObject(int id);
	MovingObject(int id, double x, double y);
	MovingObject(int id, double x, double y, double angle);
	virtual ~MovingObject();
	double	GetAngleOfRotation() const;
	void	SetAngleOfRotation(double angle);
private:
	double m_angleOfRotation; // <0, 2*PI>, 0 – north, PI - south
};

#endif // !_MOVING_OBJECT_H
