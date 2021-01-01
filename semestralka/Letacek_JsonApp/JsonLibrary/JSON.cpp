#include <iostream>
#include "JSON.h"
#include "BoolValue.h"
#include "NullValue.h"
#include "NumberValue.h"
#include "StringValue.h"
#include "ArrayValue.h"
#include "ObjectValue.h"

Value* JSON::deserialize(const std::string& string) {
	unsigned int pointer = 0;
	if (pointer >= string.size())
		throw std::invalid_argument("Retezec nesmi byt prazdny!");

	return deserialize(string, pointer);
}

Value* JSON::deserialize(const std::string& string, unsigned int& pointer) {
	Value* json = deserializeValue(string, pointer);

	trim(string, pointer);
	if (pointer > string.size() || string[pointer] != '\0') {
		delete json;
		throw std::invalid_argument("Retezec musi byt JSON! - ocekavan konec");
	}

	return json;
}

Value* JSON::deserializeObject(const std::string& string, unsigned int& pointer) {
	ObjectValue* json = new ObjectValue{};
	try {
		deseralizeSet(json, string, pointer, '{', '}');
	}
	catch (const std::invalid_argument& ex) {
		delete json;
		throw std::invalid_argument(ex.what());
	}
	return json;
}

Value* JSON::deserializeArray(const std::string& string, unsigned int& pointer) {
	ArrayValue* json = new ArrayValue{};
	try {
		deseralizeSet(json, string, pointer, '[', ']');
	}
	catch (const std::invalid_argument& ex) {
		delete json;
		throw std::invalid_argument(ex.what());
	}
	return json;
}

Value* JSON::deseralizeSet(Value* json, const std::string& string, unsigned int& pointer, const char start, const char end) {
	ArrayValue* valArray = nullptr;
	ObjectValue* object = dynamic_cast<ObjectValue*> (json);
	if (!object)
		valArray = dynamic_cast<ArrayValue*> (json);

	trim(string, pointer);
	if (pointer >= string.size())
		throw std::invalid_argument("Retezec musi byt JSON! - neocekavany konec");

	// zacatek - musi obsahovat hodnotu, resp. par klic-hodnotu, nebo nic
	if (string[pointer] == start) {
		trim(string, ++pointer);
		while (pointer < string.size() && string[pointer] != end) {
			if (object)
				object->append(deserializeKeyValue(string, pointer));
			else if (valArray)
				valArray->append(deserializeValue(string, pointer));

			// hlidani carky nebo ukonceni objektu
			trim(string, pointer);
			if (!(pointer < string.size() && (string[pointer] == end || string[pointer] == ',')))
				throw std::invalid_argument("Retezec musi byt JSON! - neocekavany konec");
			else if (string[pointer] == ',')
				++pointer;
		}
	}

	++pointer;
	return json;
}

Value* JSON::deserializeValue(const std::string& string, unsigned int& pointer) {
	trim(string, pointer);
	if (pointer >= string.size())
		throw std::invalid_argument("Retezec musi byt JSON! - neocekavany zacatek klic-hodnoty");

	if ((48 <= string[pointer] && string[pointer] <= 57) || string[pointer] == '-') { // - NUM
		int sign = (string[pointer] == '-') ? -1 : 1;
		if (string[pointer] == '-')
			++pointer;

		// musi byt cislo po zapornem znamenku -> neni mozne nacist cislo zacinajici desetinnou carkou, nebo cislo zacinajici s kladnem znamenkem
		if (!(48 <= string[pointer] && string[pointer] <= 57))
			throw std::invalid_argument("Retezec musi byt JSON! - ocekavano cislo");

		double val = 0;
		double constant = 1;
		bool dec = false;
		while (pointer < string.size() && (48 <= string[pointer] && string[pointer] <= 57) || string[pointer] == '.') {
			if (string[pointer] == '.' && dec) {
				throw std::invalid_argument("Retezec musi byt JSON! - neocekavana desetinna tecka");
			}
			else if (string[pointer] == '.' && !dec) {
				pointer++;
				dec = true;
				continue;
			}

			if (dec)
				constant /= 10;

			int number = (string[pointer] - 48);
			val *= (dec) ? 1 : 10;
			val += number * constant;
			++pointer;
		}

		if (string[pointer - 1] == '.')
			throw std::invalid_argument("Retezec musi byt JSON! - za desetinnou teckou ocekavano cislo");

		return (new NumberValue{ val * sign });
	}
	else if (string[pointer] == 'n') { // - NULL
		if (pointer + 3 > string.size() || !(
			(string[pointer + 1] == 'u') &&
			(string[pointer + 2] == 'l') &&
			(string[pointer + 3] == 'l')))
			throw std::invalid_argument("Retezec musi byt JSON! - neocekavany string pro null");

		pointer = pointer + 4;
		return (new NullValue{});
	}
	else if (string[pointer] == 't' || string[pointer] == 'f') { // - BOOL
		bool val;
		if (string[pointer] == 't') {
			if (pointer + 3 > string.size() || !(
				(string[pointer + 1] == 'r') &&
				(string[pointer + 2] == 'u') &&
				(string[pointer + 3] == 'e')))
				throw std::invalid_argument("Retezec musi byt JSON! - neocekavany string pro boolean true");
			pointer = pointer + 4;
			val = true;
		}
		else {
			if (pointer + 4 > string.size() || !(
				(string[pointer + 1] == 'a') &&
				(string[pointer + 2] == 'l') &&
				(string[pointer + 3] == 's') &&
				(string[pointer + 4] == 'e')))
				throw std::invalid_argument("Retezec musi byt JSON! - neocekavany string pro boolean false");
			pointer = pointer + 5;
			val = false;
		}
		return (new BoolValue{ val });
	}
	else if (string[pointer] == '"') { // - STRING
		return (new StringValue{ getString(string, pointer) });
	}
	else if (string[pointer] == '{') { // - OBJECT
		return deserializeObject(string, pointer);
	}
	else if (string[pointer] == '[') { // - ARRAY
		return deserializeArray(string, pointer);
	}
	else {
		throw std::invalid_argument("Retezec musi byt JSON! - neocekavany zacatek hodnoty");
	}
}

std::string JSON::getString(const std::string& string, unsigned int& pointer) {
	// musi obsahovat -> "retezec" 
	trim(string, pointer);
	if (pointer >= string.size() && string[pointer] != '"')
		throw std::invalid_argument("Retezec musi byt JSON! - neocekavany zacatek stringu");
	pointer++;

	std::string str = "";
	while (pointer < string.size() && !(string[pointer - 1] != '\\' && string[pointer] == '"')) {
		if (pointer + 1 < string.size() && (
			(string[pointer] == '\\' && string[pointer + 1] == '\\') ||
			(string[pointer] == '\\' && string[pointer + 1] == '\"')))
			++pointer;
		str += string[pointer++];
	}

	if (pointer >= string.size())
		throw std::invalid_argument("Retezec musi byt JSON! - neocekavany konec stringu");

	pointer++;
	return str;
}

KeyValuePair JSON::deserializeKeyValue(const std::string& string, unsigned int& pointer) {
	// klic
	std::string key = getString(string, pointer);

	// oddelovac
	trim(string, pointer);
	if (pointer >= string.size() || string[pointer] != ':')
		throw std::invalid_argument("Retezec musi byt JSON! - ocekavan oddelovac");

	// hodnota
	Value* val = deserializeValue(string, ++pointer);

	if (pointer >= string.size() || !(whiteSpace(string[pointer]) || string[pointer] == '}' || string[pointer] == ']' || string[pointer] == ','))
		throw std::invalid_argument("Retezec musi byt JSON! - neocekavany konec u key-value");

	KeyValuePair kv{ key, val };
	return kv;
}

void JSON::trim(const std::string& string, unsigned int& pointer) {
	while (pointer < string.size()) {
		if (whiteSpace(string[pointer]))
			pointer++;
		else
			return;
	}
}

bool JSON::whiteSpace(const char character) {
	return (character == ' ' || character == '\t' || character == '\n');
}

std::string JSON::serialize(const Value* value) {
	return value->serialize();
}
