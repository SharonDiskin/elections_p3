#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "adress.h"

//c'tor
Adress::Adress(const char* street, int number, const char* city)
{
	setStreet(street);
	setNumber(number);
	setCity(city);
}

//copy c'tor
Adress::Adress(const Adress& other)
{
	setStreet(other.street);
	setNumber(other.number);
	setCity(other.city);
}

Adress::Adress(Adress&& other)//Move c'tor
{
	street = other.street;
	other.street = nullptr;
	number = other.number;
	city = other.city;
	other.city = nullptr;
}

char* Adress::getStreet() const
{
	return street;
}

int Adress::getNumber() const
{
	return number;
}

char* Adress::getCity() const
{
	return city;
}

bool nameCharForAdress(char c)
//This function check is a given charcter is a letter (big or small) or a space.
//if yes, the function return true, else return false.
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c < 'Z') || (c == ' '));
}

bool validNameCheckForAdress(const char* str)
//This function returns true if a given string is made of letters and spaces,
//else the function return false.
{
	int i, len = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (!nameCharForAdress(str[i]))
		{
			return false;
		}
	}

	return true;
}

bool Adress::setStreet(const char* streetName)
{
	if (!validNameCheckForAdress(streetName)) //If validation check for adress name is false the setter returns false
	{
		cout << "Invalid adress.\n";
		return false;
	}
	else
	{
		street = new char[strlen(streetName) + 1]; //We allocate the street of the object according to the size of the input we recieved (we add 1 more by for the \0)
		strcpy(street, streetName);
		return true;
	}
}

bool Adress::setNumber(int num)
{
	if (num > 0)
	{
		number = num;
		return true;
	}
	else //The number enterd is not a positive number. A street number must be positive.
	{
		cout << "Street number must be a positive number. Number unchanged\n";
		return false;
	}
}

bool Adress::setCity(const char* cityName)
{
	if (!validNameCheckForAdress(cityName))
		return false;
	else
	{
		city = new char[strlen(cityName) + 1]; //We allocate the street of the object according to the size of the input we recieved (we add 1 more by for the \0)
		strcpy(city, cityName);
		return true;
	}
}

const Adress& Adress:: operator=(const Adress& other)
{
	if (this != &other)
	{
		delete[] street;
		street = new char[strlen(other.getStreet()) + 1];
		strcpy(street, other.getStreet());
		delete[] city;
		city = new char[strlen(other.getCity()) + 1];
		strcpy(city, other.getCity());
		number = other.number;
	}
	return *this;
}

ostream& operator<<(ostream& os, const Adress& adress)
{
	os << "Adress: " << adress.street << " " << adress.number << " " << adress.city;
	return os;
}

Adress:: ~Adress() //D'tor
{
	if (street != nullptr)
	{
		delete[] street;
	}
	if (city != nullptr)
	{
		delete[] city;
	}
}