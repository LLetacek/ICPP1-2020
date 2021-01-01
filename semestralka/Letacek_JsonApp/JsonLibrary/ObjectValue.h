#ifndef __OBJECT_VALUE_H
#define __OBJECT_VALUE_H

#include <string>
#include "platform.h"
#include "DynamicArray.h"
#include "KeyValuePair.h"

// - reprezentuje hodnotu typu JSON objekt
class DLL_SPEC ObjectValue :
	public Value
{
public:
	ObjectValue();
	~ObjectValue();

	// - p�id� kl��-element do objektu
	void append(const KeyValuePair& pair);

	// - vrati pocet hodnot
	int getSize() const;

	// - vrati 
	Value* getValueByKey(const std::string key) const;

	std::string serialize() const override;
private:
	// - atribut DynamicArray<KeyValuePair> pro uchov�n� jednotliv�ch hodnot a kl��� v objektu
	DynamicArray<KeyValuePair> m_array;
};

#endif // !__OBJECT_VALUE_H