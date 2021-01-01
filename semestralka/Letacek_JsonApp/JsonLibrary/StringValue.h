#ifndef __STRING_VALUE_H
#define __STRING_VALUE_H

#include <string>
#include "platform.h"
#include "Value.h"

// - reprezentuje hodnotu typu JSON øetìzec (string)
class DLL_SPEC StringValue :
	public Value
{
public:
	StringValue(std::string value);

	// - vrací øetìzcovou hodnotu
	std::string get() const;

	std::string serialize() const override;

private:
	std::string m_value;
};

#endif // !__STRING_VALUE_H