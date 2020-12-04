#pragma once
#include "GameObject.h"

#define FIRE_BBOX_WIDTH  8
#define FIRE_BBOX_HEIGHT  8

#define FIRE_ANI_RIGHT  0
#define FIRE_ANI_LEFT  1

#define FIRE_GRAVITY 0.002f
#define FIRE_SPEED 0.15f
#define FIRE_GRAVITY 0.002f

class CFire: public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};