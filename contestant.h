#ifndef __CONTESTANT
#define __CONTESTANT

#include "citizen.h"

class Contestant : virtual public Citizen
{
private:
	char* partyName;

public:
	Contestant(const char* partyName, const char* name, const Date& birthday, int id, int ballotNum, bool isIsolated); //C'tor
	Contestant(const Contestant& other); //Copy c'tor
	Contestant(Contestant&& other); //Move c'tor

	char* getPartyName() const;
	bool setPartyName(const char* partyName);

	void show() const;

	~Contestant();
};
#endif // !__CONTESTANT