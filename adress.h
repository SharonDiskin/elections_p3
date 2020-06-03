#ifndef __ADRESS
#define __ADRESS

#include <iostream>
using namespace std;

class Adress
{
private:
	char* street;
	int number;
	char* city;

public:

	Adress(const char* name = "Hertzel", int number = 1, const char* city = "Tel Aviv"); //C'tor
	Adress(const Adress& other); //cpy c'tor
	Adress(Adress&& other);//Move c'tor

						   //Get methods
	char* getStreet() const;
	int getNumber() const;
	char* getCity() const;

	//Set methods
	bool setStreet(const char* streetName);
	bool setNumber(int num);
	bool setCity(const char* cityName);

	const Adress& operator=(const Adress& other);
	friend ostream& operator<<(ostream& os, const Adress& adress);

	~Adress(); //D'tor
};

#endif // !__ADRESS