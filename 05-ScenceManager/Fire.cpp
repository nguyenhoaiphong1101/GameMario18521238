#include "Fire.h"
#include "Goomba.h"
#include "Brick.h"
#include "Box.h"
#include "Drain.h"
#include "Koopas.h"


void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vy += FIRE_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);

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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 




		//// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;




		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);


				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					goomba->SetState(GOOMBA_STATE_DIE);
				}
				x = -100;

			}
			if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);


				if (koopas->GetState() != KOOPAS_STATE_HIDE)
				{
					koopas->SetState(KOOPAS_STATE_HIDE);
				}
				x = -100;


			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = -0.25f;
					y += vy * dt;
					x += dx;
				}
				else if (e->ny > 0)
				{
					vy = 0.25f;
					y += vy * dt;
					x += dx;
				}
				/*else
				{
					x = -100;
				}*/
			}
			if (dynamic_cast<CDrain*>(e->obj))
			{
				if (e->nx != 0)
				{
					x = -100;
				}
			}
			if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->nx != 0)
				{
					x += dx;
					y += dy;
				}
				else if (e->ny < 0)
				{
					vy = -0.25f;
					y += vy * dt;
					x += dx;
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CFire::Render()
{
	int ani = -1;
	if (nx = 1)
	{
		ani = FIRE_ANI_RIGHT;
	}
	else {
		ani = FIRE_ANI_LEFT;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}



void CFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_HEIGHT;
	b = y + FIRE_BBOX_WIDTH;
}

