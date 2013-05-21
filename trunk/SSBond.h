#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class cSSBond
{
public:
	cSSBond(void);
	cSSBond(string* line);
	~cSSBond(void);

	int serialNumber;

	string residueName1;
	char chainID1;
	int residueSeqNumber1;
	char insertionCode1;

	string residueName2;
	char chainID2;
	int residueSeqNumber2;
	char insertionCode2;

	string symmetry1;
	string symmetry2;

	float bondDistance;

private:
	//functions
	void init(string* line);

};

