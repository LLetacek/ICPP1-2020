#include <iomanip> 
#include "Date.h"

Date::Date(int day, int month, int year)
	: m_day(day),
	m_month(month),
	m_year(year) {}

Date::Date()
	: Date(0, 0, 0) {}

int Date::GetDay() const {
	return m_day;
}

int Date::GetMonth() const {
	return m_month;
}

int Date::GetYear() const {
	return m_year;
}

void Date::SetDay(int day) {
	m_day = day;
}

void Date::SetMonth(int month) {
	m_month = month;
}

void Date::SetYear(int year) {
	m_year = year;
}

std::ostream& operator<<(std::ostream& os, const Date& obj) {
	os << std::setw(2) << std::setfill('0') << obj.m_day
		<< '.'
		<< std::setw(2) << std::setfill('0') << obj.m_month
		<< '.'
		<< obj.m_year;

	return os;
}

std::istream& operator>>(std::istream& is, Date& obj) {
	char skip;

	is >> obj.m_day >> skip >> obj.m_month >> skip >> obj.m_year;

	return is;
}
