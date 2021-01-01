#include <iostream>
#include "KeyValuePair.h"
#include "Functions.h"

KeyValuePair::KeyValuePair(std::string key, Value* value)
	: m_key(key) {
	if (!value)
		throw std::invalid_argument("Nelze vlozit prazdnou hodnotu");
	m_value = value;
}

std::string KeyValuePair::getKey() const {
	return m_key;
}

bool KeyValuePair::equalityOfKeys(const std::string key) const {
	return (m_key.compare(key)==0);
}

Value* KeyValuePair::getValue() const {
	return m_value;
}

std::string KeyValuePair::serialize() const {
	std::string serializer = '"' + escape(m_key) + "\": ";
	serializer += m_value->serialize();
	return serializer;
}
