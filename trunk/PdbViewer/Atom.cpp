#include "Atom.h"

#include <string>
#include <stdio.h>


cAtom::cAtom(void)
{
}

cAtom::cAtom(string* line, int _chainNumber)
{
	isPartOfLigand = false;
	chainNumber = _chainNumber;
	charge = 0;
	init(line);
}

cAtom::~cAtom(void)
{
}

void cAtom::init(string* line)
{//might be 31 ect. also might be 8 instead of 7
	
	string serial = line->substr(6,5);
	sscanf_s(serial.c_str(), "%i", &serialNumber);

	atomName =  line->substr(13,3);
	residueName = line->substr(17,3);
	string residueID = line->substr(22,4);
	sscanf_s(residueID.c_str(), "%i", &residueSeqNumber);
	
	string x = line->substr(30,7);
	string y = line->substr(38,7);
	string z = line->substr(46,7);

	location = new Vec3();
	sscanf_s(x.c_str(), "%f", &location->X);
	sscanf_s(y.c_str(), "%f", &location->Y);
	sscanf_s(z.c_str(), "%f", &location->Z);

	string temperature = line->substr(60,5);
	sscanf_s(temperature.c_str(), "%f", &tempuratureFactor);
	
	element = line->substr(76,2);

	string chargeStr = line->substr(78,2);
	sscanf_s(chargeStr.c_str(), "%d", &charge);
}

