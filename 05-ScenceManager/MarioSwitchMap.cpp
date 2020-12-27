#include "MarioSwitchMap.h"

void CMarioSwitchMap::runLeft()
{
	if (x == 117 && y == 58)
	{
		vx = -0.08f;
		vy = 0;
	}
}
void CMarioSwitchMap::runRight()
{
	if (x == 86 && y == 58)
	{
		vx = 0.08f;
		vy = 0;
	}
}
void CMarioSwitchMap::runUp()
{
	if (x == 117 && y == 58)
	{
		vy = -0.08f;
		vx = 0;
	}
}


void CMarioSwitchMap::runDown()
{
	if (x == 117 && y == 27)
	{
		vy = 0.08f;
		vx = 0;
	}
}

void CMarioSwitchMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	if (vx > 0)
	{
		if (x >= 117)
		{
			x = 117;
			vx = 0;
		}
	}
	else
	{
		if (vx < 0)
		{
			if (x <= 86)
			{
				x = 86;
				vx = 0;
			}
		}
	}
	if (vy > 0)
	{
		if (y >= 58)
		{
			y = 58;
			vy = 0;
		}
	}
	else
	{
		if (vy < 0)
		{
			if (y <= 27)
			{
				y = 27;
				vy = 0;
			}
		}
	}


	if (x == 117 && y == 27)
	{
		first = true;
	}
	else
	{
		first = false;
	}
}

void CMarioSwitchMap::Render()
{
	animation_set->at(0)->Render(x, y);
}
void CMarioSwitchMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}