#pragma once
#include <CaveLib/GUIPanel.h>
class AtomPanel :
	public GUIPanel
{
public:
	std::string name, element, residueN ;
	int charge, chain, residueS;

	AtomPanel(void);
	~AtomPanel(void);
};

