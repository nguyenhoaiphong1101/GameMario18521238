#include "BrickQuestion.h"

#include "Scence.h"
#include "Coin.h"
#include "MushRoom.h"
#include <algorithm>
CBrickQuestion::CBrickQuestion(int status)
{
	this->status = status;
	state = -1;
}


void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_QUESTION_BBOX_WIDTH;
	b = y + BRICK_QUESTION_BBOX_HEIGHT;
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CalcPotentialCollisions(coObjects, coEvents);
	// tạo animation gạch nhảy lên
	if (!status_before)//nếu gạch k còn trạng thái đứng yên
	{
		if (check)
		{
			if (timeAni > 3)
			{
				timeAni = 0;
				check = false;
			}
			else
			{
				y -= 3;
				timeAni++;
			}
		}
		else
		{
			if(timeAni<=3)
			{
				y += 3;
				timeAni++;
			}
				
		}
	}


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with the others Goombas
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CBrickQuestion::Render()
{
	int ani = -1;

	if (status_before)
	{
			ani = BRICK_QUESTION_ANI_BEFORE;
	}
	else
		ani = BRICK_QUESTION_ANI_AFTER;
	animation_set->at(ani)->Render(x, y);

	/*RenderBoundingBox();*/
}

void CBrickQuestion::SetState(int state)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPSCENE scene = CGame::GetInstance()->GetCurrentScene();
	if (state == BRICK_QUESTION_STATE_AFTER)
	{
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		switch (status)
		{
		case BRICK_QUESTION_STATUS_COIN:
		{
			CCoin *coins = new CCoin(COIN);
			coins->SetState(COIN_STATE_UP);
			coins->x = x+ BRICK_QUESTION_BBOX_WIDTH/4;
			coins->y = y - COIN_BBOX_HEIGHT;
			LPANIMATION_SET ani_set = animation_sets->Get(7001);
			coins->SetAnimationSet(ani_set);
			((CPlayScene*)scene)->addObject(coins);
			break;
		}
		case BRICK_QUESTION_STATUS_LEAF:
		{
			
			break;
		}
		case BRICK_QUESTION_STATUS_MUSHROOM:
		{
			CMushRoom* mushroom = new CMushRoom();
			mushroom->x = x ;
			mushroom->y = y - MUSHROOM_BBOX_HEIGHT *1.2;
			mushroom->vx = -MUSHROOM_SPEED;
			LPANIMATION_SET ani_set = animation_sets->Get(6022);
			mushroom->SetAnimationSet(ani_set);
			((CPlayScene*)scene)->addObject(mushroom);
			break;
		}
		default:
			break;
		}
	}
}
