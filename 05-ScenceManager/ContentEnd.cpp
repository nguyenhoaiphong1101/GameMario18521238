#include "ContentEnd.h"
#include "Game.h"
#include "Mario.h"
#include "Scence.h"
#include "PlayScence.h"
#include "Card.h"
void ContentEnd::Render()
{
		if (show)
			animation_set->at(0)->Render(x, y);
}
void ContentEnd::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void ContentEnd::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type >= 4)
	{
		if (show)
		{
			vy = -0.07f;
		}
	}
	CGameObject::Update(dt);
	y += dy;
	LPSCENE scence = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->checkEnd)
	{
		if (type == 0)
			show = true;
		if (mario->card == type)
			show = true;
		switch (mario->card)
		{
		case 1:
			if (type == 4)
				show = true;
		case 2:
			if (type == 5)
				show = true;
		case 3:
			if (type == 6)
				show = true;
		default:
			break;
		}
	}
}

void ContentEnd::SetState(int state)
{
	CGameObject::SetState(state);
}

