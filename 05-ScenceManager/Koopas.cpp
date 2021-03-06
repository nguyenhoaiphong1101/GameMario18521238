#include "Koopas.h"
#include "Box.h"
#include "Drain.h"
#include "Brick.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Game.h"
#include "GoombaPara.h"
#include <algorithm>
#include "FireFlower.h"
#include "BrickBroken.h"
#include "BrickQuestion.h"
#include "Coin.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
		if (dynamic_cast<CGoomba*>(coObjects->at(i)))
		{
			if (GetState() != KOOPAS_STATE_THROW)
				continue;
		}
		if (dynamic_cast<CGoombaPara*>(coObjects->at(i)))
		{
			if (GetState() != KOOPAS_STATE_THROW)
				continue;
		}
		if (dynamic_cast<CBox*>(coObjects->at(i)))
		{
			if (e->nx != 0)
				continue;
		}
		if (dynamic_cast<CFireFlower*>(coObjects->at(i)))
		{
			if (e->nx != 0)
				continue;
		}
		if (dynamic_cast<CCoin*>(coObjects->at(i)))
		{
			continue;
		}


		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);

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
	if (state == KOOPAS_STATE_HIDE)
	{
		left = top = right = bottom = 0;
	}


}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int ids = CGame::GetInstance()->GetCurrentScene()->GetId();
	LPSCENE scence = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	CGameObject::Update(dt);

	if (state != KOOPAS_STATE_HOLD)
		vy += dt * KOOPAS_GRAVITY;



	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != KOOPAS_STATE_HOLD && state != KOOPAS_STATE_HIDE)
		CalcPotentialCollisions(coObjects, coEvents);

	float tempy = y + dy;
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

		if (ids == 4)
		{
			if (x < 1763)
			{
				if (back && (state == KOOPAS_STATE_WALKING))
				{
					if (y - tempbacky >= 1.0f)
					{
						y -= 5;
						if (vx < 0)
							x += 12;
						else
							x -= 12;
						vx = -vx;
					}
				}
			}
		}

	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (state != KOOPAS_STATE_DIE && state != KOOPAS_STATE_THROW && state != KOOPAS_STATE_HIDE)
		{
			x += min_tx * dx + nx * 0.4f;
			if (nx < 0)
				y += min_ty * dy + ny * 0.4f;

		}
		if (ny != 0) vy = 0;
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			/*if (e->nx != 0)
			{
				vx = -vx;
			}*/
			if (!dynamic_cast<CMario*>(e->obj) && nx == 0)
			{
				tempbacky = y;
				back = true;
			}

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				if (state == KOOPAS_STATE_THROW)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						mario->ScoreUp();
						goomba->SetState(GOOMBA_STATE_DIE_DOWN);
					}
				}
			}
			if (dynamic_cast<CGoombaPara*>(e->obj)) // if e->obj is Goomba 
			{
				CGoombaPara* goomba = dynamic_cast<CGoombaPara*>(e->obj);

				if (state == KOOPAS_STATE_THROW)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						mario->ScoreUp();
						goomba->SetState(GOOMBA_STATE_DIE_DOWN);
					}
				}
			}
			if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Goomba 
			{
				CKoopas* goomba = dynamic_cast<CKoopas*>(e->obj);

				if (state == KOOPAS_STATE_THROW)
				{
					mario->ScoreUp();
					goomba->SetState(GOOMBA_STATE_DIE_DOWN);
				}
			}
			if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->nx != 0)
				{
					x += dx;
				}
			}
			if (dynamic_cast<CDrain*>(e->obj))
			{
				if (e->nx != 0)
				{
					vx = -vx;
				}
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (nx != 0)
				{
					vx = -vx;
				}
			}

			if (dynamic_cast<CBrickQuestion*>(e->obj))
			{
				CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion*>(e->obj);
				
				if (brickQuestion->GetAfter())
				{
					if (state != KOOPAS_STATE_DIE)
						SetState(KOOPAS_STATE_DIE);
					
					x =brickQuestion->x+ 16;
				}
			}
			if (dynamic_cast<CBrickBroken*>(e->obj))
			{
				CBrickBroken* brick = dynamic_cast<CBrickBroken*>(e->obj);

				if (nx != 0)
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
			if (mario->GetLevel() != MARIO_LEVEL_SMALL)
			{
				if (mario->GetLevel() == MARIO_LEVEL_FOX)
				{
					if (mario->nx > 0)
					{
						x = mario->x + MARIO_FOX_BBOX_WIDTH;
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
			}
			else
			{
				if (mario->nx > 0)
				{
					x = mario->x + MARIO_BIG_BBOX_WIDTH + 2;
					y = mario->y - MARIO_BIG_BBOX_HEIGHT / 5;
				}
				else
				{
					x = mario->x - KOOPAS_BBOX_WIDTH - 3;
					y = mario->y - MARIO_BIG_BBOX_HEIGHT / 5;
				}
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
	int ids = CGame::GetInstance()->GetCurrentScene()->GetId();
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_HOLD)
	{
		if (ids == 4)
		{
			ani = 6;
		}
		else
			ani = KOOPAS_ANI_DIE;
	}
	else
		if (state == KOOPAS_STATE_DIE) {
			if (vx != 0)
			{
				if (ids == 4)
				{
					ani = 7;
				}
				else
					ani = KOOPAS_ANI_TURN;
			}
			else
			{
				if (ids == 4)
				{
					ani = 6;
				}
				else
					ani = KOOPAS_ANI_DIE;
			}

		}
		else if (state == KOOPAS_STATE_THROW)
		{
			if (ids == 4)
			{
				ani = 7;
			}
			else
				ani = KOOPAS_ANI_TURN;
		}
		else if (vx > 0)
		{
			if (ids == 4)
			{
				ani = 5;
			}
			else
				ani = KOOPAS_ANI_WALKING_RIGHT;
		}
		else if (vx < 0)
		{
			if (ids == 4)
			{
				ani = 4;
			}
			else
				ani = KOOPAS_ANI_WALKING_LEFT;
		}

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
	case KOOPAS_STATE_HIDE:
		vy = -0.5f;
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