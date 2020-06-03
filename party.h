#ifndef __PARTY
#define __PARTY

#include "contestant.h"

class Party
{
public:
	enum class eStream { Left, Right, Center };

private:
	char* name; //Party name
	eStream theStream;
	Date creationDate;
	int logSize = 0, phySize = 1; //logical and physical size for the array contestant array
	Contestant** contestants;

public:

	Party(); //Default c'tor
	Party(const char* name, Party::eStream stream, const Date& date); //C'tor
	Party(const Party& other); //copy C'tor
	Party(Party&& other);//Move c'tor

	//Get methods
	char* getName() const;
	eStream getStream() const;
	const Date& getCreationDate() const;
	Contestant** getContestants() const;

	//Set methods
	bool setName(const char* str);
	bool setStream(Party::eStream s);
	bool setCreationDate(const Date& date);

	void addContestant(const Contestant& citizen);

	const Party& operator=(const Party& other);
	bool operator>(const Party& other) const;

	void show() const;

	~Party(); //D'tor

};
#endif // !__PARTY