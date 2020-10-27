#pragma once
#ifndef _ENTITIES_H
#define _ENTITIES_H

#include <string>

namespace Entities {

	class Person {
	 public:
	 	 Person(int id, std::string name, std::string phone);
	 	 int GetId() const;
		 std::string GetName() const;
		 std::string GetPhone() const;
	 private:
		 const int m_id;
		 const std::string m_name;
		 const std::string m_phone;
	};
}

#endif // !_ENTITIES_H