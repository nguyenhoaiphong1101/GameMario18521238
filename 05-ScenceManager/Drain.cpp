#include "Drain.h"

void CDrain::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CDrain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + DRAIN_BBOX_WIDTH;
	b = y + DRAIN_BBOX_HEIGHT;
}