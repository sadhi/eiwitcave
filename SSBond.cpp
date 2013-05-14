#include "SSBond.h"


cSSBond::cSSBond(void)
{
}

cSSBond::cSSBond(string* line)
{
	init(line);
}


cSSBond::~cSSBond(void)
{
}

void cSSBond::init(string* line)
{
	//int serialNumber;
	string serial = line->substr(7,3);
	sscanf_s(serial.c_str(), "%i", &serialNumber);

	//string residueName1;
	residueName1 =  line->substr(11,3);
	//char chainID1;
	chainID1 = line->substr(15,1)[0];
	//int residueSeqNumber1;
	string residueSeqNumber1String = line->substr(17,4);
	sscanf_s(residueSeqNumber1String.c_str(), "%i", &residueSeqNumber1);
	//char insertionCode1;
	insertionCode1 = line->substr(21,1)[0];

	//string residueName2;
	residueName2 =  line->substr(25,3);
	//char chainID2;
	chainID2 = line->substr(29,1)[0];
	//int residueSeqNumber2;
	string residueSeqNumber2String = line->substr(31,4);
	sscanf_s(residueSeqNumber2String.c_str(), "%i", &residueSeqNumber2);
	//char insertionCode2;
	insertionCode2 = line->substr(35,1)[0];

	//string symmetry1;
	symmetry1 =  line->substr(59,6);
	//string symmetry2;
	symmetry2 =  line->substr(66,6);

	//float bondDistance;
	string bondDistanceString = line->substr(73,5);
	sscanf_s(bondDistanceString.c_str(), "%f", &bondDistance);
}