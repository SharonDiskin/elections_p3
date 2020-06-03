#ifndef __CITIZEN
#define __CITIZEN

#include "date.h"

class Citizen
{
protected:
	char* name;
	Date birthday;
	int id;
	int ballotNum;
	bool isIsolated;

public:

	Citizen(); //Default c'tor
	Citizen(const char* name, const Date& birthday, int id, int ballotNum, bool isIsolated); //C'tor
	Citizen(const Citizen& other); //Copy c'tor
	Citizen(Citizen&& other);//Move c'tor

							 //Get methods
	const char* getName() const; //Name is 'const' - can't change name
	const Date& getBirth() const; //Birthday is 'const' - can't change date of birth
	const int getId() const; //Id is 'const' - can't change id
	int getBallotNum() const;
	bool getIsIsolated() const;

	//Set methods
	bool setName(const char* citizenName);
	bool setBirth(Date birth);
	bool setId(int id);
	bool setBallotNum(int bn);
	bool setIsIsolated(bool ans);


	virtual void show() const;

	virtual ~Citizen(); //D'tor
};

#endif // !__CITIZEN