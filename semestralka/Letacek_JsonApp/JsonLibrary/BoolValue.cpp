#include "BoolValue.h"

BoolValue::BoolValue(bool value)
	: m_value(value) {
}

bool BoolValue::get() const {
	return m_value;
}

std::string BoolValue::serialize() const {
	return (m_value) ? "true" : "false";
}
