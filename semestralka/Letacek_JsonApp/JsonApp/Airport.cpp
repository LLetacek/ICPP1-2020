#include <iostream>
#include "Airplane.h"

#include "UtilityFunctions.h"

Airport::Airport() : m_icao("null"), m_place("null") {
}

Airport::Airport(std::string icao, std::string place)
	: m_icao(icao), m_place(place) {
}

Airport::Airport(Value* val) {
	ObjectValue* obj = dynamic_cast<ObjectValue*>(val);
	if (!obj)
		throw std::invalid_argument("Ocekavan objekt!");

	int attributeChecker = 0;
	int size = obj->getSize();
	// 2 (max pocet atributu)
	if (size > 2)
		throw std::invalid_argument("Objekt ocekava 2 atributy!");

	m_icao = valueOfOptionalAttribute<StringValue*,std::string>("icao", attributeChecker, obj, "");
	m_place = valueOfOptionalAttribute<StringValue*, std::string>("poloha", attributeChecker, obj, "");

	// kontrola, zda nebyly v objektu prebitecne keyvalue hodnoty
	// 2 (max pocet atributu)
	if ((2-attributeChecker) != size)
		throw std::invalid_argument("neplatny objekt");
}

void Airport::setIcao(std::string icao) {
	m_icao = icao;
}

void Airport::setPlace(std::string place) {
	m_place = place;
}

std::string Airport::getIcao() {
	return m_icao;
}

std::string Airport::getPlace() {
	return m_place;
}

bool Airport::equalityOfKeys(const std::string key) const {
	return (m_icao.compare(key)==0);
}

std::string Airport::toString() const {
	std::string str = (m_icao.empty()) ? "NULL" : m_icao;
	str += " (";
	str += (m_place.empty()) ? "NULL" : m_place;
	str += ")";
	return str;
}

Value* Airport::getJSON() const {
	ObjectValue* ov = new ObjectValue{};
	if (m_icao.size() != 0)
		ov->append(KeyValuePair{ "icao", new StringValue{m_icao} });
	if (m_place.size() != 0)
		ov->append(KeyValuePair{ "poloha", new StringValue{m_place}});
	return ov;
}
