#include "VisibilityLabel.h"


VisibilityLabel::VisibilityLabel(std::string text , bool v) : Label(text)
{
	visible = v;
}


VisibilityLabel::~VisibilityLabel(void)
{
}

void VisibilityLabel::render(float depth)
{
	if(visible)
	{
		Label::render(depth);
	}
	else
	{
	}
}

void VisibilityLabel::setVisibility(bool v)
{
	visible = v;
}

bool VisibilityLabel::getVisibility()
{
	return visible;
}