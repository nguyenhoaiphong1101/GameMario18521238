#pragma once
#include "GameObject.h"
#define BRICK_QUESTION_BBOX_WIDTH	16
#define BRICK_QUESTION_BBOX_HEIGHT	16

#define BRICK_QUESTION_ANI_BEFORE	0
#define BRICK_QUESTION_ANI_AFTER	1

#define BRICK_QUESTION_STATE_AFTER	123
#define BRICK_QUESTION_ANI_AFTER	1

#define BRICK_QUESTION_STATUS_DEFAULT		1




class CBrickQuestion : public CGameObject
{
	int status;
	int timeAni=0;
	bool status_before=true;
	bool status_after=false;
	bool check=false;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	CBrickQuestion(int status);
	virtual void SetState(int state, vector<LPGAMEOBJECT>* coObjects);
	int GetStatus()
	{
		return status;
	}
	void SetStatus(int status)
	{
		this->status = status;
	}
	bool GetBefore()
	{
		return status_before;
	}
	void SetBefore(bool status)
	{
		status_before = status;
	}
	bool GetAfter()
	{
		return status_after;
	}
	void SetAfter(bool status)
	{
		status_after = status;
	}
	void SetUp(bool status)
	{
		check = status;
	}
};

