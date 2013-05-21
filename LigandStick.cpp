#include "LigandStick.h"


cLigandStick::cLigandStick(void)
{
}

cLigandStick::cLigandStick(string* line)
{
	int bondedSerialNumbers[4] = {0};
	init(line);
}

cLigandStick::~cLigandStick(void)
{
}

void cLigandStick::init(string* line)
{
	//Scanning serial number of stick.
	string serial = line->substr(6,5);
	sscanf_s(serial.c_str(), "%i", &serialNumber);

	for(int i = 0; i < 4; i++)
	{
		bondedSerialNumbers[i] = 0;
		string bondedSerial = line->substr(11+(i*5), 5);
		sscanf_s(bondedSerial.c_str(), "%i", &bondedSerialNumbers[i]);
	}
}
