#include "BrickQuestion.h"
#include "Mario.h"
#include "PlayScence.h"
#include <algorithm>
CBrickQuestion::CBrickQuestion(int status)
{
	this->status = status;
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

	RenderBoundingBox();
}

void CBrickQuestion::SetState(int state, vector<LPGAMEOBJECT>* coObjects)
{
	
}
