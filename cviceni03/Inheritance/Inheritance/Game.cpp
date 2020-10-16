#define _USE_MATH_DEFINES

#include <cmath>
#include "Game.h"
#include "StaticObject.h"

Game::Game() : Game(8) {}

Game::Game(int size) :	m_size((size<=0)?8:size), 
						m_counter(0), 
						m_objects(new Object*[m_size]) {}

Game::~Game() {
	for (int i = 0; i < m_counter; i++) {
		delete m_objects[i];
	}
	delete[] m_objects;
}

void Game::insertObject(Object* o) {
	if (o == nullptr)
		return;

	if (m_counter >= m_size) {
		m_size *= 2;
		Object** objects = new Object * [m_size];
		for (int i = 0; i < m_counter; i++) {
			objects[i] = m_objects[i];
		}

		Object** tmp = m_objects;
		m_objects = objects;
		delete[] tmp;
	}

	m_objects[m_counter] = o;
	++m_counter;
}

int* Game::findIdStaticObject(double xMin, double yMin, double xMax, double yMax) const {
	int idCounter = 0;
	if (m_counter == 0)
		return nullptr;

	int* idArr = new int[m_counter+1];
	for (int i = 0; i < m_counter; i++) {
		if (dynamic_cast<StaticObject*>(m_objects[i]) &&
			m_objects[i]->GetX() >= std::fmin(xMin,xMax) && 
			m_objects[i]->GetY() >= std::fmin(yMin, yMax) &&
			m_objects[i]->GetX() <= std::fmax(xMin, xMax) && 
			m_objects[i]->GetY() <= std::fmax(yMin, yMax))
		{
			idArr[idCounter++] = m_objects[i]->GetId();
		}
	}

	idArr[idCounter] = -1;

	return idArr;
}

MovingObject** Game::findMovingObjectInArea(double x, double y, double r) const {
	int idCounter = 0;
	if (m_counter == 0)
		return nullptr;

	MovingObject** obArr = new MovingObject*[m_counter+1];
	for (int i = 0; i < m_counter; i++) {
		if (dynamic_cast<MovingObject*>(m_objects[i]) &&
			pow(m_objects[i]->GetX() - x,2) + pow(m_objects[i]->GetY() - y,2) <= pow(r,2))
		{
			obArr[idCounter++] = (MovingObject*)m_objects[i];
		}
	}

	obArr[idCounter] = nullptr;

	return obArr;
}

MovingObject** Game::findMovingObjectInArea(double x, double y, double r, double uMin, double uMax) const {
	int idCounter = 0;
	if (m_counter == 0)
		return nullptr;

	uMin = std::fmod(uMin, 2 * M_PI);
	uMax = std::fmod(uMax, 2 * M_PI);

	MovingObject** obArr = new MovingObject * [m_counter+1];
	for (int i = 0; i < m_counter; i++) {
		if (dynamic_cast<MovingObject*>(m_objects[i]) &&
			pow(m_objects[i]->GetX() - x, 2) + pow(m_objects[i]->GetY() - y, 2) <= pow(r,2) &&
			((MovingObject*)m_objects[i])->GetAngleOfRotation() >= std::fmin(uMin, uMax) &&
			((MovingObject*)m_objects[i])->GetAngleOfRotation() <= std::fmax(uMin, uMax))
		{
			obArr[idCounter++] = (MovingObject*)m_objects[i];
		}
	}

	obArr[idCounter] = nullptr;

	return obArr;
}
