#ifndef __NUMBER_VALUE_H
#define __NUMBER_VALUE_H

#include <string>
#include "platform.h"
#include "Value.h"

// - reprezentuje hodnotu typu JSON ��slo
class DLL_SPEC NumberValue :
	public Value
{
public:
	NumberValue(double value);

	// - vrac� ��selnou hodnotu 
	double get() const;

	std::string serialize() const override;

private:
	double m_value;
};

#endif // !__NUMBER_VALUE_H