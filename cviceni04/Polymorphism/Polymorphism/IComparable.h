#pragma once
#ifndef _I_COMPARABLE_H
#define _I_COMPARABLE_H

#include "IObject.h"

class IComparable {
 public:
	 virtual ~IComparable() {}
	 virtual int CompareTo(IComparable* obj) const = 0;
};

#endif // !_I_COMPARABLE_H