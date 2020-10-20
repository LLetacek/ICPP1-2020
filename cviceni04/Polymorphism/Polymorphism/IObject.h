#pragma once
#ifndef _I_OBJECT_H
#define _I_OBJECT_H

#include <string>

class IObject {
 public:
	 virtual ~IObject() {}
	 virtual std::string ToString() const = 0;
};

#endif // !_I_OBJECT_H