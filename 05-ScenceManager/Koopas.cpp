#include "Koopas.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Game.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_WALKING)
		bottom = y + KOOPAS_BBOX_HEIGHT;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;

	

}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPSCENE scence = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	CGameObject::Update(dt);

	if(state != KOOPAS_STATE_HOLD)
	vy += dt * KOOPAS_GRAVITY;
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != KOOPAS_STATE_HOLD)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if(state != KOOPAS_STATE_DIE && state != KOOPAS_STATE_THROW)
		{ 
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			
		}
		if (ny != 0) vy = 0;
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (nx != 0)
			{
				vx = -vx;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (x < 0)
	{
		x = 5;
		vx = -vx;
	}
	if (state == KOOPAS_STATE_HOLD)
	{
		if (mario->holdKoopas == true)
		{
			if (mario->nx > 0)
			{
				x = mario->x + MARIO_BIG_BBOX_WIDTH;
				y = mario->y + MARIO_BIG_BBOX_HEIGHT / 5;
			}
			else
			{
				x = mario->x - KOOPAS_BBOX_WIDTH;
				y = mario->y + MARIO_BIG_BBOX_HEIGHT / 5;
			}
		}
		else
		{
			SetState(KOOPAS_STATE_THROW);
		}
			
	}
	
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_HOLD)
	{
		ani = KOOPAS_ANI_DIE;
	}else
	if (state == KOOPAS_STATE_DIE) {
		if (vx != 0)
			ani = KOOPAS_ANI_TURN;
		else
		ani = KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_THROW)
	{
			ani = KOOPAS_ANI_TURN;
	}
	else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

}

void CKoopas::SetState(int state)
{
	LPSCENE scence = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_HOLD:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_THROW:
		if (mario->nx > 0)
		{
			vx = 0.3f;
			nx = 1;
		}
		else { vx = -0.3f; nx = -1; }
		break;
	}

}