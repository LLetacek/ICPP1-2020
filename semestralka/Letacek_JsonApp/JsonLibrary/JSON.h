#ifndef __JSON_H
#define __JSON_H

#include <string>
#include "platform.h"
#include "KeyValuePair.h"

// - t��da pro pr�ci s JSON
class DLL_SPEC JSON
{
public:
	// - provede deserializaci �et�zce na vytvo�en� objekty
	// - p�e�tu znak a rozhodnu se
	// -- '{' - za��n�m ��st objekt
	// -------- �tu znaky, pak mus� b�t dvojte�ka, potom vol�m rekurzivn� deserialize(); n�sleduje ��rka nebo '}', podle situace se �ten� opakuje
	// -- '[' - za��n�m ��st pole
	// -------- vol�m rekurzivn� deserialize(); n�sleduje ��rka nebo ']', podle situace se �ten� opakuje
	// -- '"' - za��n�m ��st �et�zec - pozor na escapovan� uvozovky
	// -- [-0123456789] - za��n�m ��st ��slo - na�tu v�echny ��slice (pozor na mo�nou desetinnou te�ku)
	// -- 'n' - 'null'
	// -- 't' - 'true'
	// -- 'f' - 'false'
	// -- cokoliv jin�ho - vyvol�v�m v�jimku
	// - nen� p��pustn� vracet nullptr
	// - deserializace mus� b�t rozumn� implementov�na - nen� p��pustn� zde napsat jednu extr�mn� dlouhou metodu
	static Value* deserialize(const std::string& string);

	// - provede serializaci do JSON �et�zce
	static std::string serialize(const Value* value);

private:
	static Value* deserialize(const std::string& string, unsigned int& pointer);
	static Value* deserializeObject(const std::string& string, unsigned int& pointer);
	static Value* deserializeArray(const std::string& string, unsigned int& pointer);
	static Value* deserializeValue(const std::string& string, unsigned int& pointer);
	static KeyValuePair deserializeKeyValue(const std::string& string, unsigned int& pointer);

	static std::string getString(const std::string& string, unsigned int& pointer);

	static void trim(const std::string& string, unsigned int& pointer);
	static bool whiteSpace(const char character);

	static Value* deseralizeSet(Value* json, const std::string& string, unsigned int& pointer, const char start, const char end);
};


#endif // !__JSON_H