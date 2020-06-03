#ifndef __BALLOT
#define __BALLOT

#include "contestant.h"
#include "soldier.h"
#include "adress.h"
#include "partyvotes.h"

class Ballot
{
public:
	enum class eType { Regular, Corona, Military, MilitaryCorona };

protected:
	static int counter; //Static counter, gives serial number to each ballot
	int pLogsize = 0, pPhysize = 1, vLogSize = 0, vPhysize = 1;
	int numOfVotes = 0;
	double votingPercentage = 0;
	int serialNum;
	eType ballotType;
	Adress location;
	Citizen** voters;
	PartyVotes** partyList;

public:
	Ballot(); //default c'tor
	Ballot(const Adress& location, Ballot::eType type); //C'tor
	Ballot(const Ballot& other); //Copy c'tor
	Ballot(Ballot&& other);//move c'tor

						   //Get methods
	int getSerialNum() const;
	int getNumOfVotes() const;
	int getNumOfVoters() const;
	Adress getLocation() const;
	double getVotingPercentage() const;
	Citizen** getValidVoters() const;
	PartyVotes** getPartyList() const;
	int getCounter() const;
	eType getType() const;

	//Add methods
	void addVoter(const Citizen& c);
	void addParty(const Party& p);
	void addVoteToParty(int index);

	//Set Methods
	bool setSerialNum(int s);
	bool setLocation(Adress l);
	bool setNumOfVotes(int nv);
	bool setVotingPercentage(int votersWhoVoted, int totalVoters);
	bool setType(Ballot::eType t);

	virtual void show() const;

	~Ballot(); //D'tor
};

#endif // !__BALLOT