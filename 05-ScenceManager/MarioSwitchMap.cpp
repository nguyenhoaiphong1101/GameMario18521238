#include "MarioSwitchMap.h"

void CMarioSwitchMap::runLeft()
{
	if (x == 117)
	{
		if(y==58 )
		for (int i = 0; i < KHOANGCACH_X; i++)
		{
			x--;
			animation_set->at(0)->Render(x, y);
		}
	}
	
}
void CMarioSwitchMap::runRight()
{
	if (x == 117)
	{
		if(y!=58)
		for (int i = 0; i < KHOANGCACH_X; i++)
		{
			x++;
			animation_set->at(0)->Render(x, y);
		}
	}
	else
	{
		for (int i = 0; i < KHOANGCACH_X; i++)
		{
			x++;
			animation_set->at(0)->Render(x, y);
		}
	}
}
void CMarioSwitchMap::runUp()
{
	if (x != 86)
	{
		if(y>27)
		for (int i = 0; i < KHOANGCACH_Y; i++)
		{
			y--;
			animation_set->at(0)->Render(x, y);
		}
	}
	
}void CMarioSwitchMap::runDown()
{
	if (x != 86)
	{
		if(y!=58)
		for (int i = 0; i < KHOANGCACH_Y; i++)
		{
			y++;
			animation_set->at(0)->Render(x, y);
		}
	}
	
}

void CMarioSwitchMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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