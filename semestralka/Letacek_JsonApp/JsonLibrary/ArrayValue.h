#ifndef __ARRAY_VALUE_H
#define __ARRAY_VALUE_H

#include <string>
#include "platform.h"
#include "DynamicArray.h"
#include "Value.h"

// - reprezentuje hodnotu typu JSON pole
class DLL_SPEC ArrayValue :
	public Value
{
public:
	ArrayValue();
	~ArrayValue();

	// - pøidá element na konec pole
	void append(Value* element);

	// - vrati pocet hodnot
	int getSize() const;

	const Value* getElementAt(int index) const;
	Value* getElementAt(int index);

	std::string serialize() const override;

private:
	// - atribut DynamicArray<Value*> pro uchování jednotlivých elementù v poli
	DynamicArray<Value*> m_array;
};

#endif // !__ARRAY_VALUE_H