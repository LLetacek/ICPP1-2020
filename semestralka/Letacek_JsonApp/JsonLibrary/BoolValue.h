#ifndef __BOOL_VALUE_H
#define __BOOL_VALUE_H

#include <string>
#include "platform.h"
#include "Value.h"

// - reprezentuje hodnotu typu JSON bool
class DLL_SPEC BoolValue :
	public Value
{
public:
	BoolValue(bool value);

	// - vrací bool hodnotu
	bool get() const;

	std::string serialize() const override;

private:
	bool m_value;
};

#endif // !__BOOL_VALUE_H