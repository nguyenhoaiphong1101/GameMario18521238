#include "Scence.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"
#include <string>


CHUD::CHUD()
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)game->GetCurrentScene())->GetPlayer();

	CSprites* sprites = CSprites::GetInstance();


	backgroundBlack = sprites->Get(HUD_BACKGROUND_SPRITE);
	hudBoard = sprites->Get(HUD_BOARD_SPRITE);
	hudItem = sprites->Get(HUD_ITEM_SPRITE);
	world = getHUD('1');

	marioType = sprites->Get(HUD_MARIO_TYPE_SPRITE);

	for (int i = 0; i < SCORE_LENGTH; i++)
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

void CHUD::resetHUD()
{

}


void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	SetPosition(game->GetCamPosX(), game->GetCamPosY() + 260);
	CMario* mario = ((CPlayScene*)game->GetCurrentScene())->GetPlayer();
	if (mario->GetState() == MARIO_STATE_DIE)
	{
		marioLife = mario->GetLife();
		string stringLife = to_string(marioLife);
		while (stringLife.length() < LIFE_LENGTH)
		{
			stringLife = "0" + stringLife;
		}
		life = StringToSprite(stringLife);
		return;

	}
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
	while (stringLife.length() < LIFE_LENGTH)
	{
		stringLife = "0" + stringLife;
	}
	life = StringToSprite(stringLife);
	while (stringTime.length() < COIN_LENGTH)
	{
		stringTime = "0" + stringTime;
	}
	time = StringToSprite(stringTime);
	while (stringScore.length() < SCORE_LENGTH)
	{
		stringScore = "0" + stringScore;
	}

	coin = StringToSprite(stringCoin);
	score = StringToSprite(stringScore);
	life = StringToSprite(stringLife);

}

void CHUD::Render()
{

	//draw a black background
	backgroundBlack->Draw(x, y - 84);
	hudBoard->Draw(x + HUDBOARD_X, y - HUDBOARD_Y);
	hudItem->Draw(x + HUDITEM_X, y - HUDITEM_Y);
	marioType->Draw(x + MARIOTYPE_X, y - HUD_CHAR_HEIGHT_LTS);
	world->Draw(x + WORLD_X, y - HUD_CHAR_HEIGHT_CSS);

	for (int i = 0; i < life.size(); i++)
	{
		life[i]->Draw(x + HUD_CHAR_WIDTH_L + HUD_CHAR_WIDTH * i, y - HUD_CHAR_HEIGHT_LTS);
	}

	for (int i = 0; i < time.size(); i++)
	{
		time[i]->Draw(x + HUD_CHAR_WIDTH_T + HUD_CHAR_WIDTH * i, y - HUD_CHAR_HEIGHT_LTS);
	}

	for (int i = 0; i < score.size(); i++)
	{
		score[i]->Draw(x + HUD_CHAR_WIDTH_S + HUD_CHAR_WIDTH * i, y - HUD_CHAR_HEIGHT_LTS);
	}

	for (int i = 0; i < coin.size(); i++)
	{
		coin[i]->Draw(x + HUD_CHAR_WIDTH_C + HUD_CHAR_WIDTH * i, y - HUD_CHAR_HEIGHT_CSS);
	}

	for (int i = 0; i < storePowerNull.size(); i++)
	{
		storePowerNull[i]->Draw(x + HUD_CHAR_WIDTH_S + HUD_CHAR_WIDTH * i, y - HUD_CHAR_HEIGHT_CSS);
	}

	for (int i = 0; i < storePowerNullStack; i++)
	{
		storePower[i]->Draw(x + HUD_CHAR_WIDTH_S + HUD_CHAR_WIDTH * i, y - HUD_CHAR_HEIGHT_CSS);
	}

}

vector<LPSPRITE> CHUD::StringToSprite(string str)
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

LPSPRITE CHUD::getHUD(char a)
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


