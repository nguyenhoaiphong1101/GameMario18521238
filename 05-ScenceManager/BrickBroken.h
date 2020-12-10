#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_BROKEN 111
#define BRICK_BROKEN_BELL 222
class CBrickBroken : public CGameObject
{
	int status;
	int timeStart;
public:
	CBrickBroken(int status);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int GetStatus() { return status; };
	int SetStatus(int status) { this->status = status; };
	void TimeStart() { timeStart = GetTickCount() };

};

