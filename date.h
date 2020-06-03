#ifndef __DATE
#define __DATE

#include <iostream>
using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date(int day = 1, int month = 1, int year = 2000); //C'tor (default)

													   //Get methods
	int getDay() const;
	int getMonth() const;
	int getYear() const;

	//Set methods
	bool setDay(int d);
	bool setMonth(int m);
	bool setYear(int y);

	const Date& operator=(const Date& other);
	friend ostream& operator<<(ostream& os, const Date& date);
	friend istream& operator>>(istream& in, Date& date);

	//No need in d'tor - no dynamic allocations
};
#endif // !__DATE