#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_SPEED_PLUS		0.002f 
#define MARIO_WALKING_SPEED_PLUS1		0.0025f 
#define MARIO_WALKING_RUN_MAX		0.25f 
#define MARIO_WALKING_FLY	0.1f 
#define MARIO_GEARING_MAX	0.051f

#define TIME_FLY	5000



#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_SPEED_Y_HIGH		0.625f
#define MARIO_JUMP_DEFLECT_SPEED 0.3f
#define MARIO_GRAVITY			0.002f
#define MARIO_GRAVITY_FOX			0.0005f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_RIGHT_FAST	110
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_WALKING_LEFT_FAST	210
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_JUMP_HIGH			310
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SHOOT_FIRE				500
#define MARIO_STATE_FLY				501
#define MARIO_STATE_LANDING				502
#define MARIO_STATE_DRAIN_1			503
#define MARIO_STATE_DRAIN_2			504
#define MARIO_STATE_END			505
#define MARIO_STATE_DRAIN_3			506


#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3
#define MARIO_ANI_FIRE_IDLE_RIGHT		9
#define MARIO_ANI_FIRE_IDLE_LEFT			10

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_FIRE_WALKING_RIGHT		11
#define MARIO_ANI_FIRE_WALKING_LEFT		12
#define MARIO_ANI_FIRE_SHOOT_RIGHT		15
#define MARIO_ANI_FIRE_SHOOT_LEFT		16
#define MARIO_ANI_BIG_RUN_RIGHT		17
#define MARIO_ANI_BIG_RUN_LEFT		18
#define MARIO_ANI_BIG_FLY_RIGHT		19
#define MARIO_ANI_BIG_FLY_LEFT		20
#define MARIO_ANI_BIG_GEARING_RIGHT		22 //LẤY ĐÀ PHẢI
#define MARIO_ANI_BIG_GEARING_LEFT		21 //LẤY ĐÀ TRÁI
#define MARIO_ANI_SMALL_RUN_RIGHT		23
#define MARIO_ANI_SMALL_RUN_LEFT		24
#define MARIO_ANI_SMALL_FLY_RIGHT		25
#define MARIO_ANI_SMALL_FLY_LEFT		26
#define MARIO_ANI_SMALL_GEARING_RIGHT		27
#define MARIO_ANI_SMALL_GEARING_LEFT		28
#define MARIO_ANI_FIRE_RUN_RIGHT		29
#define MARIO_ANI_FIRE_RUN_LEFT		30
#define MARIO_ANI_FIRE_FLY_RIGHT		31
#define MARIO_ANI_FIRE_FLY_LEFT		32
#define MARIO_ANI_FIRE_GEARING_RIGHT		33 
#define MARIO_ANI_FIRE_GEARING_LEFT		34 
#define MARIO_ANI_FOX_IDLE_RIGHT		35
#define MARIO_ANI_FOX_IDLE_LEFT		36
#define MARIO_ANI_FOX_WALKING_RIGHT		37
#define MARIO_ANI_FOX_WALKING_LEFT		38
#define MARIO_ANI_FOX_RUN_RIGHT		39
#define MARIO_ANI_FOX_RUN_LEFT		40
#define MARIO_ANI_FOX_JUMP_RIGHT		41
#define MARIO_ANI_FOX_JUMP_LEFT		42
#define MARIO_ANI_FOX_GEARING_RIGHT		43 
#define MARIO_ANI_FOX_GEARING_LEFT		44 
#define MARIO_ANI_FOX_ATTACK		45 
#define MARIO_ANI_BIG_SIT_RIGHT		46
#define MARIO_ANI_BIG_SIT_LEFT		47
#define MARIO_ANI_FIRE_SIT_RIGHT		49
#define MARIO_ANI_FIRE_SIT_LEFT		48 
#define MARIO_ANI_FOX_SIT_RIGHT		50 
#define MARIO_ANI_FOX_SIT_LEFT		51 
#define MARIO_ANI_BIG_HOLDKOOPAS_RIGHT		52
#define MARIO_ANI_BIG_HOLDKOOPAS_LEFT		53 
#define MARIO_ANI_BIG_HOLDKOOPAS_WALK_RIGHT		54
#define MARIO_ANI_BIG_HOLDKOOPAS_WALK_LEFT		55 
#define MARIO_ANI_FOX_FLY_RIGHT		56
#define MARIO_ANI_FOX_FLY_LEFT		57 
#define MARIO_ANI_FOX_LANDING_RIGHT		58
#define MARIO_ANI_FOX_LANDING_LEFT		59 
#define MARIO_ANI_FIRE_HOLDKOOPAS_RIGHT		60
#define MARIO_ANI_FIRE_HOLDKOOPAS_LEFT		61 
#define MARIO_ANI_FIRE_HOLDKOOPAS_WALK_RIGHT		62
#define MARIO_ANI_FIRE_HOLDKOOPAS_WALK_LEFT		63 
#define MARIO_ANI_FOX_HOLDKOOPAS_RIGHT		64
#define MARIO_ANI_FOX_HOLDKOOPAS_LEFT		65 
#define MARIO_ANI_FOX_HOLDKOOPAS_WALK_RIGHT		66
#define MARIO_ANI_FOX_HOLDKOOPAS_WALK_LEFT		67 
#define MARIO_ANI_SMALL_HOLDKOOPAS_RIGHT		68
#define MARIO_ANI_SMALL_HOLDKOOPAS_LEFT		69 
#define MARIO_ANI_SMALL_HOLDKOOPAS_WALK_RIGHT		70
#define MARIO_ANI_SMALL_HOLDKOOPAS_WALK_LEFT		71 

#define MARIO_ANI_BIG_DRAIN		72
#define MARIO_ANI_FIRE_DRAIN		73 
#define MARIO_ANI_FOX_DRAIN		74 
#define MARIO_ANI_SMALL_DRAIN		75 


#define MARIO_ANI_DIE				8

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FIRE		3
#define	MARIO_LEVEL_FOX		4


#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_FIRE_BBOX_WIDTH  15
#define MARIO_FIRE_BBOX_HEIGHT 27
#define MARIO_SIT_BBOX_HEIGHT 18

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_FOX_BBOX_WIDTH  21
#define MARIO_FOX_BBOX_HEIGHT 27

#define MARIO_UNTOUCHABLE_TIME 5000

#define MARIO_TYPE 101

#define MARIO_SCORE 101
#define LANDING_LIMIT 0.05
#define LANDING_LIMIT_SPEED 0.04

#define MARIO_SCORE 100
#define MARIO_TIME_DRAIN 1000
#define MARIO_TIME_DRAIN_1_SPEED	0.05f
#define MARIO_TIME_DRAIN_2_SPEED	0.05f
#define MARIO_TIME_DRAIN_1_X 2103
#define MARIO_TIME_DRAIN_1_Y 270
#define MARIO_TIME_DRAIN_1_Y_DEFAULT 298

#define MARIO_TIME_DRAIN_2_X 2330
#define MARIO_TIME_DRAIN_2_Y 118
#define MARIO_TIME_DRAIN_2_Y_DEFAULT 90
#define MARIO_SCORE 100
#define MARIO_FLY_LEVEL 7
#define MARIO_FLY_LEVEL_SPEED 200

#define MARIO_MAP_Y_4 256
#define MARIO_MAP_X_4 2064
#define MARIO_MAP_X_4_LIMIT 2050
#define MARIO_FLY_LEVEL_SPEED 200


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	int marioScore = 0;
	int marioCoin = 0;
	int marioLife = 3;
	int levelFly = 0;
	DWORD timeKoopas = 0;
	DWORD timeDrain = 0;
	float camX_update = 0;
	


	float start_x;			// initial position of Mario at scene
	float start_y;

public:
	int checkjumping = 0;	//kiểm tra trạng thái nhảy
	bool checkidle = true;	//kiểm tra trạng thái đứng im
	bool attack = false;	//trạng thái tấn công
	bool sit = false;	//trạng thái ngồi
	bool holdKoopas = false;	//trạng thái giữ rùa
	bool holdKoopasCol = false;	//trạng thái giữ rùa
	bool flyCan = false;	//trạng thái bay
	int startRun = 0;	//kiểm tra thời gian có thể bay
	int stopRun = 0;	//kiểm tra thời gian có thể bay
	int timeFly = 0;	//kiểm tra thời gian bay
	bool landingCheck = false;	//kiểm tra hạ cánh
	bool checkFree = false;	
	bool checkEnd = false;	
	int card = 0;
	DWORD timeEnd = 0;
	DWORD attackCheck = 0;
	bool checkRecMove = false;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx, float& min_ty,
		float& nx, float& ny, float& rdx, float& rdy);

	int GetCheckJumping() { return checkjumping; };
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; };
	void MovetoLocation();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetLifeDown() { marioLife--; };
	void SetLifeUp() { marioLife++; };

	int GetSpeed()
	{
		return levelFly;
	};
	int GetCoin()
	{
		return marioCoin;
	};
	void CoinUp()
	{
		marioCoin++;
	};
	void ScoreUp()
	{
		marioScore+=100;
	};
	void LifeUp()
	{
		marioLife++;
	};
	double GetScore()
	{
		return marioScore;
	};
	double GetLife()
	{
		return marioLife;
	};
};