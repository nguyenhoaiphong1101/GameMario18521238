#pragma once
#include "GameObject.h"
#include "PlayScence.h"

#define COIN_BBOX_WIDTH  10
#define COIN_BBOX_HEIGHT 15


#define COIN_STATE_IDLE		0
#define COIN_STATE_UP		1


#define COIN			100
//#define COIN_CAN_TOSS		333
//
//#define TIME_COIN_ON_AIR 250

class CCoin : public CGameObject
{
	int status;
	bool hide = false;
	bool show;
	int timeStart;
public:
	
	CCoin(int status);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void TimeStart()
	{
		timeStart = GetTickCount();
	}
	void SetShow(bool temp)
	{
		show = temp;
	}
	bool GetShow()
	{
		return show;
	}
};