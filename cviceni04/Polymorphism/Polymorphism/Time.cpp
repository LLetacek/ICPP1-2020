#include "Time.h"

Time::Time(int hour, int minute, int second) 
	:	m_hour((0 <= hour && hour <= 23) ? hour : throw "hodiny musi byt cislo 0-23"),
		m_minute((0 <= minute && minute <= 59) ? hour : throw "minuty musi byt cislo 0-59"),
		m_second((0 <= second && second <= 59) ? hour : throw "sekundy musi byt cislo 0-59") {}

int Time::CompareTo(IComparable* obj) const {
	if (obj == nullptr)
		throw "nelze porovnavat s nullptr";

	Time* compObj = dynamic_cast<Time*>(obj);
	if (compObj == nullptr) {
		throw "nelze tyto objekty porovnat";
	}

	if (this->m_hour < compObj->m_hour) 
		return -1;
	else if (this->m_hour > compObj->m_hour) 
		return 1;

	if (this->m_minute < compObj->m_minute) 
		return -1;
	else if (this->m_minute > compObj->m_minute) 
		return 1;

	if (this->m_second < compObj->m_second) 
		return -1;
	else if (this->m_second > compObj->m_second) 
		return 1;
	
	return 0;
}

std::string Time::ToString() const {
	return	"CAS: " + 
			std::to_string(m_hour) + ":" + 
			std::to_string(m_minute) + ":" + 
			std::to_string(m_second);
}