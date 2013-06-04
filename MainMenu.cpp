#include "MainMenu.h"
#include <cavelib/LayoutManagers/TableLayout.h>
#include <cavelib/LayoutManagers/FlowLayout.h>
#include <cavelib/Components/Panel.h>
#include <cavelib/Components/Label.h>
#include <CaveLib/Components/Button.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


MainMenu::MainMenu(void) : GUIPanel("")
{
	demoPanel = NULL;
	rootPanel = new Panel(new TableLayoutManager(1));
	Panel* p = new Panel(new TableLayoutManager(3));
	Panel* extraPanel = new Panel(new TableLayoutManager(2));
	rootPanel->add(p);
	rootPanel->add(extraPanel);
	ModeAtomInfo = ModeMeasureDistance = false;
	p->add(new Label("Model"));
	p->add(new Label("Info"));
	p->add(new Label("View"));

	//first line of 3 buttons
	p->add(moveButton = new Button("Move", fastdelegate::MakeDelegate(this, &MainMenu::setMoveMode)));
	p->add(new Button("Atom info", fastdelegate::MakeDelegate(this, &MainMenu::setAtomMode)));
	p->add(new Button("Zoom", fastdelegate::MakeDelegate(this, &MainMenu::setZoomMode)));
	//second line of 3 buttons
	p->add(new Button("Rotate", fastdelegate::MakeDelegate(this, &MainMenu::setRotationMode)));
	p->add(new Button("Distance", fastdelegate::MakeDelegate(this, &MainMenu::setMeasureMode)));
	p->add(centrateButton = new Button("Centrate", fastdelegate::MakeDelegate(this, &MainMenu::centrate)));

	//extraPanel has items that extend function of the button
	//for example the button zoom causes a slider to appear for zooming in and out
	extraPanel->add(rotateL = new VisibilityLabel("Rotation: ",false));
	extraPanel->add(rotateS = new VisibilitySlider(0,360,0,false));
	extraPanel->add(zoomL = new VisibilityLabel("Zoom: ",false));
	extraPanel->add(zoomS = new VisibilitySlider(0,35,0,false));

	rootPanel->setFont(font);
	rootPanel->reposition(0,0,0.8f,1.5f);

	renderMatrix = glm::mat4();
	renderMatrix = glm::translate(renderMatrix, glm::vec3(-1.5,-1,-0));
	renderMatrix = glm::rotate(renderMatrix, 90.0f, glm::vec3(0,1,0));
}


MainMenu::~MainMenu(void)
{
}

void MainMenu::setRotationMode()
{
	ModeAtomInfo = false;
	ModeMeasureDistance = false;
	rotateL->setVisibility(true);
	rotateS->setVisibility(true);
	zoomL->setVisibility(false);
	zoomS->setVisibility(false);
}

void MainMenu::setZoomMode()
{
	ModeAtomInfo = false;
	ModeMeasureDistance = false;
	rotateL->setVisibility(false);
	rotateS->setVisibility(false);
	zoomL->setVisibility(true);
	zoomS->setVisibility(true);
}

void MainMenu::setMeasureMode()
{
	ModeAtomInfo = false;
	ModeMeasureDistance = true;
	rotateL->setVisibility(false);
	rotateS->setVisibility(false);
	zoomL->setVisibility(false);
	zoomS->setVisibility(false);
}

void MainMenu::setAtomMode()
{
	ModeAtomInfo = true;
	ModeMeasureDistance = false;
	rotateL->setVisibility(false);
	rotateS->setVisibility(false);
	zoomL->setVisibility(false);
	zoomS->setVisibility(false);
}

void MainMenu::setMoveMode()
{
	ModeAtomInfo = false;
	ModeMeasureDistance = false;
	rotateL->setVisibility(false);
	rotateS->setVisibility(false);
	zoomL->setVisibility(false);
	zoomS->setVisibility(false);
}

void MainMenu::centrate()
{
	ModeAtomInfo = false;
	ModeMeasureDistance = false;
	rotateL->setVisibility(false);
	rotateS->setVisibility(false);
	zoomL->setVisibility(false);
	zoomS->setVisibility(false);
}