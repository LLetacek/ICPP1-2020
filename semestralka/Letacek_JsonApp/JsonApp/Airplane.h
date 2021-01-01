#ifndef __AIRPLANE_H
#define __AIRPLANE_H

#include <string>
#include "ObjectJSON.h"
#include "Airport.h"

class Airplane : public ObjectJSON {
public:
	Airplane(std::string registration, std::string name, Airport* airport, int maxSpeed, bool airworthy);
	Airplane(Value* val);
	Airplane(const Airplane& plane);
	~Airplane();

	void setRegistration(std::string registration);
	void setName(std::string name);
	void setAirport(Airport* airport);
	void removeAirport();
	void appendInspection(std::string inspection);
	void updateInspection(std::string inspection, int index);
	void setMaxSpeed(int speed);
	void setAirworthy(bool airworthy);
	std::string getKey() const;
	
	const std::string getInspection(int index) const;
	Airport* getAirport();

	bool equalityOfKeys(const std::string key) const override;
	std::string toString() const override;
	Value* getJSON() const override;

private:
	std::string m_registration; // imatrikulace
	std::string m_name; // nazev
	Airport* m_airport; // letiste (muze byt null)
	DynamicArray<std::string> m_inspection; // kontroly
	int m_maxSpeed; // max rychlost
	bool m_airworthy; // letuschopne
};

#endif // !__AIRPLANE_H