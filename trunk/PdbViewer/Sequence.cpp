#include "Sequence.h"


cSequence::cSequence(cAtom* atom)
{
	init(atom);
}

cSequence::~cSequence(void)
{
}

string cSequence::GetSequenceName()
{
	return seqName;
}

int cSequence::GetSeqNumber()
{
	return seqNumber;
}

void cSequence::AddAtom(cAtom* _atom)
{
	atoms.push_back(_atom);
}

void cSequence::CreateVBO()
{
	sequenceModel = new ObjModel("data/pdbviewer/Models/AtomModel.obj");//, atoms);
}

void cSequence::Draw()
{
//	sequenceModel->vboDraw();
}

void cSequence::init(cAtom* atom)
{
	seqName = atom->residueName;
	seqNumber = atom->residueSeqNumber;
	AddAtom(atom);
}
