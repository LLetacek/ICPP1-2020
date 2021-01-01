#ifndef __NULL_VALUE_H
#define __NULL_VALUE_H

#include <string>
#include "platform.h"
#include "Value.h"

// - reprezentuje hodnotu typu JSON null
class DLL_SPEC NullValue :
	public Value
{
public:
	std::string serialize() const override;
};

#endif // !__NULL_VALUE_H