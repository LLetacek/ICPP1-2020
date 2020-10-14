#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Object.h"
#include "MovingObject.h"

class Game {
public:
	Game();
	Game(int size);
	~Game();
	void insertObject(Object* o);
	int* findIdStaticObject(double xMin, double yMin, double xMax, double yMax) const;
	MovingObject** findMovingObjectInArea(double x, double y, double r) const;
	MovingObject** findMovingObjectInArea(double x, double y, double r, double uMin, double uMax) const;
private:
	int m_size;
	int m_counter;
	Object** m_objects;
};

#endif // !_GAME_H
