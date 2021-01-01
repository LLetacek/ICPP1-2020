#ifndef __JSON_H
#define __JSON_H

#include <string>
#include "platform.h"
#include "KeyValuePair.h"

// - tøída pro práci s JSON
class DLL_SPEC JSON
{
public:
	// - provede deserializaci øetìzce na vytvoøené objekty
	// - pøeètu znak a rozhodnu se
	// -- '{' - zaèínám èíst objekt
	// -------- ètu znaky, pak musí být dvojteèka, potom volám rekurzivnì deserialize(); následuje èárka nebo '}', podle situace se ètení opakuje
	// -- '[' - zaèínám èíst pole
	// -------- volám rekurzivnì deserialize(); následuje èárka nebo ']', podle situace se ètení opakuje
	// -- '"' - zaèínám èíst øetìzec - pozor na escapované uvozovky
	// -- [-0123456789] - zaèínám èíst èíslo - naètu všechny èíslice (pozor na možnou desetinnou teèku)
	// -- 'n' - 'null'
	// -- 't' - 'true'
	// -- 'f' - 'false'
	// -- cokoliv jiného - vyvolávám výjimku
	// - není pøípustné vracet nullptr
	// - deserializace musí být rozumnì implementována - není pøípustné zde napsat jednu extrémnì dlouhou metodu
	static Value* deserialize(const std::string& string);

	// - provede serializaci do JSON øetìzce
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