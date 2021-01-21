#include "MarioSwitchMap.h"

void CMarioSwitchMap::runLeft()
{
	if ((x == 148 && y == 4)|| (x == 100&& y == 50)|| (x == 185&& y == 4)|| (x == 230&& y == 4)|| (x == 230&& y == 50))
	{
		vx = -0.08f;
		vy = 0;
	}
}
void CMarioSwitchMap::runRight()
{
	if ((x == 50 && y == 50)|| (x == 100 && y == 4)|| (x == 148 && y == 4)|| (x == 185 && y == 4)|| (x == 185 && y == 50))
	{
		vx = 0.08f;
		vy = 0;
	}
}
void CMarioSwitchMap::runUp()
{
	if ((x == 100 && y == 50) || (x == 185 && y == 50))
	{
		vy = -0.08f;
		vx = 0;
	}
}


void CMarioSwitchMap::runDown()
{
	if ((x == 100 && y == 4) || (x == 185 && y == 4))
	{
		vy = 0.08f;
		vx = 0;
	}
}

void CMarioSwitchMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	first = false;
	second = false;
	fourth = false;
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	if (vx > 0)
	{
		
		if (y == 50)
		{
			if (x >= 100&&x<=120)
			{
				x = 100;
				vx = 0;
			}
			if (x >= 230)
			{
				x = 230;
				vx = 0;
			}
		}
		if (y == 4)
		{
			if (x >= 148&&x<=155)
			{
				x = 148;
				vx = 0;
			}
			if (x >= 185&&x<=195)
			{
				x = 185;
				vx = 0;
			}
			if (x >= 230)
			{
				x = 230;
				vx = 0;
			}
		}
	}
	else
	{
		if (vx < 0)
		{
			if (y == 50)
			{
				if (x <= 50)
				{
					x = 50;
					vx = 0;
				}
				if (x <= 185&&x>=130)
				{
					x = 185;
					vx = 0;
				}
			}
			if (y == 4)
			{
				if (x <= 185)
				{
					x = 185;
					vx = 0;
				}
				else if (x <= 148)
				{
					x = 148;
					vx = 0;
				}
				else if (x <= 100)
				{
					x = 100;
					vx = 0;
				}
			}
		}
	}
	if (vy > 0)
	{
		if (x == 100)
		{
			if (y >= 50)
			{
				y = 50;
				vy = 0;
			}
		}
		if (x == 185)
		{
			if (y >= 50)
			{
				y = 50;
				vy = 0;
			}
		}
	}
	else
	{
		if (vy < 0)
		{
			if (y <= 4)
			{
				y = 4;
				vy = 0;
			}
		}
	}


	if (x == 100 && y == 4)
	{
		first = true;
	}
	if (x == 185 && y == 4)
	{
		first = true;
	}
	if (x == 230 && y == 50)
	{
		fourth = true;
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