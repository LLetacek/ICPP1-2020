#pragma once
#ifndef _LIST_ELEMENT_H
#define _LIST_ELEMENT_H

#include "Entities.h"

class ListElement {
 public:
 	 ListElement(Entities::Person person);
	 ListElement(Entities::Person person, ListElement* element);
	 ListElement* GetNextElement() const;
	 Entities::Person GetElement() const;
 private:
	 ListElement* m_next;
	 const Entities::Person m_person;
};

#endif // !_LIST_ELEMENT_H