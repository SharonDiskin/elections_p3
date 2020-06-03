#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "soldier.h"

//C'tor
Soldier::Soldier(const char* unitName, const char* name, const Date& birthday, int id, int ballotNum, bool isIsolated) : Citizen(name, birthday, id, ballotNum, isIsolated)
{
	this->unitName = new char[strlen(unitName) + 1];
	strcpy(this->unitName, unitName);
};

//Copy c'tor
Soldier::Soldier(const Soldier& other) : Citizen(other)
{
	this->unitName = new char[strlen(other.unitName) + 1];
	strcpy(unitName, other.unitName);
}

//move c'tor
Soldier::Soldier(Soldier&& other) : Citizen(other)
{
	this->unitName = other.unitName;
	other.unitName = nullptr;
}

char* Soldier::getUnitName() const
{
	return unitName;
}

bool Soldier::setUnitName(const char* unitName)
{

	this->unitName = new char[strlen(unitName) + 1];
	strcpy(this->unitName, unitName);
	return true;
}

void Soldier::show() const
{
	Citizen::show();
	cout << "Unit namr: " << this->unitName << "." << endl;
}


Soldier:: ~Soldier()
{
	if (unitName != nullptr)
		delete[] unitName;
}