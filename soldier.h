#ifndef __SOLDIER
#define __SOLDIER

#include "citizen.h"

class Soldier : virtual public Citizen
{
private:
	char* unitName;

public:
	Soldier(const char* unit, const char* name, const Date& birthday, int id, int ballotNum, bool isIsolated); //C'tor
	Soldier(const Soldier& other); //Copy c'tor
	Soldier(Soldier&& other); //Move c'tor

	char* getUnitName() const;
	bool setUnitName(const char* unitName);

	void show() const;

	~Soldier();
};
#endif // !__CONTESTANT