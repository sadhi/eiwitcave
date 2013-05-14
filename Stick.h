#pragma once

#include <iostream>
#include <string.h>
#include "Vec3.h"
#include <vector>
#include "Atom.h"

using namespace std;

class cStick
{
public:
	cStick(void);
	cStick(vector<cAtom*>);
	cStick(vector<cAtom*>, vector<cAtom*>);
	~cStick(void);

	vector<vector<Vec3*>> sticks;

	void draw(bool high);

private:
	//functions
	void init(vector<cAtom*>);
	void initH(vector<cAtom*>, vector<cAtom*>);
};

