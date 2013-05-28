#include "VisibilitySlider.h"


VisibilitySlider::VisibilitySlider(float min, float max, float value, bool v) : Slider(min, max, value)
{
	visible = v;
}


VisibilitySlider::~VisibilitySlider(void)
{
}

void VisibilitySlider::render(float depth)
{
	if(visible)
	{
		Slider::render(depth);
	}
	else
	{
	}
}

void VisibilitySlider::setVisibility(bool v)
{
	visible = v;
}

bool VisibilitySlider::getVisibility()
{
	return visible;
}