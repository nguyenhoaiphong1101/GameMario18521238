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

	LPSCENE scence = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->checkEnd)
	{
		if (type == 0)
			show = true;
		if (mario->card == type)
			show = true;
	}
}

void ContentEnd::SetState(int state)
{
	CGameObject::SetState(state);
}

