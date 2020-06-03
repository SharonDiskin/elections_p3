#include <iostream>
using namespace std;

#include "ballot.h"

const char* typeStr[] = { "Regular", "Corona", "Military", "MilitaryCoron" };

int Ballot::counter = 0;
Ballot::Ballot() : Ballot(Adress("Herzel", 16, "Tel Aviv"), (Ballot::eType)0) { }; //Default c'tor

Ballot::Ballot(const Adress& location, Ballot::eType type) : location(std::move(location)) //C'tor
{
	votingPercentage = 0;
	voters = new Citizen*[vPhysize];
	partyList = new PartyVotes*[pPhysize];
	serialNum = ++counter;
	setType(type);

}

Ballot::Ballot(const Ballot& other) //Copy c'tor
{
	serialNum = other.serialNum;
	votingPercentage = other.votingPercentage;
	counter = other.counter;
	numOfVotes = other.numOfVotes;
	pPhysize = other.pPhysize;
	pLogsize = other.pLogsize;
	vPhysize = other.vPhysize;
	vLogSize = other.vLogSize;
	ballotType = other.ballotType;
	voters = new Citizen*[vPhysize];
	for (int i = 0; i < vLogSize; i++)
	{
		voters[i] = other.voters[i];
	}
	partyList = new PartyVotes*[pPhysize];
	for (int i = 0; i<pLogsize; i++)
	{
		partyList[i] = other.partyList[i];
	}
	location = other.location;
}

//move c'tor
Ballot::Ballot(Ballot&& other)
{
	serialNum = other.serialNum;
	votingPercentage = other.votingPercentage;
	counter = other.counter;
	numOfVotes = other.numOfVotes;
	pPhysize = other.pPhysize;
	pLogsize = other.pLogsize;
	vPhysize = other.vPhysize;
	vLogSize = other.vLogSize;
	ballotType = other.ballotType;
	voters = other.voters;
	other.voters = nullptr;
	partyList = other.partyList;
	other.partyList = nullptr;
	location = other.location;
}

int Ballot::getSerialNum() const
{
	return serialNum;
}

int Ballot::getNumOfVotes() const
{
	return numOfVotes;
}

int Ballot::getNumOfVoters() const
{
	return vLogSize;
}

Adress Ballot::getLocation() const
{
	return location;
}

Citizen** Ballot::getValidVoters() const
{
	return voters;
}

double Ballot::getVotingPercentage() const
{
	return votingPercentage;
}

PartyVotes** Ballot::getPartyList() const
{
	return partyList;
}

int Ballot::getCounter() const
{
	return counter;
}

Ballot::eType Ballot::getType() const
{
	return this->ballotType;
}

bool Ballot::setSerialNum(int s)
{
	if (s <= 0)
	{
		cout << "The serial number must be a positive number. Number unchanged.\n";
		return false;
	}
	else
	{
		serialNum = s;
		return true;
	}
}

bool Ballot::setType(Ballot::eType t)
{
	if ((int)t < 0 || (int)t > 3)
	{
		cout << "You entered invalid type. Ballot type unchanged\n";
		return false;
	}
	else
	{
		ballotType = t;
		return true;
	}
}

bool Ballot::setLocation(Adress l)
{
	location = l;
	return true;
}

bool Ballot::setNumOfVotes(int nv)
{
	numOfVotes = nv;
	return true;
}

bool Ballot::setVotingPercentage(int votersWhoVoted, int totalVoters)
{
	if (totalVoters == 0)
	{
		votingPercentage = 0;
		return false;
	}
	else
	{
		votingPercentage = ((double)votersWhoVoted / (double)totalVoters) * 100;
		return true;
	}
}

Citizen** reallocCitizenArr(Citizen** arr, int oldSize, int newSize)
{
	int i;
	Citizen** newArr = new Citizen*[newSize];
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];
	}

	delete[] arr;
	return newArr;
}

void Ballot::addVoter(const Citizen& c)
{
	if (vLogSize == vPhysize)
	{
		vPhysize *= 2;
		voters = reallocCitizenArr(voters, vLogSize, vPhysize);
	}

	voters[vLogSize] = new Citizen(c);
	vLogSize++;
}

PartyVotes** reallocPartyVotesArray(PartyVotes** arr, int oldSize, int newSize)
{
	int i;
	PartyVotes** newArr = new PartyVotes*[newSize];
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];
	}

	delete[] arr;
	return newArr;
}

void Ballot::addParty(const Party& p)//from party to partyVotes
{
	PartyVotes* pv;
	pv = new PartyVotes(p);

	if (pLogsize == pPhysize)
	{
		pPhysize *= 2;
		partyList = reallocPartyVotesArray(partyList, pLogsize, pPhysize);
	}
	partyList[pLogsize] = pv;
	pLogsize++;
}

void Ballot::addVoteToParty(int index)
{
	int currVotes;
	currVotes = partyList[index]->getNumOfVoters();
	partyList[index]->setNumVotes(currVotes + 1);
}

void Ballot::show() const
{
	cout << "-------------\n";
	cout << "Ballot # " << serialNum << endl;
	cout << "-------------\n";

	cout << "Ballot type: " << typeStr[(int)ballotType] << endl
		<< location << endl;

	if (vLogSize == 0)
	{
		cout << "No citizens are allowed to vote in this ballot at the moment.\n";
	}
	else
	{
		cout << "The citizens who are allowed to vote in this ballot are:" << endl;
		for (int i = 0; i < vLogSize; i++)
		{
			voters[i]->show();
		}
	}

	cout << "Ballot voting percentage is: " << votingPercentage << endl;

	cout << "The voting results are:" << endl;
	for (int i = 0; i < pLogsize; i++)
	{
		cout << *(partyList[i]) << endl;
	}
}

Ballot::~Ballot()
{
	if (voters != nullptr)
	{
		delete[] voters;
	}
	if (partyList != nullptr)
	{
		delete[] partyList;
	}
}