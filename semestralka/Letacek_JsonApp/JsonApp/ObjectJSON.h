#ifndef __OBJECT_JSON_H
#define __OBJECT_JSON_H

#include <string>
#include <api.h>

class ObjectJSON {
public:
	virtual ~ObjectJSON() {}

	// - zjistovani shodnosti klicu
	virtual bool equalityOfKeys(const std::string key) const = 0;

	// - objekt do citelne podoby
	virtual std::string toString() const = 0;

	// - objekt do JSON
	virtual Value* getJSON() const = 0;
};

#endif // !__OBJECT_JSON_H