#include "Phonebook.h"
#include <stdexcept>

using namespace Model;
using namespace Entities;
using namespace std;

Phonebook::Phonebook() 
	: m_begin(nullptr) {}

Phonebook::~Phonebook() {
	ListElement* tmp = nullptr;

	while (m_begin != nullptr) {
		tmp = m_begin->GetNextElement();
		delete m_begin;
		m_begin = tmp;
	}
}

void Phonebook::AddPerson(Person person) {
	ListElement* tmp = m_begin;
	ListElement* newElement = new ListElement(person, tmp);
	m_begin = newElement;
}

string Phonebook::FindPhone(string name) const {
	if (name.empty())
		throw invalid_argument("jmeno nemuze byt prazdne");

	ListElement* tmp = m_begin;
	while (tmp != nullptr && (tmp->GetElement().GetName().compare(name)!=0)) {
		tmp = tmp->GetNextElement();
	}

	if (tmp != nullptr)
		return tmp->GetElement().GetPhone();

	throw invalid_argument("nenalezeno");
}

string Phonebook::FindPhone(int id) const {
	if (id < 0)
		throw invalid_argument("id nemuze byt zaporne");

	ListElement* tmp = m_begin;
	while (tmp != nullptr && tmp->GetElement().GetId() != id) {
		tmp = tmp->GetNextElement();
	}

	if (tmp != nullptr)
		return tmp->GetElement().GetPhone();

	throw invalid_argument("nenalezeno");
}

Phonebook::ListElement::ListElement(Person person)
	: ListElement(person, nullptr) {}

Phonebook::ListElement::ListElement(Person person, ListElement* element)
	: m_person(person),
	m_next(element) {}

Phonebook::ListElement* Phonebook::ListElement::GetNextElement() const {
	return m_next;
}

Person Phonebook::ListElement::GetElement() const {
	return m_person;
}
