#ifndef __PARTYVOTES
#define __PARTYVOTES

#include <iostream>
using namespace std;
#include "party.h"

class PartyVotes
{
private:
	Party party;
	int numOfVotes;

public:
	PartyVotes(); //Default c'tor (initialized in cpp file)
	PartyVotes(const Party& party); //C'tor

									//Get
	const Party& getParty() const;
	int getNumOfVoters() const;

	//Set
	bool setNumVotes(int num);
	bool setParty(Party& party);

	friend ostream& operator<<(ostream& os, const PartyVotes& partyVotes);

	//No need in d'tor - no dynamic allocation in class
};
#endif // !__PARTYVOTES