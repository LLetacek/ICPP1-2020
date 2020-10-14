#include "Monster.h"

#define DEFAULT_HP 1000

Monster::Monster(int id) :	MovingObject(id), 
							m_hp(DEFAULT_HP),
							m_maxHp(DEFAULT_HP) {}

Monster::Monster(int id, double x, double y) 
	: Monster(id, x, y, DEFAULT_HP) {}

Monster::Monster(int id, double x, double y, int hp) 
	: Monster(id, x, y, hp, hp) {}

Monster::Monster(int id, double x, double y, int hp, int maxHp) 
	:	MovingObject(id, x, y),
		m_hp(hp),
		m_maxHp(maxHp) {}

Monster::~Monster() {}

int Monster::GetHp() const {
	return m_hp;
}

int Monster::GetMaxHp() const {
	return m_maxHp;
} 

void Monster::SetHp(int hp) {
	m_hp = hp;
}

void Monster::SetMaxHp(int maxHp) {
	m_maxHp = maxHp;
}
