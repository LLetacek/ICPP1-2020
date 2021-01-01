#include "StringValue.h"
#include "Functions.h"

StringValue::StringValue(std::string value)
	: m_value(value) {
}

std::string StringValue::get() const {
	return m_value;
}

std::string StringValue::serialize() const {
	std::string serializer = '"' + escape(m_value) + '"';
	return serializer;
}
