#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Box.h"
#include "Portal.h"
#include "Fire.h"
#include "Brick.h"
#include "Drain.h"
#include "Koopas.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

UINT checkCollBox(vector<LPCOLLISIONEVENT> a)
{
	for (UINT i = 0; i < a.size(); i++)
	{
		LPCOLLISIONEVENT e = a[i];
		if (dynamic_cast<CBox*>(e->obj))
		{
			return i;
		}
	}
	return -1;
}


void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	if(flyCan == false && landingCheck == false)
	vy += MARIO_GRAVITY * dt;
	
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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
		/*if (ny != 0) vy = 0;*/
		//
		// Collision logic with other objects
		//

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->ny < 0)
			{
				checkjumping = 0;
				landingCheck = false;
			}

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				if (level == MARIO_LEVEL_FOX && attack == true)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE_DOWN);
					}
				}
				else
					// jump on top >> kill Goomba and deflect a bit 
					if (e->ny < 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							goomba->SetState(GOOMBA_STATE_DIE);
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}
					}
					else if (e->nx != 0)
					{
						if (untouchable == 0)
						{
							if (goomba->GetState() != GOOMBA_STATE_DIE)
							{
								if (level == MARIO_LEVEL_FIRE || level == MARIO_LEVEL_FOX)
								{
									level = MARIO_LEVEL_BIG;
									StartUntouchable();
								}
								else
									if (level == MARIO_LEVEL_BIG)
									{
										level = MARIO_LEVEL_SMALL;
										StartUntouchable();
									}
									else
										SetState(MARIO_STATE_DIE);
							}
						}
					}
			} // if Goomba
			if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (level == MARIO_LEVEL_FOX && attack == true)
				{
					if (koopas->GetState() != KOOPAS_STATE_HIDE)
					{
						koopas->SetState(KOOPAS_STATE_HIDE);
					}
				}
				else
					if (holdKoopas == true)
					{
						koopas->SetState(KOOPAS_STATE_HOLD);
					}
					else
						if (e->ny < 0)
						{
							if (koopas->GetState() != KOOPAS_STATE_DIE)
							{
								koopas->SetState(KOOPAS_STATE_DIE);
								vy = -MARIO_JUMP_DEFLECT_SPEED;
							}
							else
							{
								koopas->vx = 0;
							}
						}
						else if (e->nx != 0)
						{

							if (untouchable == 0)
							{
								if (koopas->GetState() != KOOPAS_STATE_DIE)
								{
									if (level == MARIO_LEVEL_FIRE || level == MARIO_LEVEL_FOX)
									{
										level = MARIO_LEVEL_BIG;
										StartUntouchable();
									}
									else
										if (level == MARIO_LEVEL_BIG)
										{
											level = MARIO_LEVEL_SMALL;
											StartUntouchable();
										}
										else
											SetState(MARIO_STATE_DIE);
								}
								else
								{
									if (koopas->vx != 0)
									{
										if (level == MARIO_LEVEL_FIRE || level == MARIO_LEVEL_FOX)
										{
											level = MARIO_LEVEL_BIG;
											StartUntouchable();
										}
										else
										{
											if (level == MARIO_LEVEL_BIG)
											{
												level = MARIO_LEVEL_SMALL;
												StartUntouchable();
											}
											else
												SetState(MARIO_STATE_DIE);
										}

									}
									else
									{
										if (nx > 0)
										{
											koopas->vx = -0.3f;
										}

										else
										{
											koopas->vx = +0.3f;
										}

									}
								}
							}
						}
			}
			if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny > 0)
				{
					y += dy;
				}
				else if (e->nx != 0)
				{
					x += dx;
				}
				else
				{
					//if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
			}
			else
			{
				if (ny != 0 && flyCan!=true) vy = 0;
			}
			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

		}
	}
	if (timeFly != 0 && GetTickCount() - timeFly > 3000)
	{
		flyCan = false;
		
		timeFly = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx > 0)
				{
					if (vx < MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_BIG_GEARING_RIGHT;
					}
					else
					{
						if (vx > MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_BIG_RUN_RIGHT;
						else
							ani = MARIO_ANI_BIG_WALKING_RIGHT;
					}

				}
				else
				{
					if (vx < MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_BIG_GEARING_LEFT;
					}
					else
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_BIG_RUN_LEFT;
						else
							ani = MARIO_ANI_BIG_WALKING_LEFT;
				}
			}
			else
			{
				if (nx < 0)
				{
					if (vx > -MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_BIG_GEARING_LEFT;
					}
					else
					{
						if (vx < -MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_BIG_RUN_LEFT;
						else
							ani = MARIO_ANI_BIG_WALKING_LEFT;
					}

				}
				else
				{
					if (vx > -MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_BIG_GEARING_RIGHT;
					}
					else
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_BIG_RUN_RIGHT;
						else
							ani = MARIO_ANI_BIG_WALKING_RIGHT;
				}
			}

			if (checkjumping == 1)
			{
				if (nx < 0)
					ani = MARIO_ANI_BIG_FLY_RIGHT;
				else ani = MARIO_ANI_BIG_FLY_LEFT;
			}
			if (sit == true)
			{
				if (nx > 0)
					ani = MARIO_ANI_BIG_SIT_RIGHT;
				else
					ani = MARIO_ANI_BIG_SIT_LEFT;
			}
			if (holdKoopas == true)
			{
				if (vx == 0)
				{
					if (nx > 0)
						ani = MARIO_ANI_BIG_HOLDKOOPAS_RIGHT;
					else
						ani = MARIO_ANI_BIG_HOLDKOOPAS_LEFT;
				}
				else
				{
					if (vx > 0)
						ani = MARIO_ANI_BIG_HOLDKOOPAS_WALK_RIGHT;
					else
						ani = MARIO_ANI_BIG_HOLDKOOPAS_WALK_LEFT;
				}


			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx > 0)
				{
					if (vx < MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_SMALL_GEARING_RIGHT;
					}
					else
					{
						if (vx > MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_SMALL_RUN_RIGHT;
						else
							ani = MARIO_ANI_SMALL_WALKING_RIGHT;
					}

				}
				else
				{
					if (vx < MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_SMALL_GEARING_LEFT;
					}
					else
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_SMALL_RUN_LEFT;
						else
							ani = MARIO_ANI_SMALL_WALKING_LEFT;
				}
			}
			else
			{
				if (nx < 0)
				{
					if (vx > -MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_SMALL_GEARING_LEFT;
					}
					else {
						if (vx < -MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_SMALL_RUN_LEFT;
						else
							ani = MARIO_ANI_SMALL_WALKING_LEFT;
					}

				}
				else
				{
					if (vx > -MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_SMALL_GEARING_RIGHT;
					}
					else
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_SMALL_RUN_RIGHT;
						else
							ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				}
			}

			if (checkjumping == 1)
			{
				if (nx < 0)
					ani = MARIO_ANI_SMALL_FLY_LEFT;
				else ani = MARIO_ANI_SMALL_FLY_RIGHT;
			}
			if (holdKoopas == true)
			{
				if (vx == 0)
				{
					if (nx > 0)
						ani = MARIO_ANI_SMALL_HOLDKOOPAS_RIGHT;
					else
						ani = MARIO_ANI_SMALL_HOLDKOOPAS_LEFT;
				}
				else
				{
					if (vx > 0)
						ani = MARIO_ANI_SMALL_HOLDKOOPAS_WALK_RIGHT;
					else
						ani = MARIO_ANI_SMALL_HOLDKOOPAS_WALK_LEFT;
				}


			}
		}
		else if (level == MARIO_LEVEL_FIRE)
		{

			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				else ani = MARIO_ANI_FIRE_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx > 0)
				{
					if (vx < MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_FIRE_GEARING_RIGHT;
					}
					else
					{
						if (vx > MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_FIRE_RUN_RIGHT;
						else
							ani = MARIO_ANI_FIRE_WALKING_RIGHT;
					}

				}
				else
				{
					if (vx < MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_FIRE_GEARING_LEFT;
					}
					else
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_FIRE_RUN_LEFT;
						else
							ani = MARIO_ANI_FIRE_WALKING_LEFT;
				}
			}
			else
			{
				if (nx < 0)
				{
					if (vx > -MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_FIRE_GEARING_LEFT;
					}
					else {
						if (vx < -MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_FIRE_RUN_LEFT;
						else
							ani = MARIO_ANI_FIRE_WALKING_LEFT;
					}

				}
				else
				{
					if (vx > -MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_FIRE_GEARING_RIGHT;
					}
					else
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_FIRE_RUN_RIGHT;
						else
							ani = MARIO_ANI_FIRE_WALKING_RIGHT;
				}
			}

			if (checkjumping == 1)
			{
				if (nx < 0)
					ani = MARIO_ANI_FIRE_FLY_LEFT;
				else ani = MARIO_ANI_FIRE_FLY_RIGHT;
			}
			if (sit == true)
			{
				if (nx > 0)
					ani = MARIO_ANI_FIRE_SIT_RIGHT;
				else
					ani = MARIO_ANI_FIRE_SIT_LEFT;
			}
			if (holdKoopas == true)
			{
				if (vx == 0)
				{
					if (nx > 0)
						ani = MARIO_ANI_FIRE_HOLDKOOPAS_RIGHT;
					else
						ani = MARIO_ANI_FIRE_HOLDKOOPAS_LEFT;
				}
				else
				{
					if (vx > 0)
						ani = MARIO_ANI_FIRE_HOLDKOOPAS_WALK_RIGHT;
					else
						ani = MARIO_ANI_FIRE_HOLDKOOPAS_WALK_LEFT;
				}
			}
		}
		else if (level == MARIO_LEVEL_FOX)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_FOX_IDLE_RIGHT;
				else ani = MARIO_ANI_FOX_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx > 0)
				{
					if (vx < MARIO_GEARING_MAX && checkidle != true)
					{
						ani = MARIO_ANI_FOX_GEARING_RIGHT;
					}
					else
					{
						if (vx > MARIO_GEARING_MAX)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_FOX_RUN_RIGHT;
						else
							ani = MARIO_ANI_FOX_WALKING_RIGHT;
					}
				}
				else
				{
					if (vx < MARIO_GEARING_MAX)
					{
						ani = MARIO_ANI_FOX_GEARING_LEFT;
					}
					else
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_FOX_RUN_LEFT;
						else
							ani = MARIO_ANI_FOX_WALKING_LEFT;
				}
			}
			else
			{
				if (nx < 0)
				{
					if (vx > -0.051f && checkidle != true)
					{
						ani = MARIO_ANI_FOX_GEARING_LEFT;
					}
					else
					{
						if (vx < -0.051f)
							checkidle = false;
						if (state == MARIO_STATE_WALKING_LEFT_FAST)
							ani = MARIO_ANI_FOX_RUN_LEFT;
						else
							ani = MARIO_ANI_FOX_WALKING_LEFT;
					}

				}
				else
				{
					if (vx > -0.051f)
					{
						ani = MARIO_ANI_FOX_GEARING_RIGHT;
					}
					else
						if (state == MARIO_STATE_WALKING_RIGHT_FAST)
							ani = MARIO_ANI_FOX_RUN_RIGHT;
						else
							ani = MARIO_ANI_FOX_WALKING_RIGHT;
				}
			}

			if (checkjumping == 1)
			{
				if (nx < 0)
					ani = MARIO_ANI_FOX_JUMP_LEFT;
				else ani = MARIO_ANI_FOX_JUMP_RIGHT;
			}
			if (attack == true)
			{
				ani = MARIO_ANI_FOX_ATTACK;
			}
			else if (holdKoopas == true)
			{
				if (vx == 0)
				{
					if (nx > 0)
						ani = MARIO_ANI_FOX_HOLDKOOPAS_RIGHT;
					else
						ani = MARIO_ANI_FOX_HOLDKOOPAS_LEFT;
				}
				else
				{
					if (vx > 0)
						ani = MARIO_ANI_FOX_HOLDKOOPAS_WALK_RIGHT;
					else
						ani = MARIO_ANI_FOX_HOLDKOOPAS_WALK_LEFT;
				}
			}
			else if (flyCan == true)
			{
				if (nx > 0)
					ani = MARIO_ANI_FOX_FLY_RIGHT;
				else
					ani = MARIO_ANI_FOX_FLY_LEFT;
			}
			else if (landingCheck == true)
			{
				if (nx > 0)
					ani = MARIO_ANI_FOX_LANDING_RIGHT;
				else
					ani = MARIO_ANI_FOX_LANDING_LEFT;
			}
			else if (sit == true)
			{
				if (nx > 0)
					ani = MARIO_ANI_FOX_SIT_RIGHT;
				else
					ani = MARIO_ANI_FOX_SIT_LEFT;
			}
			
		}



	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	/*RenderBoundingBox();*/
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		if (vx <= MARIO_WALKING_SPEED)
		{
			if (vx < 0)
				vx = 0;
			else
				vx += MARIO_WALKING_SPEED_PLUS1;
		}
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (vx >= -MARIO_WALKING_SPEED)
		{
			if (vx > 0)
				vx = 0;
			else
				vx -= MARIO_WALKING_SPEED_PLUS1;
		}
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		checkjumping = 1;
		vy = -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_IDLE:
		checkidle = true;
		vx = 0;
		break;
	case MARIO_STATE_FLY:
		vy = -MARIO_WALKING_FLY;
		checkjumping = 1;
		break;
	case MARIO_STATE_LANDING:
		vy = MARIO_WALKING_FLY;
		checkjumping = 1;
		break;


	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_WALKING_RIGHT_FAST:
		if (vx < MARIO_WALKING_RUN_MAX)
		{
			if (vx < -0.05)//giới hạn tốc độ để mario lấy đà mượt hơn
				vx = -0.04;
			else
			{
				vx += MARIO_WALKING_SPEED_PLUS;
			}
		}
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT_FAST:
		if (vx > -MARIO_WALKING_RUN_MAX)
		{
			if (vx > 0.05)
				vx = 0.04;
			else
			{
				vx -= MARIO_WALKING_SPEED_PLUS;
			}
		}
		nx = -1;
		break;
	case MARIO_STATE_JUMP_HIGH:
		checkjumping = 1;
		vy = -MARIO_JUMP_SPEED_Y_HIGH;
		break;

	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		right = x + MARIO_FIRE_BBOX_WIDTH;
		bottom = y + MARIO_FIRE_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_FOX)
	{
		right = x + MARIO_FOX_BBOX_WIDTH;
		bottom = y + MARIO_FOX_BBOX_HEIGHT;
	}
	if (sit == true)
	{
		if (level != MARIO_LEVEL_SMALL)
			bottom = y + MARIO_SIT_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}



