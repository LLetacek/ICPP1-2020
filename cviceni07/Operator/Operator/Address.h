#pragma once
#ifndef _ADDRESS_H
#define _ADDRESS_H

#ifndef _IOSTREAM
#define _IOSTREAM
#include <iostream>
#endif // !_IOSTREAM

struct Address {
public:
	Address(std::string street, std::string town, int pin);
	Address();
	std::string GetStreet() const;
	std::string GetTown() const;
	int GetPin() const;
	void SetStreet(std::string street);
	void SetTown(std::string town);
	void SetPin(int pin);
private:
	std::string m_street;
	std::string m_town;
	int m_pin;
};

std::ostream& operator<<(std::ostream& os, const Address& obj);
std::istream& operator>>(std::istream& is, Address& obj);

#endif // !_ADDRESS_H