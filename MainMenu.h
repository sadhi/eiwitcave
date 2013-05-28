#pragma once
#include <CaveLib/GUIPanel.h>
#include <cavelib/Components/Button.h>
#include "VisibilityLabel.h"
#include "VisibilitySlider.h"
#include <cavelib/Components/CheckBox.h>

class MainMenu :
	public GUIPanel
{
	Panel* demoPanel;

public:
	MainMenu(void);
	~MainMenu(void);

	//buttons
	Button* moveButton, *centrateButton;
	VisibilitySlider *rotateS, *zoomS;
	VisibilityLabel *rotateL, *zoomL;

	bool ModeAtomInfo, ModeMeasureDistance;
};
