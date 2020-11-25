#pragma once
#ifndef _PERSON_H
#define _PERSON_H
#include "Date.h"
#include "Address.h"

struct Person {
public:
	Person(std::string name, std::string lastName, Address residence, Date birthDay);
	Person();
	std::string GetName() const;
	std::string GetLastName() const;
	Address GetResidence() const;
	Date GetBirthDay() const;
	void SetName(std::string name);
	void SetLastName(std::string lastName);
	void SetResidence(Address residence);
	void SetBirthDay(Date birthDay);
	friend std::ostream& operator<<(std::ostream& os, const Person& obj);
	friend std::istream& operator>>(std::istream& is, Person& obj);
private:
	std::string m_name;
	std::string m_lastName;
	Address m_residence;
	Date m_birthDay;
};

std::ostream& operator<<(std::ostream& os, const Person& obj);
std::istream& operator>>(std::istream& is, Person& obj);

#endif // !_PERSON_H