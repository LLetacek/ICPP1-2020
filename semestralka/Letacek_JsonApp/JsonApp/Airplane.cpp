#include <iostream>
#include <sstream>
#include "Airplane.h"

#include "UtilityFunctions.h"

Airplane::Airplane(std::string registration, std::string name, Airport* airport, int maxSpeed, bool airworthy)
	: m_registration(registration),
	  m_name(name),
	  m_airport(airport),
	  m_maxSpeed((maxSpeed<0) ? throw std::invalid_argument("Rychlost nemuze byt zaporna") : maxSpeed),
	  m_airworthy(airworthy) {
}

Airplane::Airplane(Value* val) : m_airport(nullptr) {
	ObjectValue* obj = dynamic_cast<ObjectValue*>(val);
	if (!obj)
		throw std::invalid_argument("Ocekavan objekt!");

	int size = obj->getSize();
	if (size < 4 || size > 6) // TODO misto 5 napis 4
		throw std::invalid_argument("Ocekavan objekt s 4-6 parametry! - nevalidni JSON pro aplikaci");

	int attributeChecker = 0;
	Value* tmp;
	tmp = obj->getValueByKey("imatrikulace");	// povinny udaj (musi byt v JSONu)
	m_registration = valueToVariableNotNull<StringValue*, std::string>(tmp);
	if (m_registration.empty())
		throw std::invalid_argument("Chyba - imatrikulace je prazdna!");

	tmp = obj->getValueByKey("nazev");	// povinny udaj (musi byt v JSONu)
	m_name = valueToVariableNotNull<StringValue*, std::string>(tmp);
	if (m_name.empty())
		throw std::invalid_argument("Chyba - nazev je prazdny!");

	tmp = obj->getValueByKey("letiste"); // povinny udaj (musi byt v JSONu) - hodnota muze byt null
	if (!dynamic_cast<NullValue*>(tmp))
		m_airport = new Airport{ tmp };

	// nepovinny udaj
	m_maxSpeed = (int)valueOfOptionalAttribute<NumberValue*, double>("max rychlost", attributeChecker, obj, 0);
	if(m_maxSpeed<0)
		throw std::invalid_argument("Chyba - max rychlost nemuze byt zaporna!");

	tmp = obj->getValueByKey("letuschopne"); // povinny udaj (musi byt v JSONu)
	m_airworthy = valueToVariableNotNull<BoolValue*, bool>(tmp);

	try {
		tmp = nullptr;
		tmp = obj->getValueByKey("kontroly"); // nepovinny udaj - muze byt prazdne pole nebo null
	}
	catch (...) {
		++attributeChecker;
	}

	if (tmp) {
		ArrayValue* arr = dynamic_cast<ArrayValue*>(tmp);
		if (!(dynamic_cast<NullValue*>(tmp)) && !arr) {
			throw std::invalid_argument("Chyba - ocekavano pole");
		}
		else if (arr) {
			for (int i = 0; i < arr->getSize(); ++i) {
				m_inspection.append(valueToVariable<StringValue*, std::string>(arr->getElementAt(i), ""));
			}
		}
	}

	// 6 (max pocet atributu)
	if ((6-attributeChecker) != size)
		throw std::invalid_argument("neplatny objekt");
}

Airplane::Airplane(const Airplane& plane) : m_airport(nullptr) {
	m_registration = plane.m_registration;
	m_name = plane.m_name;
	if (plane.m_airport) {
		m_airport = new Airport{ plane.m_airport->getIcao(),plane.m_airport->getPlace() };
	}
	m_maxSpeed = plane.m_maxSpeed;
	m_airworthy = plane.m_airworthy;

	if (plane.m_inspection.getSize()) {
		for (int i = 0; i < plane.m_inspection.getSize(); ++i) {
			m_inspection.append(plane.m_inspection.getElementAt(i));
		}
	}
}

Airplane::~Airplane() {
	if (m_airport)
		delete m_airport;
}

void Airplane::setRegistration(std::string registration) {
	m_registration = registration;
}

void Airplane::setName(std::string name) {
	m_name = name;
}

void Airplane::setAirport(Airport* airport) {
	if (m_airport)
		delete m_airport;
	m_airport = airport;
}

void Airplane::removeAirport() {
	if (m_airport)
		delete m_airport;
	m_airport = nullptr;
}

void Airplane::appendInspection(std::string inspection) {
	m_inspection.append(inspection);
}

const std::string Airplane::getInspection(int index) const {
	return m_inspection.getElementAt(index);
}

void Airplane::updateInspection(std::string inspection, int index) {
	std::string& old = m_inspection.getElementAt(index);
	old = inspection;
}

void Airplane::setMaxSpeed(int speed) {
	m_maxSpeed = speed;
}

void Airplane::setAirworthy(bool airworthy) {
	m_airworthy = airworthy;
}

std::string Airplane::getKey() const {
	return m_registration;
}

Airport* Airplane::getAirport() {
	if (m_airport)
		return m_airport;
	throw std::logic_error("Letadlo nema domovske letiste, nebo je nezname!");
}

bool Airplane::equalityOfKeys(const std::string key) const {
	return (m_registration.compare(key)==0);
}

std::string Airplane::toString() const {
	std::stringstream str;
	str << "\nLETADLO :"
		<< "\n\tIMATRIKULACE => " << m_registration
		<< "\n\tNAZEV => " << m_name
		<< "\n\tLETISTE => ";

	if (m_airport)
		str << m_airport->toString();
	else
		str << "NULL";
	
	str << "\n\tKONTROLY => ";
	if (m_inspection.getSize() == 0) {
		str << "NULL";
	}
	else {
		for (int i = 0; i < m_inspection.getSize(); ++i) {
			std::string tmp = m_inspection.getElementAt(i);
			str << ((!tmp.empty()) ? tmp : "NULL");
			str << ((i + 1 != m_inspection.getSize()) ? ", " : "");
		}
	}

	str << "\n\tMAX RYCHLOST => ";
	if (m_maxSpeed == 0)
		str << "NEZNAMA";
	else
		str << m_maxSpeed;

	str << "\n\tLETUSCHOPNE => " << ((m_airworthy) ? "TRUE" : "FALSE");
	str << std::endl;

	return str.str();
}

Value* Airplane::getJSON() const {
	ObjectValue* ov = new ObjectValue{};
	ov->append(KeyValuePair{ "imatrikulace", new StringValue{m_registration} });
	ov->append(KeyValuePair{ "nazev", new StringValue{m_name} });
	ov->append(KeyValuePair{ "letiste", (m_airport != nullptr) ? m_airport->getJSON() : new NullValue{} });
	
	ArrayValue* av = new ArrayValue{};
	for (int i = 0; i < m_inspection.getSize(); ++i) {
		std::string tmp = m_inspection.getElementAt(i);
		if (!tmp.empty())
			av->append(new StringValue{ tmp });
	}
	ov->append(KeyValuePair{ "kontroly", av });

	if (m_maxSpeed!=0)
		ov->append(KeyValuePair{ "max rychlost", new NumberValue{(double)m_maxSpeed} });

	ov->append(KeyValuePair{ "letuschopne", new BoolValue{m_airworthy} });
	return ov;
}