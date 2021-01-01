#include "NumberValue.h"

NumberValue::NumberValue(double value)
	: m_value(value) {
}

double NumberValue::get() const {
	return m_value;
}

std::string NumberValue::serialize() const {
	return std::to_string(m_value);
}
