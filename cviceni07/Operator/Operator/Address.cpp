#include "Address.h"
#include <string>

Address::Address(std::string street, std::string town, int pin)
	: m_street(street),
	m_town(town),
	m_pin(pin) {}

Address::Address()
	: Address("", "", 0) {}

std::string Address::GetStreet() const {
	return m_street;
}

std::string Address::GetTown() const {
	return m_town;
}

int Address::GetPin() const {
	return m_pin;
}

void Address::SetStreet(std::string street) {
	m_street = street;
}

void Address::SetTown(std::string town) {
	m_town = town;
}

void Address::SetPin(int pin) {
	m_pin = pin;
}

std::ostream& operator<<(std::ostream& os, const Address& obj) {
	os << obj.m_street;
	os << ';';
	os << obj.m_town;
	os << ';';
	os << obj.m_pin;

	return os;
}

std::istream& operator>>(std::istream& is, Address& obj) {
	char skip;

	skip = is.get();
	std::getline(is, obj.m_street, ';');
	std::getline(is, obj.m_town, ';');
	is >> obj.m_pin;

	return is;
}
