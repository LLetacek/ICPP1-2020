#include <iostream>
#include "ArrayValue.h"

ArrayValue::ArrayValue() {
}

ArrayValue::~ArrayValue() {
	if (m_array.getSize() == 0)
		return;

	while (m_array.getSize()) {
		delete m_array.remove();
	}
}

void ArrayValue::append(Value* element) {
	if (!element)
		throw std::invalid_argument("Value nesmi byt nullptr!");
	m_array.append(element);
}

int ArrayValue::getSize() const {
	return m_array.getSize();
}

const Value* ArrayValue::getElementAt(int index) const {
	return m_array.getElementAt(index);
}

Value* ArrayValue::getElementAt(int index) {
	return m_array.getElementAt(index);
}

std::string ArrayValue::serialize() const {
	std::string serializer = "[ ";
	serializer += m_array.serializeAll(&Value::serialize);
	return serializer + " ]";
}
