#pragma once
#include "GameObject.h"
#include "algorithm"
#include "Mario.h"
#include "PlayScence.h"


#define RECTANGLE_MOVE_BBOX_WIDTH		48
#define RECTANGLE_MOVE_BBOX_HEIGHT		16



#define  RECTANGLE_MOVE_STATE_NORMAL		0
#define  RECTANGLE_MOVE_STATE_DOWN			1

#define	 RECTANGLE_MOVE_STATE_NORMAL_SPEED   -0.03f
#define  RECTANGLE_MOVE_STATE_DOWN_SPEED	   0.05f



class CRectangleMove : public CGameObject
{
	bool isAppear = false;
	DWORD upping_start = 0;
	

public:
	bool mario_check = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	CRectangleMove();
	virtual void SetState(int state);


};