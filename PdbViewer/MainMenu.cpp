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
	rootPanel = new Panel(new TableLayoutManager(4));

	rootPanel->add(new Label("Camera"));
	rootPanel->add(new Label("Selection"));
	rootPanel->add(new Label("Measure"));
	rootPanel->add(new Label("View"));

	rootPanel->add(new Button("a"));
	rootPanel->add(new Button("b"));
	rootPanel->add(new Button("c"));
	rootPanel->add(new Button("d"));
	rootPanel->add(new Button("e"));
	rootPanel->add(new Button("f"));
	rootPanel->add(new Button("g"));

	rootPanel->setFont(font);
	rootPanel->reposition(0,0,0.6f,0.9f);

	renderMatrix = glm::mat4();
	renderMatrix = glm::translate(renderMatrix, glm::vec3(-1.5,-0.6f,-0));
	renderMatrix = glm::rotate(renderMatrix, 90.0f, glm::vec3(0,1,0));
}


MainMenu::~MainMenu(void)
{
}
