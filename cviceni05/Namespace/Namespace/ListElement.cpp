#include "ListElement.h"

using namespace Entities;

ListElement::ListElement(Person person)
	: ListElement(person, nullptr) {}

ListElement::ListElement(Person person, ListElement* element)
	: m_person(person),
	  m_next(element) {}

ListElement* ListElement::GetNextElement() const {
	return m_next;
}

Person ListElement::GetElement() const {
	return m_person;
}