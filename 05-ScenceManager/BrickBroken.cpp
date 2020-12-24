#include "BrickBroken.h"

CBrickBroken::CBrickBroken()
{
	SetState(BRICK_BROKEN_STATE_SHOW);
}

void CBrickBroken::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == BRICK_BROKEN_STATE_SHOW)
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
	
}
void CBrickBroken::SetState(int state)
{
	CGameObject::SetState(state);
	
}
void CBrickBroken::Render()
{
	if (state == BRICK_BROKEN_STATE_SHOW)
		animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}