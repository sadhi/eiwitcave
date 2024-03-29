#pragma once
#include <cavelib/guipanel.h>
#include <cavelib/Components/Button.h>
#include "VisibilityLabel.h"
#include "VisibilitySlider.h"
#include <cavelib/Components/CheckBox.h>
#include "Atom.h"
#include <vector>

class EnzymePanel :
	public GUIPanel
{
public:
	EnzymePanel(int, std::vector<cAtom*>);
	~EnzymePanel(void);

	void check();
	std::vector<Label*> labels;
	std::vector<CheckBox*> atomBoxes;
	std::vector<cAtom*> Atoms;
};

