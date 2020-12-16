#include "Coin.h"
#include "Mario.h"
#include "BrickQuestion.h"
#include <algorithm>


CCoin::CCoin(int temp)
{
	this->status = temp;
	if (status == COIN)
	{
		show = true;
	}
	else
		show = false;
	SetState(COIN_STATE_IDLE);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (show == false)
	{
		l = t = r = b = 0;
	}
	else
	{
		l = x;
		t = y;
		r = x + COIN_BBOX_WIDTH;
		b = y + COIN_BBOX_HEIGHT;
	}

}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != COIN_STATE_IDLE)
	{
		vy += 0.003f * dt;
		CalcPotentialCollisions(coObjects, coEvents);

	}
	
	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (!show) return;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		// Collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickQuestion*>(e->obj))
			{
				isDisAppear = true;
			}
		}
	}
	
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CCoin::Render()
{
	if (!show)
		return;
	animation_set->at(0)->Render(x, y);
}
void CCoin::SetState(int state)
{
	this->state = state;
	switch (this->state)
	{
	case COIN_STATE_IDLE:
		vx = vy = 0;
		break;
	case COIN_STATE_UP:
		vx = 0;
		vy = -0.5f;
	default:
		break;
	}
	
}
