#include "Entities.h"

using namespace Entities;
using namespace std;

Person::Person(int id, string name, string phone) 
	: m_id((id>=0) ? id : throw "-- id nemuze byt zaporne --"),
	  m_name(name),
	  m_phone(phone) {}

int Person::GetId() const {
	return m_id;
}

string Person::GetName() const {
	return m_name;
}

string Person::GetPhone() const {
	return m_phone;
}
