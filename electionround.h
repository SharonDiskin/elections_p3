
#ifndef __ELECTIONROUND
#define __ELECTIONROUND

#include "ballot.h"

class ElectionRound
{
private:

	Date electionDate;
	int cLogSize = 0, cPhySize = 1; //Logical and physical size of citizen note
	Citizen** citizenNote;
	int pLogSize = 0, pPhySize = 1; //Logical and physical size of party list
	Party** partyList;
	int bLogSize = 0, bPhySize = 1; //Logical and physical size of ballot list
	Ballot** ballotList;

public:
	ElectionRound(const Date& date); //C'tor (No need in a default c'tor at this point - we only define one election round the whole program an we initialize it when defining it)

									 //get methods
	Date getElecationDate() const;
	Citizen** getCitizenNote() const;
	int getPLogSize() const;
	Party** getPartyList() const;
	int getPartyListSize() const;
	Ballot** getBallotList() const;

	//Set methods
	bool setElectionDate(const Date& date);
	bool setCitizenNote(Citizen** vv);
	bool setPartyList(Party** p);
	bool setBallotList(Ballot** b);

	void electionDay();

	//Add methods
	void addNewBallot(const Ballot& ballot);
	bool addNewParty(const Party& party);

	//Show methods
	void showRelevantBallots(int age, bool isIsolated);
	void showBallots() const;
	void showCitizens() const;
	void showParties() const;
	void showElectionResults() const;

	int findParty(Party** allParties, int size, const char* partyName);
	bool isValidBallot(int age, bool isIsolted, int ballotNum);

	const ElectionRound& operator+=(Citizen& citizen);
	//const ElectionRound& operator+=(const Contestant& citizen);

	~ElectionRound(); //D'tor
};

#endif // !__ELECTIONROUND