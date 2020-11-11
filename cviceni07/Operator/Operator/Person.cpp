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
	os << obj.GetName()
		<< ' ' << obj.GetLastName()
		<< ' ' << obj.GetBirthDay()
		<< ' ' << obj.GetResidence();

	return os;
}

std::istream& operator>>(std::istream& is, Person& obj) {
	std::string name;
	std::string lastName;
	Address residence{ "","",0 };
	Date birthDay{ 0,0,0 };

	is >> name >> lastName
		>> birthDay
		>> residence;

	obj.SetName(name);
	obj.SetLastName(lastName);
	obj.SetResidence(residence);
	obj.SetBirthDay(birthDay);

	return is;
}
