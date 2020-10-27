#pragma once
#ifndef _MODEL_H
#define _MODEL_H


#include "ListElement.h"
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
		 ListElement* m_begin;
	};
}

#endif // !_MODEL_H