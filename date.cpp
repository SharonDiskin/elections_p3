#include <iostream>
using namespace std;

#include "date.h"

int const MIN_YEAR = 1900;
int const MAX_YEAR = 2020;

Date::Date(int day, int month, int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}

int Date::getDay() const
{
	return day;
}

int Date::getMonth() const
{
	return month;
}

int Date::getYear() const
{
	return year;
}

bool Date::setDay(int d)
{
	if (0 <= d && d <= 31)
	{
		day = d;
		return true;
	}
	else
	{
		cout << "Day must be between 1 to 31. Day unchanged.\n";
		return false;
	}
}

bool Date::setMonth(int m)
{
	if (1 <= m && m <= 12)
	{
		month = m;
		return true;
	}
	else
	{
		cout << "Month must be between 1 to 12. Month unchanged.\n";
		return false;
	}
}

bool Date::setYear(int y)
{
	if (MIN_YEAR <= y && y <= MAX_YEAR)
	{
		year = y;
		return true;
	}
	else
	{
		cout << "Year must be between " << MIN_YEAR << " to " << MAX_YEAR << ". year unchanged.\n";
		return false;
	}
}

const Date& Date::operator=(const Date& other)
{
	if (this != &other)
	{
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day << "\\" << date.month << "\\" << date.year;
	return os;
}

istream& operator>>(istream& in, Date& date)
{
	in >> date.day >> date.month >> date.year;
	return in;
}