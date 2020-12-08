#include "HUD.h"
#include "Scence.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"
#include <string>


HUD::HUD()
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)game->GetCurrentScene())->GetPlayer();
	CSprites* sprites = CSprites::GetInstance();


	backgroundBlack = sprites->Get(HUD_BACKGROUND_SPRITE);
	hudBoard = sprites->Get(HUD_BOARD_SPRITE);
	hudItem = sprites->Get(HUD_ITEM_SPRITE);
	world = getHUD('1');

	marioType = sprites->Get(HUD_MARIO_TYPE_SPRITE);

	for (int i = 0; i < 7; i++)
	{
		if (i != 6)
		{
			storePowerNull.push_back(sprites->Get(HUD_ARROW_BLACK_SPRITE));
			storePower.push_back(sprites->Get(HUD_ARROW_WHITE_SPRITE));
		} 
		else
		{
			storePowerNull.push_back(sprites->Get(HUD_POWER_BLACK_SPRITE));
			storePower.push_back(sprites->Get(HUD_POWER_WHITE_SPRITE));
		}
			
	}
	

	storePowerNullStack = mario->GetSpeed();
	marioCoin = mario->GetCoin();
	marioScore = mario->GetScore();
	marioLife = mario->GetLife();


}

void HUD::resetHUD()
{

}


void HUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	SetPosition(game->GetCamPosX(), game->GetCamPosY() + 260);
	CMario* mario = ((CPlayScene*)game->GetCurrentScene())->GetPlayer();

	if (mario->GetState() == MARIO_STATE_DIE) return;
	//Cập nhật thuộc tính
	tempTime += dt;
	marioTime = game->GetGameTime() - tempTime / 1000;
	storePowerNullStack = mario->GetSpeed();
	marioCoin = mario->GetCoin();
	marioScore = mario->GetScore();
	marioLife = mario->GetLife();
	
	if (marioTime == 0)
	{
		mario->SetState(MARIO_STATE_DIE);
	}

	
	string stringLife = to_string(marioLife);
	string stringCoin = to_string(marioCoin);
	string stringTime = to_string(marioTime);
	string stringScore = to_string(marioScore);


	//Chỉnh sửa phù hợp với HUD
	while (stringLife.length() < 2)
	{
		stringLife = "0" + stringLife;
	}
	life = StringToSprite(stringLife);
	while (stringTime.length() < 3)
	{
		stringTime = "0" + stringTime;
	}
	time = StringToSprite(stringTime);
	while (stringScore.length() < 7)	
	{
		stringScore = "0" + stringScore;
	}

	coin = StringToSprite(stringCoin);
	score = StringToSprite(stringScore);
}

void HUD::Render()
{

	//draw a black background
	backgroundBlack->Draw(x, y - 84);
	hudBoard->Draw(x + 55, y - 81);
	hudItem->Draw(x + 235, y - 81);
	marioType->Draw(x + 59, y - 66);
	world->Draw(x + 92, y - 74);	

	for (int i = 0; i < life.size(); i++)
	{
		life[i]->Draw(x + 84 + 8 * i, y - 66);
	}

	for (int i = 0; i < time.size(); i++)
	{
		time[i]->Draw(x + 179 + 8 * i, y - 66);
	}

	for (int i = 0; i < score.size(); i++)
	{
		score[i]->Draw(x + 107 + 8 * i, y - 66);
	}

	for (int i = 0; i < coin.size(); i++)
	{
		coin[i]->Draw(x + 187 + 8 * i, y - 74);
	}

	for (int i = 0; i < storePowerNull.size(); i++)
	{
		storePowerNull[i]->Draw(x + 107 + 8 * i, y - 74);
	}

	for (int i = 0; i < storePowerNullStack; i++)
	{
		storePower[i]->Draw(x + 107 + 8 * i, y - 74);
	}

}

vector<LPSPRITE> HUD::StringToSprite(string str)
{
	vector<LPSPRITE> spritesVector;
	LPSPRITE sprite;
	char temp;
	for (int i = 0; i < str.size(); i++)
	{
		temp = (char)str[i];
		sprite = getHUD(temp);
		if (sprite != NULL)
			spritesVector.push_back(sprite);
	}
	return spritesVector;
}

LPSPRITE HUD::getHUD(char a)
{
	CSprites* number = CSprites::GetInstance();
	switch (a)
	{
	case '0':
		return number->Get(HUD_0_SPRITE);
		break;
	case '1':
		return number->Get(HUD_1_SPRITE);
		break;
	case '2':
		return number->Get(HUD_2_SPRITE);
		break;
	case '3':
		return number->Get(HUD_3_SPRITE);
		break;
	case '4':
		return number->Get(HUD_4_SPRITE);
		break;
	case '5':
		return number->Get(HUD_5_SPRITE);
		break;
	case '6':
		return number->Get(HUD_6_SPRITE);
		break;
	case '7':
		return number->Get(HUD_7_SPRITE);
		break;
	case '8':
		return number->Get(HUD_8_SPRITE);
		break;
	case '9':
		return number->Get(HUD_9_SPRITE);
		break;
	default:
		return NULL;
		break;
	}

	
}


