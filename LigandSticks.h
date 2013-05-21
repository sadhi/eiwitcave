#pragma once
#include "LigandStick.h"
#include "Atom.h"
#include <vector>

using namespace std;
class cLigandSticks
{
public:
	cLigandSticks(void);
	~cLigandSticks(void);

	void addLigandStick(string);
	void addLocations(vector<cAtom*>, vector<cAtom*>);

	vector<cLigandStick*> getLigandSticks(void);

	void draw(void);



private:
	vector<cLigandStick*> ligandSticks;
};

