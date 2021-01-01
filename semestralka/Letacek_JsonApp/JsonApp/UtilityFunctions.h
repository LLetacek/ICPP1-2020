#ifndef __UTILITY_FUNCTIONS_H
#define __UTILITY_FUNCTIONS_H

#include <string>
#include <api.h>

template<typename From, typename To>
To valueToVariable(Value* val, To ifNull) {
	From tmp = dynamic_cast<From> (val);
	if (tmp)
		return tmp->get();
	else if (dynamic_cast<NullValue*> (val))
		return ifNull;
	else
		throw std::invalid_argument("Chyba - ocekavana hodnota nenalezena");
}

template<typename From, typename To>
To valueToVariableNotNull(Value* val) {
	From tmp = dynamic_cast<From> (val);
	if (tmp)
		return tmp->get();
	else
		throw std::invalid_argument("Chyba - ocekavana hodnota nenalezena");
 }

template<typename From, typename To>
To valueOfOptionalAttribute(const std::string attName, int& checker, ObjectValue* obj, const To ifNull) {
	Value* tmp = nullptr;
	try {
		tmp = obj->getValueByKey(attName); // nepovinny udaj
	}
	catch (...) {
		++checker;
		return ifNull;
	}

	To val = valueToVariable<From, To>(tmp, ifNull); // vyhodi vyjimku, pokud Value neodpovida
	return val;
}

#endif // !__UTILITY_FUNCTIONS_H