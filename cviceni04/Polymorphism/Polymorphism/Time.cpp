#include "Time.h"

Time::Time(int hour, int minute, int second) :	m_hour(hour % 24),
												m_minute(minute % 60),
												m_second(second % 60) {}
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