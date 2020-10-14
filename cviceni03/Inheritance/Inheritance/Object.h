#pragma once
#ifndef _OBJECT_H
#define _OBJECT_H

class Object {
public:
	Object(int id);
	Object(int id, double x, double y);
	virtual ~Object();
	int		GetId() const;
	double	GetX() const;
	double	GetY() const;
	void	SetX(double x);
	void	SetY(double y);
private:
	int		m_id;
	double	m_x;
	double	m_y;
};

#endif // !_OBJECT_H
