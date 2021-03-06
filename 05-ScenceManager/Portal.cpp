#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id )
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r - l + 1;
	height = b - t + 1;
}
CPortal::CPortal(int scene_id)
{
	this->scene_id = scene_id;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}
CPortal::CPortal(float l ,float t,int scene_id)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width =x+ 26;
	height = y+25;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}