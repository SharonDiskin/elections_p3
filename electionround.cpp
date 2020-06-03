#include <iostream>
using namespace std;

#include <string.h>
#include "electionround.h"

int const MAX_LEN = 100;
int const PARTY_NOT_FOUND = -1;

//C'tor
ElectionRound::ElectionRound(const Date& date) : electionDate(date)
{
	citizenNote = new Citizen*[cPhySize];
	partyList = new Party*[pPhySize];
	ballotList = new Ballot*[bPhySize];
}

Date ElectionRound::getElecationDate() const
{
	return electionDate;
}

Citizen** ElectionRound::getCitizenNote() const
{
	return citizenNote;
}

int ElectionRound::getPLogSize() const
{
	return pLogSize;
}

Party** ElectionRound::getPartyList() const
{
	return partyList;
}

int ElectionRound::getPartyListSize() const
{
	return pLogSize;
}

Ballot** ElectionRound::getBallotList() const
{
	return ballotList;
}

bool ElectionRound::setElectionDate(const Date& date)
{
	electionDate = date;
	return true;
}

bool ElectionRound::setCitizenNote(Citizen** vv)
{
	if (vv = nullptr)
	{
		cout << "The array doesnt exist. The cuurent array unchanged.\n";
		return false;
	}
	else
	{
		citizenNote = vv;
		return true;
	}
}

bool ElectionRound::setPartyList(Party** p)
{
	if (p == nullptr)
	{
		cout << "The array doesnt exist. The cuurent array unchanged.\n";
		return false;
	}
	else
	{
		partyList = p;
		return true;
	}
}

bool ElectionRound::setBallotList(Ballot** b)
{
	if (b == nullptr)
	{
		cout << "The array doesnt exist. The cuurent array unchanged.\n";
		return false;
	}
	else
	{
		ballotList = b;
		return true;
	}
}

Ballot** reallocBallotArray(Ballot** arr, int oldSize, int newSize)
//This function make the ballot array bigger.
{
	int i;
	Ballot** newArr = new Ballot*[newSize];//allocate new memory according to a given size.
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];//copy data.
	}

	delete[] arr;//deallocate old memory.
	return newArr;
}

void ElectionRound::addNewBallot(const Ballot& ballot)
//This function gets a ballot from user, and insert the ballot into the ballot list(array at the moment).
{
	if (bLogSize == bPhySize)//the ballot array is full?
	{
		bPhySize *= 2;
		ballotList = reallocBallotArray(ballotList, bLogSize, bPhySize);//make him bigger.
	}
	ballotList[bLogSize] = new Ballot(ballot);
	for (int i = 0; i < pLogSize; i++)//making the party list for the new ballot.
	{
		ballotList[bLogSize]->addParty(*(partyList[i]));
	}
	bLogSize++;
}

bool checkIfIdExists(int id, Citizen** allCitizens, int size)
//This function checks if a given id is already exist in the system.
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (allCitizens[i]->getId() == id)
		{
			return true;
		}
	}
	return false;
}

Citizen** reallocCitizenArray(Citizen** arr, int oldSize, int newSize)
//This function make the citizen array bigger.
{
	int i;
	Citizen** newArr = new Citizen*[newSize];//allocating new memory according to given size.
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];//copy data.
	}

	delete[] arr;//deallocate old memory.
	return newArr;
}


int ElectionRound::findParty(Party** allParties, int size, const char* partyName)
//This function seach for a party according to a given party name,
//if the party doesnt exist, the function return -1.
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (strcmp(partyName, allParties[i]->getName()) == 0)
		{
			return i;
		}
	}
	return PARTY_NOT_FOUND; //didn't find the party that matches the name user enterd
}

Party** reallocPartyArray(Party** arr, int oldSize, int newSize)
//This function make the party array bigger.
{
	int i;
	Party** newArr = new Party*[newSize];//allocate new memory according to a given size.
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];//copy data.
	}

	delete[] arr;//deallocate old memory.
	return newArr;
}

bool ElectionRound::addNewParty(const Party& party)
//This function gets a new party, and add her to the party list(now array).
{
	Party newParty(party);
	if (findParty(partyList, pLogSize, party.getName()) != PARTY_NOT_FOUND)
	{//if the party doesnt exist.
		cout << "\nThe party you entered alreay exist.\nThe party wasn't added to the parties list\n";
		return false;
	}
	else//if the party isnt in the system: 
	{
		int i;
		for (i = 0; i < bLogSize; i++) //We add the new party to all of the ballots
		{
			ballotList[i]->addParty(newParty);
		}
		if (pLogSize == pPhySize)
		{
			pPhySize *= 2;
			partyList = reallocPartyArray(partyList, pLogSize, pPhySize);
		}

		partyList[pLogSize] = new Party(newParty);//placement
		pLogSize++;
		return true;
	}

}

void ElectionRound::electionDay()
//This function recieve all the votes from the citizens.
{
	char answer;
	char partyName[MAX_LEN];
	bool canVote = true;
	for (int i = 0; i < cLogSize; i++)//for each citizen:
	{
		canVote = true;
		cout << "Hello " << citizenNote[i]->getName() << "." << " Do you want to vote? Please enter y/n:" << endl;
		cin >> answer;
		if (answer == 'y')//want to vote
		{
			if (citizenNote[i]->getIsIsolated() == true) //We check if the person is qualified to vote (if he is isolated than if he wear valid cloths)
			{
				answer = '0'; //We restart answer in order to re-use the vraiable
				do {
					cout << "You are in isolation. Do you have proper wear?\n";
					cin >> answer;
				} while (answer != 'y' && answer != 'n');

				if (answer == 'n')
				{
					cout << "You must wear proper cloth inorder to vote\n";
					canVote = false; //We flag that this person can vote and we move to the next person
				}
			}

			if (canVote) {
				//If you got to this point it means the person is valid to vote - we take his vote
				int j = 0, k = 0, cBallotNum = citizenNote[i]->getBallotNum();

				do {//enter the party name, if worng or doesnt exist, enter again.
					cout << "Please enter the party name: <Party name must be a name of a party who exists>\n"; //to what party
					if (j != PARTY_NOT_FOUND)
					{
						cin.ignore();
					}
					cin.getline(partyName, MAX_LEN);
					j = findParty(partyList, pLogSize, partyName);//party exist?
				} while (j == PARTY_NOT_FOUND);

				while (ballotList[k]->getSerialNum() != cBallotNum) //We keep the index of the right ballot 
				{
					k++;
				}

				ballotList[k]->addVoteToParty(j);//add the vote to the party in the correct ballot.
				ballotList[k]->setNumOfVotes(ballotList[k]->getNumOfVotes() + 1);
				ballotList[k]->setVotingPercentage(ballotList[k]->getNumOfVotes(), ballotList[k]->getNumOfVoters());
			}
		}

	}
}

//This function checks if citizen choose a valid ballot number
bool ElectionRound::isValidBallot(int age, bool isIsolted, int ballotNum)
{
	int ballotType;
	if (isIsolted == true && 18 <= age && age <= 21) //Citizens who should be assigned to a corona-military ballot
		ballotType = 3;
	else if (18 <= age && age <= 21) //Citizens who should be assigned to military ballot
		ballotType = 2;
	else if (isIsolted == true) //Citizens who should be assigned to a corona ballot
		ballotType = 1;
	else //The citizen have no special attributes - he should be assigned to a regular ballot
		ballotType = 0;

	for (int i = 0; i < bLogSize; i++) //We loop over all the ballots and search for ballots who match the type of ballot the citizen can be assigned to
	{
		if (ballotList[i]->getType() == (Ballot::eType)ballotType
			&& ballotList[i]->getSerialNum() == ballotNum)
			return true;
	}
	return false; //We got to the end of the loop and the ballot type of the new citizen didn't match a ballot of the relevant type
}


const ElectionRound& ElectionRound:: operator+=(Citizen& citizen)
{

	if (checkIfIdExists(citizen.getId(), citizenNote, cLogSize)) //If the id of the new citizen already exists in the system return false
	{
		cout << "\nThe Id num you entered for the citizen alreay exist.\nThe citizen wasn't added to the voters note.\n";
		return *this;
	}

	//Add citizen to the citizen list
	if (cLogSize == cPhySize)//the citizen array is full?
	{
		cPhySize *= 2;
		citizenNote = reallocCitizenArray(citizenNote, cLogSize, cPhySize);//make it bigger.
	}

	Contestant* tempCont = dynamic_cast<Contestant*>(&citizen);
	if (!tempCont) //If he is not a contestant we check if he is a citizen of a soldier
	{
		Soldier* tempSold = dynamic_cast<Soldier*>(&citizen);
		if (!tempSold) //if he is not a soldier, we add him as regular citizen
			citizenNote[cLogSize] = new Citizen(citizen);//placement
		else //he is a soldier - we add him as soldier
			citizenNote[cLogSize] = new Soldier(*tempSold);
	}
	else // he is a contestant - we add him as a contestant
		citizenNote[cLogSize] = new Contestant(*tempCont);//placement

	cLogSize++; //We increase the size of the citizen note

	int serialNum = citizen.getBallotNum();//get the ballot of the citizen.
	for (int i = 0; i < bLogSize; i++)
	{
		if (serialNum == ballotList[i]->getSerialNum())
		{
			ballotList[i]->addVoter(citizen);//add the citizen to the correct ballot.
		}
	}
	return *this;
}


/*
const ElectionRound& ElectionRound:: operator+=(const Citizen& citizen)
{
	Citizen newCitizen(citizen);//copy c'tor

	if (checkIfIdExists(newCitizen.getId(), citizenNote, cLogSize)) //If the id of the new citizen already exists in the system return false
	{
		cout << "\nThe Id num you entered for the citizen alreay exist.\nThe citizen wasn't added to the voters note.\n";
		return *this;
	}

	//Add citizen to the citizen list
	if (cLogSize == cPhySize)//the citizen array is full?
	{
		cPhySize *= 2;
		citizenNote = reallocCitizenArray(citizenNote, cLogSize, cPhySize);//make it bigger.
	}

	citizenNote[cLogSize] = new Citizen(newCitizen);//placement
	cLogSize++;

	int serialNum = newCitizen.getBallotNum();//get the ballot of the citizen.
	for (int i = 0; i < bLogSize; i++)
	{
		if (serialNum == ballotList[i]->getSerialNum())
		{
			ballotList[i]->addVoter(newCitizen);//add the citizen to the correct ballot.
		}
	}
	return *this;
}

const ElectionRound& ElectionRound:: operator+=(const Contestant& citizen)
{
	Contestant newCitizen(citizen);//copy c'tor

	if (checkIfIdExists(newCitizen.getId(), citizenNote, cLogSize))
	{//If the id of the new citizen already exists in the system return false.
		cout << "\nThe Id num you entered for the citizen alreay exist."
			<< "\nThe citizen wasn't added to the voters note.\n";
	}
	else
	{
		//Add Contestant to the citizen list
		if (cLogSize == cPhySize)//the citizen array is full?
		{
			cPhySize *= 2;
			citizenNote = reallocCitizenArray(citizenNote, cLogSize, cPhySize);//make it bigger.
		}

		citizenNote[cLogSize] = new Contestant(newCitizen);//placement
		cLogSize++;

		int serialNum = newCitizen.getBallotNum();//get the ballot of the citizen.
		for (int i = 0; i < bLogSize; i++)
		{
			if (serialNum == ballotList[i]->getSerialNum())
			{
				ballotList[i]->addVoter(newCitizen);//add the citizen to the correct ballot.
			}
		}
		int index;
		for (index = 0; index < pLogSize; index++)
		{
			if (strcmp(partyList[index]->getName(), newCitizen.getPartyName()) == 0)
			{
				break;
			}
		}
		partyList[index]->addContestant(newCitizen);
	}

	return *this;
}
*/

//This function prints all relevant ballots for a person
void ElectionRound::showRelevantBallots(int age, bool isIsolated)
{
	int ballotType;

	if (isIsolated == true && (18 <= age && age <= 21)) //Citizens who should be assigned to a corona-military ballot
		ballotType = 3;
	else if (18 <= age && age <= 21) //Citizens who should be assigned to military ballot
		ballotType = 2;
	else if (isIsolated == true) //Citizens who should be assigned to a corona ballot
		ballotType = 1;
	else //The citizen have no special attributes - he should be assigned to a regular ballot
		ballotType = 0;

	for (int i = 0; i < bLogSize; i++) //We loop over all the ballots and search for ballots who match the type of ballot the citizen can be assigned to
	{
		if (ballotList[i]->getType() == (Ballot::eType)ballotType)
			cout << ballotList[i]->getSerialNum() << " ";
	}
	cout << endl;
}

void ElectionRound::showElectionResults() const
//This function shows the election day results.
{
	int* results = new int[pLogSize];//array of the results.

	cout << "\n\nElections results that took place at " << electionDate.getMonth() << "/" << electionDate.getYear() << ":\n";
	cout << "--------------------------------------------\n";
	for (int i = 0; i < pLogSize; i++)//make the results array all zeros.
	{
		results[i] = 0;
	}
	for (int i = 0; i < bLogSize; i++)//for each ballot:
	{
		cout << "In ballot #" << ballotList[i]->getSerialNum() << ":" << endl;
		cout << "-------------\n";
		cout << "Voting percentage is: " << ballotList[i]->getVotingPercentage() << endl;//print voting percentage
		for (int j = 0; j < pLogSize; j++)//print the number of votes for each party:
		{
			char* name = ballotList[i]->getPartyList()[j]->getParty().getName();
			int votes = (ballotList[i]->getPartyList())[j]->getNumOfVoters();
			cout << "Party: " << name << " recieved " << votes << " votes. \n";
			results[j] += votes;//add the number of votes in this ballot, to the total sum of votes.
		}
		cout << endl;
	}
	cout << "\nThe final results are:" << endl;
	cout << "----------------------\n";
	for (int i = 0; i < pLogSize; i++)//for each party, prints the final results:
	{
		cout << "Party: " << partyList[i]->getName() << " recieved "
			<< results[i] << " votes." << endl;
	}
	delete[] results;//free memory.
}

void ElectionRound::showBallots() const
//This function prints all the ballots.
{
	cout << "The ballots are:" << endl;
	for (int i = 0; i < bLogSize; i++)
	{
		ballotList[i]->show();
	}
}

void ElectionRound::showCitizens() const
//This function prints all the citizens.
{
	cout << "The voters note is:" << endl;
	cout << "-------------------\n";
	for (int i = 0; i < cLogSize; i++)
	{
		cout << "Voter #" << i + 1 << " is: " << endl;
		cout << "-----------" << endl;
		citizenNote[i]->show();
		cout << endl;
	}
}

void ElectionRound::showParties() const
//This function prints all the parties.
{
	cout << "The parties are:" << endl;
	for (int i = 0; i < pLogSize; i++)
	{
		cout << "-----------------\n";
		partyList[i]->show();
	}
}

ElectionRound::~ElectionRound()
//D'tor - This function deallocate all of the used memory
{
	delete[] citizenNote;//free citizen array.
	delete[] partyList;//free party array.
	delete[] ballotList;//free ballot array.
}