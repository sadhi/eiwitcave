#pragma once
#include <CaveLib/GUIPanel.h>
#include <cavelib/Components/Button.h>
#include <cavelib/Components/CheckBox.h>

class MainMenu :
	public GUIPanel
{
	Panel* demoPanel;

public:
	MainMenu(void);
	~MainMenu(void);
};

