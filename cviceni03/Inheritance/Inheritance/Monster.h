#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H

#include "MovingObject.h"

class Monster : public MovingObject {
public:
	Monster(int id);
	Monster(int id, double x, double y);
	Monster(int id, double x, double y, int hp);
	Monster(int id, double x, double y, int hp, int maxHp);
	~Monster();
	int		GetHp() const;
	int		GetMaxHp() const;
	void	SetHp(int hp);
	void	SetMaxHp(int maxHp);
private:
	int m_hp;
	int m_maxHp;
};

#endif // !_MONSTER_H
