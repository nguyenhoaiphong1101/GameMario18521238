#pragma once
#include "Game.h"
#include <iostream>
#include <fstream>
#include "Textures.h"
#include "Scence.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "NoCollision.h"
#include "Box.h"
#include "Drain.h"
#include "Fire.h"
#include "HUD.h"
#include "Coin.h"
#include "BrickQuestion.h"
#include "FlowerAttack.h"
#include "GoombaPara.h"
#include "KoopaPara.h"
#include "Card.h"
#include "IntroMario.h"
#include "FireFlower.h"
#include "MarioSwitchMap.h"
#include "BrickBroken.h"
#include "RectangleMove.h"
#include "KoopaBoomerang.h"
#include "Boomerang.h"
#include "ContentEnd.h"
#include "Cell.h"
#include "Grid.h"

#define MAX_RENDER_LAYER 4

class CPlayScene: public CScene
{
protected: 
	Map* map;
	CMario *player;		
	
	CGrid* grid;// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objectsW;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_GRID(string line);
	


	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	void addObject(CGameObject* a) { objects.push_back(a); };
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	bool IsInUseArea(float Ox, float Oy);
	void SwapButton();
	void ChoosePlayer();
	void runLeft();
	void runRight();
	void runUp();
	void runDown();
	void ChooseMap();

	vector<LPGAMEOBJECT> getObject() { return objects; };
	CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler 
{
	
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) ;
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

