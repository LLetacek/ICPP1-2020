#include "Functions.h"

std::string escape(std::string str) {
	std::string newstr = "";
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str[i] == '"' || str[i] == '\\')
			newstr += '\\';
		newstr += str[i];
	}
	return newstr;
}
