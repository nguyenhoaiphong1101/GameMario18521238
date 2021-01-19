#include "RectangleMove.h"


CRectangleMove::CRectangleMove()
{
	SetState(RECTANGLE_MOVE_STATE_NORMAL);
}

void CRectangleMove::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (!dynamic_cast<CMario*>(coObjects->at(i)))
		{
			continue;
		}

		if (e->t > 0 && e->t <= 1.0f)
		{
			coEvents.push_back(e);
		}
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}
void CRectangleMove::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = x;
	t = y;
	r = x + RECTANGLE_MOVE_BBOX_WIDTH;
	b = y + RECTANGLE_MOVE_BBOX_HEIGHT;


}

void CRectangleMove::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	mario_check = false;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	
	

	
	if (mario->checkRecMove)
	{
		if (mario_check)
		{
			if (mario->GetLevel() != MARIO_LEVEL_SMALL)
			{
				mario->y = this->y - 27;
			}
			else
			{
				mario->y = this->y - 15;
			}
		}
	}
	
	
	// clean up collision events

}

void CRectangleMove::Render()
{
	animation_set->at(0)->Render(x, y);

	//RenderBoundingBox();
}

void CRectangleMove::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case  RECTANGLE_MOVE_STATE_NORMAL:
		vx = RECTANGLE_MOVE_STATE_NORMAL_SPEED;
		vy = 0;
		break;
	case  RECTANGLE_MOVE_STATE_DOWN:
		vy = RECTANGLE_MOVE_STATE_DOWN_SPEED;
		vx = 0;
		break;
	}
}



