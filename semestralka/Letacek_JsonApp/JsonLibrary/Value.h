#ifndef __VALUE_H
#define __VALUE_H

#include <string>
#include "platform.h"

// JSON hodnota - reprezentuje abstraktního pøedka pro základní datové typy v JSON (string, number, object, array, bool, null)
class DLL_SPEC Value
{
public:
	virtual ~Value() {};

	// serializuje hodnotu do podoby JSON reprezentace
	virtual std::string serialize() const = 0;
};

#endif // !__VALUE_H