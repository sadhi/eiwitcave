#include "MainMenu.h"
#include <cavelib/LayoutManagers/TableLayout.h>
#include <cavelib/LayoutManagers/FlowLayout.h>
#include <cavelib/Components/Panel.h>
#include <cavelib/Components/Label.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class RotateButton : public Button
	{
		MainMenu *mm;

	public:
		RotateButton(MainMenu *menu) : Button("Rotate")
		{
			this->mm = menu;
		}

		void click()
		{
			mm->ModeAtomInfo = false;
			mm->ModeMeasureDistance = false;
			mm->rotateL->setVisibility(true);
			mm->rotateS->setVisibility(true);
			mm->zoomL->setVisibility(false);
			mm->zoomS->setVisibility(false);
		}
	};

class ZoomButton : public Button
	{
		MainMenu *mm;

	public:
		ZoomButton(MainMenu *menu) : Button("Zoom")
		{
			this->mm = menu;
		}

		void click()
		{
			mm->ModeAtomInfo = false;
			mm->ModeMeasureDistance = false;
			mm->rotateL->setVisibility(false);
			mm->rotateS->setVisibility(false);
			mm->zoomL->setVisibility(true);
			mm->zoomS->setVisibility(true);
		}
	};

class MeasureButton : public Button
	{
		MainMenu *mm;

	public:
		MeasureButton(MainMenu *menu) : Button("Distance")
		{
			this->mm = menu;
		}

		void click()
		{
			mm->ModeAtomInfo = false;
			mm->ModeMeasureDistance = true;
			mm->rotateL->setVisibility(false);
			mm->rotateS->setVisibility(false);
			mm->zoomL->setVisibility(false);
			mm->zoomS->setVisibility(false);
		}
	};

class AtomButton : public Button
	{
		MainMenu *mm;

	public:
		AtomButton(MainMenu *menu) : Button("Atom info")
		{
			this->mm = menu;
		}

		void click()
		{
			mm->ModeAtomInfo = true;
			mm->ModeMeasureDistance = false;
			mm->rotateL->setVisibility(false);
			mm->rotateS->setVisibility(false);
			mm->zoomL->setVisibility(false);
			mm->zoomS->setVisibility(false);
		}
	};

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
	p->add(moveButton = new Button("Move"));
	p->add(new AtomButton(this));
	p->add(new ZoomButton(this));
	//second line of 3 buttons
	p->add(new RotateButton(this));
	p->add(new MeasureButton(this));
	p->add(centrateButton = new Button("Centrate"));

	//extraPanel has items that extend function of the button
	//for example the button zoom causes a slider to appear for zooming in and out
	extraPanel->add(rotateL = new VisibilityLabel("Rotation: ",false));
	extraPanel->add(rotateS = new VisibilitySlider(0,360,0,false));
	extraPanel->add(zoomL = new VisibilityLabel("Zoom: ",false));
	extraPanel->add(zoomS = new VisibilitySlider(0,1000,0,false));

	rootPanel->setFont(font);
	rootPanel->reposition(0,0,0.8f,1.5f);

	renderMatrix = glm::mat4();
	renderMatrix = glm::translate(renderMatrix, glm::vec3(-1.5,-0.6f,-0));
	renderMatrix = glm::rotate(renderMatrix, 90.0f, glm::vec3(0,1,0));
}


MainMenu::~MainMenu(void)
{
}
