#include "VisibilityCheckBox.h"


VisibilityCheckBox::VisibilityCheckBox(bool value, bool v) : CheckBox(value)
{
	visible = v;
}

VisibilityCheckBox::VisibilityCheckBox(bool value, bool v, fastdelegate::FastDelegate0<> onclick) : CheckBox(v, onclick)
{
	visible = v;
}

VisibilityCheckBox::~VisibilityCheckBox(void)
{
}

void VisibilityCheckBox::render(float depth)
{
	if(visible)
	{
		CheckBox::render(depth);
	}
	else
	{
	}
}

void VisibilityCheckBox::setVisibility(bool v)
{
	visible = v;
}

bool VisibilityCheckBox::getVisibility()
{
	return visible;
}