#pragma once
#ifndef _MODEL_H
#define _MODEL_H


#include "Entities.h"
#include <string>

namespace Model {

	class Phonebook {
	 public:
		 Phonebook();
		 ~Phonebook();
		 void AddPerson(Entities::Person person);
		 std::string FindPhone(std::string name) const;
		 std::string FindPhone(int id) const;
	 private:
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

		 ListElement* m_begin;
	};
}

#endif // !_MODEL_H