#ifndef __AIRPORT_H
#define __AIRPORT_H

#include <string>
#include "ObjectJSON.h"

class Airport : public ObjectJSON {
public:
	Airport();
	Airport(std::string icao, std::string place);
	Airport(Value* obj);

	void setIcao(std::string icao);
	void setPlace(std::string place);
	std::string getIcao();
	std::string getPlace();

	bool equalityOfKeys(const std::string key) const override;
	std::string toString() const override;
	Value* getJSON() const override;

private:
	std::string m_icao; // icao
	std::string m_place; // poloha
};

#endif // !__AIRPORT_H