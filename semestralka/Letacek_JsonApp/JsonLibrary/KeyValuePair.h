#ifndef __KEY_VALUE_PAIR_H
#define __KEY_VALUE_PAIR_H

#include <string>
#include "platform.h"
#include "Value.h"

// - definuje p�r kl�� (�et�zec) a hodnota (JSON hodnota) pro reprezentaci hodnot JSON objektu
class DLL_SPEC KeyValuePair {
public:
	KeyValuePair(std::string key, Value* value);

	// - vr�t� kl��
	std::string getKey() const;

	// - vr�t� hodnotu
	Value* getValue() const;

	// - zjistovani shodnosti klicu
	bool equalityOfKeys(const std::string key) const;

	std::string serialize() const;

private:
	std::string m_key;
	Value* m_value;
};

#endif // !__KEY_VALUE_PAIR_H