#include "ObjectValue.h"

ObjectValue::ObjectValue() {
}

ObjectValue::~ObjectValue() {
	if (m_array.getSize() == 0)
		return;

	while (m_array.getSize()) {
		delete (m_array.remove()).getValue();
	}
}

void ObjectValue::append(const KeyValuePair& pair) {
	m_array.append(pair);
}

int ObjectValue::getSize() const {
	return m_array.getSize();
}

Value* ObjectValue::getValueByKey(const std::string key) const {
	return (m_array.findByKey(&KeyValuePair::equalityOfKeys, key)).getValue();
}

std::string ObjectValue::serialize() const {
	std::string serializer = "{ ";
	serializer += m_array.serializeAll(&KeyValuePair::serialize);
	return serializer + " }";
}
