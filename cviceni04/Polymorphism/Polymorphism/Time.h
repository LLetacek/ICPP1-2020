#pragma once
#ifndef _TIME_H
#define _TIME_H

#include "IComparable.h"

struct Time : public IComparable, public IObject{
 public:
	 Time(int hour, int minute, int second);
	 int CompareTo(IComparable* obj) const override;
	 std::string ToString() const override;
 private:
	 int m_hour;
	 int m_minute;
	 int m_second;
};

#endif // !_TIME_H