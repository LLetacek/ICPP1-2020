#pragma once
#ifndef _DATE_H
#define _DATE_H

#ifndef _IOSTREAM
#define _IOSTREAM
#include <iostream>
#endif // !_IOSTREAM

struct Date {
public:
	Date(int day, int month, int year);
	Date();
	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);
	friend std::ostream& operator<<(std::ostream& os, const Date& obj);
	friend std::istream& operator>>(std::istream& is, Date& obj);
private:
	int m_day;
	int m_month;
	int m_year;
};

std::ostream& operator<<(std::ostream& os, const Date& obj);
std::istream& operator>>(std::istream& is, Date& obj);

#endif // !_DATE_H