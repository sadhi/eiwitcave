#include "MainMenu.h"
#include <cavelib/LayoutManagers/TableLayout.h>
#include <cavelib/LayoutManagers/FlowLayout.h>
#include <cavelib/Components/Panel.h>
#include <cavelib/Components/Label.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

MainMenu::MainMenu(void) : GUIPanel("")
{
	demoPanel = NULL;
	rootPanel = new Panel(new TableLayoutManager(1));
	Panel* p = new Panel(new TableLayoutManager(3));
	Panel* extraPanel = new Panel(new TableLayoutManager(2));
	rootPanel->add(p);

	p->add(new Label("Model"));
	p->add(new Label("Info"));
	p->add(new Label("View"));

	//first line of 3 buttons
	p->add(new Button("Move"));
	p->add(new Button("Atom info"));
	p->add(new Button("Zoom"));
	//second line of 3 buttons
	p->add(new Button("Rotate"));
	p->add(new Button("Distance"));
	p->add(new Button("Centrate"));

	rootPanel->setFont(font);
	rootPanel->reposition(0,0,0.6f,0.9f);

	renderMatrix = glm::mat4();
	renderMatrix = glm::translate(renderMatrix, glm::vec3(-1.5,-0.6f,-0));
	renderMatrix = glm::rotate(renderMatrix, 90.0f, glm::vec3(0,1,0));
}


MainMenu::~MainMenu(void)
{
}
