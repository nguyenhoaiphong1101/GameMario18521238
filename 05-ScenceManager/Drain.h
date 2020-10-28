#pragma once
#include "GameObject.h"

#define DRAIN_BBOX_WIDTH  16
#define DRAIN_BBOX_HEIGHT 16

class CDrain : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};