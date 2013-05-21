#pragma once

#include <vector>
#include "Atom.h"
#include "ObjModel.h"

using namespace std;

class cSequence
{
public:
	//constructors
	cSequence(cAtom* atom);
	~cSequence(void);

	//functions
	string GetSequenceName(void);
	int GetSeqNumber(void);
	void AddAtom(cAtom* _atom);
	void CreateVBO(void);
	void Draw(void);

private:
	//functions
	void init(cAtom* atom);

	//variables
	string seqName;
	int seqNumber;
	vector<cAtom*> atoms;
	ObjModel* sequenceModel;
};

