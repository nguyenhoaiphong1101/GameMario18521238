#include "Coin.h"
#include "Mario.h"

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
	x += dx;
	y += dy;
	if (!show) return;


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
	if (state == COIN_STATE_IDLE)
	{
		vx = vy = 0;
	}
}
