
#include "Game.h"
#include "PlayScence.h"


CIntroMario::CIntroMario(int type)
{
	typeIntro = type;
	time = GetTickCount();
}
void CIntroMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPSCENE scene = CGame::GetInstance()->GetCurrentScene();
	if (typeIntro == INTRO_TYPE_CURTAIN)
	{
		y--;
		if (y <= -187)
			isDisAppear == true;
		if (y == -93)
		{
			CIntroMario* marioleft = new CIntroMario(INTRO_ANI_MARIO_LEFT);
			marioleft->x = 164;
			marioleft->y = 160;
			LPANIMATION_SET ani_set = animation_sets->Get(1);
			marioleft->SetAnimationSet(ani_set);
			((CPlayScene*)scene)->addObject(marioleft);
			CIntroMario* marioright = new CIntroMario(INTRO_ANI_MARIO_RIGHT);
			marioright->x = 183;
			marioright->y = 160;
			LPANIMATION_SET ani_set2 = animation_sets->Get(1);
			marioright->SetAnimationSet(ani_set2);
			((CPlayScene*)scene)->addObject(marioright);
		}
	}
	if (typeIntro == INTRO_TYPE_ICON_BLACK)
	{
		if(y<=0)
		y++;
		else
		{
			CIntroMario* introcolor = new CIntroMario(INTRO_TYPE_ICON_COLOR);
			introcolor->x = 55;
			introcolor->y = 0;
			LPANIMATION_SET ani_set = animation_sets->Get(1);
			introcolor->SetAnimationSet(ani_set);
			((CPlayScene*)scene)->addObject(introcolor);


			CIntroMario* number = new CIntroMario(INTRO_TYPE_ICON_CHANGE_COLOR);
			number->x = 167;
			number->y = 96;
			LPANIMATION_SET ani_set2 = animation_sets->Get(1);
			number->SetAnimationSet(ani_set2);
			((CPlayScene*)scene)->addObject(number);


			CIntroMario* firstbutton = new CIntroMario(INTRO_TYPE_ARROW);
			firstbutton->first = true;
			LPANIMATION_SET ani_set3 = animation_sets->Get(1);
			firstbutton->SetAnimationSet(ani_set3);
			((CPlayScene*)scene)->addObject(firstbutton);
			isDisAppear=true;
		}
	}
	if (typeIntro == INTRO_ANI_MARIO_LEFT)
	{
		x--;
		if (x <= 55)
			isDisAppear = true;
	}
	if (typeIntro == INTRO_ANI_MARIO_RIGHT)
	{
		x++;
		if (x >= 292)
			isDisAppear = true;
	}
	if (typeIntro == INTRO_TYPE_ARROW)
	{
		if (first == true)
		{
			x = 123;
			y = 144;
		}
		if (second == true)
		{
			x = 123;
			y = 161;
		}
	}
}

void CIntroMario::Render()
{
	int ani = -1;
	switch (typeIntro)
	{
	case INTRO_TYPE_BACKGROUNDBLACK:
		ani = INTRO_ANI_BACKGROUNDBLACK;
		break;
	case INTRO_TYPE_FLOOR:
		ani = INTRO_ANI_FLOOR;
		break;
	case INTRO_TYPE_ICON_BLACK:
		ani = INTRO_ANI_ICON_BLACK;
		break;
	case INTRO_TYPE_ICON_COLOR:
		ani = INTRO_ANI_ICON_COLOR;
		break;
	case INTRO_TYPE_ICON_CHANGE_COLOR:
		ani = INTRO_ANI_ICON_CHANGE_COLOR;
		break;
	case INTRO_TYPE_ARROW:
		ani = INTRO_ANI_ARROW;
		break;
	case INTRO_TYPE_CURTAIN:
		ani = INTRO_ANI_CURTAIN;
		break;
	case INTRO_TYPE_MARIO_LEFT:
		ani = INTRO_ANI_MARIO_LEFT;
		break;
	case INTRO_TYPE_MARIO_RIGHT:
		ani = INTRO_ANI_MARIO_RIGHT;
		break;
	default:
		break;
	}
	animation_set->at(ani)->Render(x, y);
}
void CIntroMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}


