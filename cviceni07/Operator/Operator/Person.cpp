#include "Person.h"

Person::Person(std::string name, std::string lastName, Address residence, Date birthDay)
	: m_name(name),
	m_lastName(lastName),
	m_residence(residence),
	m_birthDay(birthDay) {}

Person::Person()
	: Person("", "", Address(), Date()) {}

std::string Person::GetName() const {
	return m_name;
}

std::string Person::GetLastName() const {
	return m_lastName;
}

Address Person::GetResidence() const {
	return m_residence;
}

Date Person::GetBirthDay() const {
	return m_birthDay;
}

void Person::SetName(std::string name) {
	m_name = name;
}

void Person::SetLastName(std::string lastName) {
	m_lastName = lastName;
}

void Person::SetResidence(Address residence) {
	m_residence = residence;
}

void Person::SetBirthDay(Date birthDay) {
	m_birthDay = birthDay;
}

std::ostream& operator<<(std::ostream& os, const Person& obj) {
	os << obj.m_name
		<< ' ' << obj.m_lastName
		<< ' ' << obj.m_birthDay
		<< ' ' << obj.m_residence;

	return os;
}

std::istream& operator>>(std::istream& is, Person& obj) {
	is >> obj.m_name >> obj.m_lastName
		>> obj.m_birthDay
		>> obj.m_residence;

	return is;
}
