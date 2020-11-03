#include "Fire.h"

void CFire::Render()
{
	int ani = -1;
	if (nx = 1)
	{
		ani = FIRE_ANI_RIGHT;
	}
	else {
		ani = FIRE_ANI_LEFT;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	x += dx;
}

void CFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_HEIGHT;
	b = y + FIRE_BBOX_WIDTH;
}

