#include "MarioSwitchMap.h"

void CMarioSwitchMap::runLeft()
{
	if ((x == 148 && y == 4)|| (x == 100&& y == 50)|| (x == 185&& y == 4)|| (x == 230&& y == 4)|| (x == 230&& y == 50))
	{
		x -= 3;
		vx = -0.12f;
		vy = 0;
	}
}
void CMarioSwitchMap::runRight()
{
	if ((x == 50 && y == 50)|| (x == 100 && y == 4)|| (x == 148 && y == 4)|| (x == 185 && y == 4)|| (x == 185 && y == 50))
	{
		x += 3;
		vx = 0.12f;
		vy = 0;
	}
}
void CMarioSwitchMap::runUp()
{
	if ((x == 100 && y == 50) || (x == 185 && y == 50))
	{
		vy = -0.12f;
		vx = 0;
	}
}


void CMarioSwitchMap::runDown()
{
	if ((x == 100 && y == 4) || (x == 185 && y == 4))
	{
		vy = 0.12f;
		vx = 0;
	}
}

void CMarioSwitchMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	first = false;
	second = false;
	fourth = false;

	int xx = (int)x;
	int yy = (int)y;
	

	if (vx > 0)
	{
		
		if (y == 50)
		{
			if (xx >= 100&& xx<=120)
			{
				x = 100;
				vx = 0;
			}
			if (xx >= 230)
			{
				x = 230;
				vx = 0;
			}
		}
		if (y == 4)
		{
			if (xx >= 148&& xx <=149)
			{
				x = 148;
				vx = 0;
			}
			if (xx >= 185&& xx <=187)
			{
				x = 185;
				vx = 0;
			}
			if (xx >= 230)
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
				if (xx <= 50)
				{
					x = 50;
					vx = 0;
				}
				if (xx <= 185&& xx >=130)
				{
					x = 185;
					vx = 0;
				}
			}
			if (y == 4)
			{
				if (xx <= 185&& xx >=183)
				{
					x = 185;
					vx = 0;
				}
				if (xx <= 148&& xx >=146)
				{
					x = 148;
					vx = 0;
				}
				if (xx <= 100)
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
	CGameObject::Update(dt);
	x += dx;
	y += dy;
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