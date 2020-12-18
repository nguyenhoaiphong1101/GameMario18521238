#pragma once
#pragma once
#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;
#define KOOPAS_RUN_SPEED 0.3f;
#define KOOPAS_RUN_SPEED_Y 0.5f;
#define KOOPAS_JUMP_SPEED_Y 0.25f;
#define KOOPAS_GRAVITY 0.002f;

#define KOOPAS_BBOX_WIDTH 15
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_JUMP_BBOX_WIDTH 16
#define KOOPAS_JUMP_BBOX_HEIGHT 27
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_HOLD 201
#define KOOPAS_STATE_THROW 202
#define KOOPAS_STATE_HIDE 203
#define KOOPAS_STATE_JUMP 204

#define KOOPASPARA_ANI_WALKING_LEFT 3
#define KOOPASPARA_ANI_WALKING_RIGHT 2
#define KOOPASPARA_ANI_JUMP_LEFT 1
#define KOOPASPARA_ANI_JUMP_RIGHT 0
#define KOOPASPARA_ANI_DIE 5
#define KOOPASPARA_ANI_TURN 4

#define KOOPAS_TIME_JUMP 2000


class CKoopaPara : public CGameObject
{
	DWORD checkJump;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopaPara();
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	virtual void SetState(int state);

};

