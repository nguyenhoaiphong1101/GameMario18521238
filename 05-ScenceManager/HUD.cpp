#include "HUD.h"
#include "Scence.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"


void HUD::Render()
{
	animation_set->at(0)->Render(x, y);
}
void HUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	LPSCENE scence = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	

	if (mario->x <= (game->GetScreenWidth() / 2)) 
		x = x_default;
	if (mario->y >= -46)
		y = -46;
	else cy -= game->GetScreenHeight() / 2;
	


}

