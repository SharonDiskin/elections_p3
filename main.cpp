/*
This project was made by:
Sharon Diskin, ID 205379993.
Yossi Daniels, ID 204323299.
Last update: 3/6/2020
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "electionround.h"

using namespace std;
const int MAX_LEN = 100;

//Prototypes

void getCitizenInfo(ElectionRound& elections, int& id, Date& bDay, int& ballotNum, bool& isIsolated, char& ans);
int calcAge(Date electionDate, Date birthdate);
void createCitizen(ElectionRound& elections, int opt);
Ballot createBallot();
Party createParty();
void menu(ElectionRound& election);

//MAIN FUNCTION
int main()
{
	int day, month, year;

	cout << "-----------------------Elections----------------------------\n";
	cout << "Please enter date of the elections:\n";
	cin >> day >> month >> year;

	Date date(day, month, year);

	ElectionRound election(date);

	//insert hard coded information:
	Date d1(15, 12, 1955);
	Date d2(27, 2, 1975);
	Date d3(23, 1, 1980);
	Date d4(1, 7, 1957);
	Date d5(6, 6, 1966);
	Date d6(6, 1, 1970);
	Date d7(9, 11, 1990);
	Date d8(6, 1, 2000);
	Date d9(19, 4, 1995);
	Adress a1("Albert", 11, "Ashdod");
	Adress a2("Hakishon", 55, "Yaffo");
	Adress a3("Hertzel", 15, "Tel Aviv");
	Adress a4("Nof", 15, "Ashkelon");
	Adress a5("Salame", 16, "Haifa");
	Ballot b1(a1, (Ballot::eType)0);
	Ballot b2(a2, (Ballot::eType)0);
	Ballot b3(a3, (Ballot::eType)1);
	Ballot b4(a4, (Ballot::eType)2);
	Ballot b5(a5, (Ballot::eType)3);
	Contestant c1("Halikud", "Rubi Rivlin", d1, 205379993, 1, 1);
	Contestant c2("Halikud", "Yair Lapid", d2, 301742599, 1, 1);
	Contestant c3("Halikud", "Yonit Levi", d3, 204323299, 1, 0);
	Contestant c4("Meretz", "Dani Kushmaru", d4, 924593221, 1, 0);
	Contestant c5("Yemina", "John Lenon", d5, 316567262, 2, 0);
	Contestant c6("Meretz", "Harry Potter", d6, 311550230, 2, 0);
	Party p1("Halikud", (Party::eStream)1, d7);
	Party p2("Meretz", (Party::eStream)1, d8);
	Party p3("Yemina", (Party::eStream)1, d9);
	election.addNewBallot(b1);
	election.addNewBallot(b2);
	election.addNewBallot(b3);
	election.addNewBallot(b4);
	election.addNewBallot(b5);
	election.addNewParty(p1);
	election.addNewParty(p2);
	election.addNewParty(p3);
	election += c1;
	election += c2;
	election += c3;
	election += c4;
	election += c5;
	election += c6;
	//end of hard coded information.

	menu(election);

}

void getCitizenInfo(ElectionRound& elections, int& id, Date& bDay,
	int& ballotNum, bool& isIsolated, char& ans)
{
	cout << "Id: ";
	cin >> id;//get the ID.
	cout << "Date of birth: ";
	cin >> bDay;//get the date.
	cout << "Is Isolated? y/n ";
	cin >> ans;
	ans == 'y' ? isIsolated = true : isIsolated = false;

	do {//until the citizen enters a suitable ballot number.
		cout << "Please enter ballot number. "
			<< "Ballot number can be one of the following ballots"
			<< " according to your age and isolation status: ";
		elections.showRelevantBallots(calcAge(elections.getElecationDate(), bDay), isIsolated);
		cin >> ballotNum;
	} while (!elections.isValidBallot(calcAge(elections.getElecationDate(), bDay), isIsolated, ballotNum));
}

int calcAge(Date electionDate, Date birthdate)
{
	// days of every month 
	int month[] = { 31, 28, 31, 30, 31, 30, 31,	31, 30, 31, 30, 31 };
	int currDay = electionDate.getDay();
	int currMonth = electionDate.getMonth();
	int currYear = electionDate.getYear();

	// if birth date is greater then current birth 
	// month then do not count this month and add 30  
	// to the date so as to subtract the date and 
	// get the remaining days 
	if (birthdate.getDay()>currDay) {
		currDay = currDay + month[birthdate.getDay() - 1];
		currMonth -= 1;
	}

	// if birth month exceeds current month, then do 
	// not count this year and add 12 to the month so 
	// that we can subtract and find out the difference 
	if (birthdate.getMonth() > currMonth) {
		currYear -= 1;
	}

	return currYear - birthdate.getYear(); //We return the age (in years) of the citizen
}

void createCitizen(ElectionRound& elections, int opt)
//This function create and return a new citizen.
{
	char name[MAX_LEN];
	int id;
	Date bDay;
	int ballotNum;
	bool isIsolated;
	char ans;
	
	int age;
	//get citizen information:
	cout << "--------Add citizen--------\nPlease enter new citizen info:\n";
	cout << "Name: ";
	cin.ignore();
	cin.getline(name, MAX_LEN);//get the name.
	getCitizenInfo(elections, id, bDay, ballotNum, isIsolated, ans);
	age = calcAge(elections.getElecationDate(), bDay);

	if (18 <= age && age <= 21) //If the citizen if a soldier - create a new soldier
	{
		char UnitName[MAX_LEN];
		cout << "According to your age, you are a soldier. Please enter unit name\n";
		cin.ignore(); //clean buffer.
		cin >> UnitName;
		Soldier soldier(UnitName,name, bDay, id, ballotNum, isIsolated);
		elections += soldier;
	}
	else if (opt == 2)//If the citizen if a regular citizen - create a new citizen
	{
		Citizen citizen(name, bDay, id, ballotNum, isIsolated);
		elections += citizen;//add citizen.
	}
	else if (opt == 4)//If the citizen if a contestant - create a new contestant
	{
		char PartyName[MAX_LEN];
		cout << "Enter party name: ";
		cin.ignore();//clean buffer.
		cin.getline(PartyName, MAX_LEN);//get party name.
		while (elections.findParty(elections.getPartyList(), elections.getPLogSize(), PartyName) == -1)
		{//until the party the citizen entered exist.
			cout << "The Party you entered doesn't exist in the party list. "
				<< "Try again.\nEnter party name: ";
			cin.getline(PartyName, MAX_LEN);//get party name.
		}
		Contestant contestant(PartyName, name, bDay, id, ballotNum, isIsolated);
		elections += contestant;//add contestant.
	}
}

Ballot createBallot()
//This function create and return a new ballot.
{
	char street[MAX_LEN];
	int stNum;
	char city[MAX_LEN];
	int type;
	cout << "--------Add ballot--------\n";

	cout << "Please enter ballot location : \nStreet name : ";
	cin.ignore();//flush the buffer for getline function.
	cin.getline(street, MAX_LEN);
	cout << "Street number: ";
	cin >> stNum;
	cout << "City name: ";
	cin.ignore();//flush the buffer for getline function.
	cin.getline(city, MAX_LEN);
	cout << "Please enter Ballot type:\nFor regular ballot enter 0\nFor Corona ballot enter 1\nFor military ballot enter 2\nFor military corona ballot enter3\n";
	cin >> type;
	Adress adress(street, stNum, city);
	Ballot ballot(adress, (Ballot::eType) type);
	return ballot;
}

Party createParty()
//This function create and returns a new party.
{
	char name[MAX_LEN];
	int stream;
	Date creationDate;

	cout << "--------Add party--------\n";

	//get party information
	cout << "Please enter new party information:\n";
	cout << "Party name: ";
	cin.ignore();
	cin.getline(name, MAX_LEN);//get party name.
	cout << "Creation date: ";
	cin >> creationDate;//get date.
	cout << "Party stream:\nFor left enter 0\nFor center enter 1\nFor right enter 2\n";
	cin >> stream;//get the party stream.

	Party party(name, (Party::eStream)stream, creationDate);
	return party;
}

void menu(ElectionRound& election)
//This function create the menu for this election round.
{
	int choice;
	bool fContinue = true;
	bool res, isElectionNotOver = true;

	do {
		cout << "Please enter your choice\n";
		cout << "Add ballot --------------------------------------> 1\n";
		cout << "Add citizen -------------------------------------> 2\n";
		cout << "Add party ---------------------------------------> 3\n";
		cout << "Add a contestant on a behalf of a party ---------> 4\n";
		cout << "Show all ballots --------------------------------> 5\n";
		cout << "Show all citizens -------------------------------> 6\n";
		cout << "Show all parties --------------------------------> 7\n";
		cout << "Elections ---------------------------------------> 8\n";
		cout << "Show elections results --------------------------> 9\n";
		cout << "Exit menu --------------------------------------> 10\n";
		cin >> choice;

		switch (choice)
		{
		case 1://add new ballot.
			if (isElectionNotOver)
			{
				election.addNewBallot(createBallot());
			}
			else
				cout << "The election is over. Thank you.";
			break;

		case 2://add new citizen.
			if (isElectionNotOver)
			{
				createCitizen(election, 2);
			}
			else
				cout << "The election is over. Thank you.";
			break;

		case 3://add new party.
			if (isElectionNotOver)
			{
				election.addNewParty(createParty());
			}
			else
				cout << "The election is over. Thank you.";
			break;

		case 4://add new citizen and make him contestant to a given party.
			if (isElectionNotOver)
			{
				cout << "--------Add contestant-----\n";
				createCitizen(election, 4);
			}
			else
				cout << "The election is over. Thank you.";
			break;

		case 5://print all ballots.
			election.showBallots();
			break;

		case 6://print all citizens.
			election.showCitizens();
			break;

		case 7://print all parties.
			election.showParties();
			break;

		case 8://election day menu.
			if (isElectionNotOver)
			{
				isElectionNotOver = false;
				election.electionDay();
			}
			else
			{
				cout << "The election is over. Thank you.";
			}
			break;

		case 9://print the election day result.
			election.showElectionResults();
			break;

		case 10://ending the program.
			cout << "Bye bye!\n";
			fContinue = false;
		}

		cout << "\n\n";

	} while (fContinue);

}