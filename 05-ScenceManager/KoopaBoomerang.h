

#pragma once
#include "GameObject.h"
#include "algorithm"
#include "Mario.h"
#include "PlayScence.h"


#define  KOOPABOOMERANG_BBOX_WIDTH		16
#define  KOOPABOOMERANG_BBOX_HEIGHT	24

#define  KOOPABOOMERANG_STATE_IDLE				0
#define  KOOPABOOMERANG_STATE_MOVE_FORWARD		100
#define  KOOPABOOMERANG_STATE_MOVE_BACKWARD    200
#define	 KOOPABOOMERANG_STATE_DIE				300

#define KOOPABOOMERANG_GRAVITY		0.002f


#define KOOPABOOMERANG_ANI_NORMAL_RIGHT				0
#define KOOPABOOMERANG_ANI_THROW_BOOMERANG_RIGHT		1
#define KOOPABOOMERANG_ANI_DIE_RIGHT					2
#define KOOPABOOMERANG_ANI_DIE_LEFT					3
#define KOOPABOOMERANG_ANI_NORMAL_LEFT					4	
#define KOOPABOOMERANG_ANI_THROW_BOOMERANG_LEFT		5

class CKoopaBoomerang : public CGameObject
{
	bool isAllowToHaveBBox = true;

	DWORD time_switch_state = 0;

	bool isAlive = true;

	bool isAllowToRenderThrowAni = false;

	DWORD time_rendering_throw_ani = 0;

	bool isAllowToShowScore = false;
	DWORD timing_score;

	DWORD pre_get_tick_count = 0;
	DWORD sub_time = 0;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	CKoopaBoomerang();
	virtual void SetState(int state);

	void StartTimeSwitchingState()
	{
		if (time_switch_state == 0)
		{
			time_switch_state = GetTickCount();
		}
	}
	void StartTimeRenderingThrowAni()
	{
		if (time_rendering_throw_ani == 0)
		{
			time_rendering_throw_ani = GetTickCount();
		}
	}
	bool GetIsAlive()
	{
		return isAlive;
	}
	void SetIsAlive(bool isAliveBool)
	{
		isAlive = isAliveBool;
	}
	bool GetIsAllowToShowScore()
	{
		if (this != NULL)
			return isAllowToShowScore;
		else
		{
			return false;
		}
	}
	void SetIsAllowToShowScore(bool isAllowToShowScoreBool)
	{
		if (this != NULL)
			isAllowToShowScore = isAllowToShowScoreBool;
	}
	void StartTimingScore()
	{
		timing_score = GetTickCount();
	}
	bool GetIsAllowToHaveBBox()
	{
		return isAllowToHaveBBox;
	}
	void SetIsAllowToHaveBBox(bool isAllowToHaveBBoxBool)
	{
		isAllowToHaveBBox = isAllowToHaveBBoxBool;
	}
};