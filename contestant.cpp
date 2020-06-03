#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "contestant.h"

//C'tor
Contestant::Contestant(const char* partyName, const char* name, const Date& birthday, int id, int ballotNum, bool isIsolated) : Citizen(name, birthday, id, ballotNum, isIsolated)
{
	this->partyName = new char[strlen(partyName) + 1];
	strcpy(this->partyName, partyName);
};

//Copy c'tor
Contestant::Contestant(const Contestant& other) : Citizen(other)
{
	this->partyName = new char[strlen(other.partyName) + 1];
	strcpy(partyName, other.partyName);
}

Contestant::Contestant(Contestant&& other) : Citizen(other)
{
	this->partyName = other.partyName;
	other.partyName = nullptr;
}

char* Contestant::getPartyName() const
{
	return partyName;
}

bool Contestant::setPartyName(const char* partyName)
{

	this->partyName = new char[strlen(partyName) + 1];
	strcpy(this->partyName, partyName);
	return true;
}

void Contestant::show() const
{
	Citizen::show();
	cout << "Party: " << this->partyName << "." << endl;
}


Contestant:: ~Contestant()
{
	if (partyName != nullptr)
		delete[] partyName;
}