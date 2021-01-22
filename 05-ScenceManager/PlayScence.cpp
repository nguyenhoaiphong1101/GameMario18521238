
#include "PlayScence.h"






using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP				7
#define SCENE_SECTION_GRID				8

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_NOCOLLISION	4
#define OBJECT_TYPE_BOX	5
#define OBJECT_TYPE_DRAIN	6
#define OBJECT_TYPE_HUD	7
#define OBJECT_TYPE_COIN	8
#define OBJECT_TYPE_BRICK_QUESTION	9
#define OBJECT_TYPE_FLOWER_RED	10
#define OBJECT_TYPE_FLOWER_FIRE	11
#define OBJECT_TYPE_BRICK_QUESTION_SPECIAL	12
#define OBJECT_TYPE_GOOMBAPARA	13
#define OBJECT_TYPE_KOOPAPARA	14
#define OBJECT_TYPE_FLOWER_GREEN	15
#define OBJECT_TYPE_FLOWER_NORMAL	16
#define OBJECT_TYPE_INTRO_TYPE_BACKGROUNDBLACK	17
#define OBJECT_TYPE_INTRO_TYPE_FLOOR	18
#define OBJECT_TYPE_INTRO_TYPE_ICON_BLACK	19
#define OBJECT_TYPE_INTRO_TYPE_ICON_COLOR	20
#define OBJECT_TYPE_INTRO_TYPE_ICON_CHANGE_COLOR	21
#define OBJECT_TYPE_INTRO_TYPE_ARROW	22
#define OBJECT_TYPE_INTRO_TYPE_CURTAIN	23
#define OBJECT_TYPE_MARIO_SWITCH_MAP	24
#define OBJECT_TYPE_BRICK_BROKEN	25
#define OBJECT_TYPE_BRICK_QUESTION_EFFECT	26
#define OBJECT_TYPE_BRICK_QUESTION_SPECIAL_GREEN	27
#define OBJECT_TYPE_CARD	28
#define OBJECT_TYPE_RETANGLE_MOVE	29
#define OBJECT_TYPE_BOOMERANG_ENEMY	30
#define OBJECT_TYPE_BOOMERANG	31
#define OBJECT_TYPE_CONTENTEND	32
#define OBJECT_TYPE_CONTENTEND_MUSH	33
#define OBJECT_TYPE_CONTENTEND_STAR	34
#define OBJECT_TYPE_CONTENTEND_TREE	35
#define OBJECT_TYPE_CONTENTEND_MUSH_GHOST	36
#define OBJECT_TYPE_CONTENTEND_STAR_GHOST	37
#define OBJECT_TYPE_CONTENTEND_TREE_GHOST	38

#define OBJECT_ANI_SET_FIRE	9

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::SwapButton()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CIntroMario*>(obj))
		{
			CIntroMario* intro = dynamic_cast<CIntroMario*>(obj);
			if (intro->getType() == INTRO_TYPE_ARROW)
			{
				intro->swapbutton();
			}
		}
	}
}

void CPlayScene::ChoosePlayer()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CIntroMario*>(obj))
		{
			CIntroMario* intro = dynamic_cast<CIntroMario*>(obj);
			if (intro->getType() == INTRO_TYPE_ARROW)
			{
				if (intro->getFirst())
				{
					CPortal* p = new CPortal(2);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}
			}
		}
	}
}
void CPlayScene::ChooseMap()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CMarioSwitchMap*>(obj))
		{
			CMarioSwitchMap* marioSW = dynamic_cast<CMarioSwitchMap*>(obj);
			if (marioSW->getFirst())
			{
				if (marioSW->getFirst())
				{
					CPortal* p = new CPortal(3);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}
			}
			if (marioSW->getFourth())
			{
				if (marioSW->getFourth())
				{
					CPortal* p = new CPortal(4);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}
			}
		}
	}
}

void CPlayScene::runLeft()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CMarioSwitchMap*>(obj))
		{
			CMarioSwitchMap* marioSM = dynamic_cast<CMarioSwitchMap*>(obj);
			marioSM->runLeft();
		}
	}
}
void CPlayScene::runRight()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CMarioSwitchMap*>(obj))
		{
			CMarioSwitchMap* marioSM = dynamic_cast<CMarioSwitchMap*>(obj);
				marioSM->runRight();
				int a = marioSM->x;
		}
	}
}
void CPlayScene::runDown()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CMarioSwitchMap*>(obj))
		{
			CMarioSwitchMap* marioSM = dynamic_cast<CMarioSwitchMap*>(obj);

			marioSM->runDown();
		}
	}
}
void CPlayScene::runUp()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CMarioSwitchMap*>(obj))
		{
			CMarioSwitchMap* marioSM = dynamic_cast<CMarioSwitchMap*>(obj);
			marioSM->runUp();
		}
	}
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	CGameObject* objW = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_NOCOLLISION: obj = new CNoCollision(); break;
	case OBJECT_TYPE_BOX: obj = new CBox(); break;
	case OBJECT_TYPE_DRAIN: obj = new CDrain(); break;
	case OBJECT_TYPE_HUD: obj = new CHUD(); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(COIN); break;
	case OBJECT_TYPE_BRICK_QUESTION: obj = new CBrickQuestion(BRICK_QUESTION_STATUS_COIN); break;
	case OBJECT_TYPE_FLOWER_RED:	  obj = new CFlowerAttack(FLOWER_RED); break;
	case OBJECT_TYPE_FLOWER_FIRE:	  obj = new CFireFlower(); break;
	case OBJECT_TYPE_BRICK_QUESTION_SPECIAL:	  obj = new CBrickQuestion(BRICK_QUESTION_STATUS_SPECIAL); break;
	case OBJECT_TYPE_BRICK_QUESTION_SPECIAL_GREEN:	  obj = new CBrickQuestion(BRICK_QUESTION_STATUS_MUSHROOM_GREEN); break;
	case OBJECT_TYPE_BRICK_QUESTION_EFFECT:	  obj = new CBrickQuestion(BRICK_QUESTION_STATUS_EFFECT); break;
	case OBJECT_TYPE_GOOMBAPARA:	  obj = new CGoombaPara(); break;
	case OBJECT_TYPE_KOOPAPARA:	  obj = new CKoopaPara(); break;
	case OBJECT_TYPE_FLOWER_GREEN:	  obj = new CFlowerAttack(FLOWER_GREEN); break;
	case OBJECT_TYPE_FLOWER_NORMAL:	  obj = new CFlowerAttack(FLOWER_NORMAL); break;
	case OBJECT_TYPE_INTRO_TYPE_BACKGROUNDBLACK:	  obj = new CIntroMario(INTRO_TYPE_BACKGROUNDBLACK); break;
	case OBJECT_TYPE_INTRO_TYPE_FLOOR:	  obj = new CIntroMario(INTRO_TYPE_FLOOR); break;
	case OBJECT_TYPE_INTRO_TYPE_ICON_BLACK:	  obj = new CIntroMario(INTRO_TYPE_ICON_BLACK); break;
	case OBJECT_TYPE_INTRO_TYPE_ICON_COLOR:	  obj = new CIntroMario(INTRO_TYPE_ICON_COLOR); break;
	case OBJECT_TYPE_INTRO_TYPE_ICON_CHANGE_COLOR:	  obj = new CIntroMario(INTRO_TYPE_ICON_CHANGE_COLOR); break;
	case OBJECT_TYPE_INTRO_TYPE_ARROW:	  obj = new CIntroMario(INTRO_TYPE_ARROW); break;
	case OBJECT_TYPE_INTRO_TYPE_CURTAIN:	  obj = new CIntroMario(INTRO_TYPE_CURTAIN); break;
	case OBJECT_TYPE_MARIO_SWITCH_MAP:	  obj = new CMarioSwitchMap(); break;
	case OBJECT_TYPE_BRICK_BROKEN:	  obj = new CBrickBroken(); break;
	case OBJECT_TYPE_CARD:	  obj = new CCard(); break;
	case OBJECT_TYPE_RETANGLE_MOVE:	  obj = new CRectangleMove(); break;
	case OBJECT_TYPE_CONTENTEND:	  obj = new ContentEnd(0); break;
	case OBJECT_TYPE_CONTENTEND_MUSH:	  obj = new ContentEnd(1); break;
	case OBJECT_TYPE_CONTENTEND_STAR:	  obj = new ContentEnd(2); break;
	case OBJECT_TYPE_CONTENTEND_TREE:	  obj = new ContentEnd(3); break;
	case OBJECT_TYPE_CONTENTEND_MUSH_GHOST:	  obj = new ContentEnd(4); break;
	case OBJECT_TYPE_CONTENTEND_STAR_GHOST:	  obj = new ContentEnd(5); break;
	case OBJECT_TYPE_CONTENTEND_TREE_GHOST:	  obj = new ContentEnd(6); break;
	case OBJECT_TYPE_BOOMERANG_ENEMY:
		obj = new CKoopaBoomerang();
		break;
	case OBJECT_TYPE_BOOMERANG:
	{
		int boomerang_id = atof(tokens[5].c_str());
		obj = new CBoomerang(boomerang_id);
	}
	break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (obj != NULL)
	{
			obj->SetPosition(x, y);
			obj->SetAnimationSet(ani_set);
			obj->SetOrigin(x, y, obj->GetState());
			if(id==4)
			obj->SetRenderLayer(atoi(tokens[4].c_str()));
			obj->SetisOriginObj(true);
			objects.push_back(obj);
	}
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return; // skip invalid lines

	int idTileSet = atoi(tokens[0].c_str());
	int totalRowsTileSet = atoi(tokens[1].c_str());
	int totalColumnsTileSet = atoi(tokens[2].c_str());
	int totalRowsMap = atoi(tokens[3].c_str());
	int totalColumnsMap = atoi(tokens[4].c_str());
	int totalTiles = atoi(tokens[5].c_str());
	wstring file_path = ToWSTR(tokens[6]);

	map = new Map(idTileSet, totalRowsTileSet, totalColumnsTileSet, totalRowsMap, totalColumnsMap, totalTiles);
	map->LoadMap(file_path.c_str());
	map->ExtractTileFromTileSet();
}

void CPlayScene::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring file_path = ToWSTR(tokens[0]);

	if (grid == NULL)
		grid = new CGrid(file_path.c_str());
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[GRID]") {
			section = SCENE_SECTION_GRID; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_GRID: _ParseSection_GRID(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	if (player != NULL)
		if (player->GetState() == MARIO_STATE_SHOOT_FIRE)
		{
			CGameObject* obj = NULL;
			obj = new CFire();
			if (player->nx == 1)
			{
				obj->SetPosition(player->x + MARIO_FIRE_BBOX_WIDTH, player->y + (MARIO_FIRE_BBOX_HEIGHT - FIRE_BBOX_WIDTH) / 4);
				obj->vx = FIRE_SPEED;
				obj->nx = 1;

			}
			else
			{
				obj->SetPosition(player->x - FIRE_BBOX_WIDTH, player->y + (MARIO_FIRE_BBOX_HEIGHT - FIRE_BBOX_WIDTH) / 4);
				obj->vx = -FIRE_SPEED;
				obj->nx = -1;

			}

			LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_ANI_SET_FIRE);
			obj->SetAnimationSet(ani_set);
			objects.push_back(obj);
		}



	CGame* game = CGame::GetInstance();

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{

		LPGAMEOBJECT obj = objects[i];
		if (obj->isDisAppear)
		{
			objects.erase(objects.begin() + i);
			delete obj;
		}
		else
		{
			if (player != NULL)
			{
				int id = CGame::GetInstance()->GetCurrentScene()->GetId();
				if (id == 4)
				{
					/*if (obj->x <= CGame::GetInstance()->GetCamPosX()+400)
					{
						objects[i]->Update(dt, &coObjects);
					}*/
				}
				else
				{
					if (obj->x <= player->x + game->GetScreenWidth())
					{
						if (dynamic_cast<CHUD*>(obj))
						{
							objects[i]->Update(dt, &coObjects);
						}
						else if (obj->y >= player->y - game->GetScreenHeight() && obj->y <= player->y + game->GetScreenHeight())
							objects[i]->Update(dt, &coObjects);
					}
				}
			}
			else
				objects[i]->Update(dt, &coObjects);
		}

	}
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	if (id == 4)
	{
		float cx = game->GetCamPosX();

		float cy = game->GetCamPosY();

		for (size_t i = 0; i < objects.size(); i++)
		{
			float Ox, Oy;
			objects[i]->GetPosition(Ox, Oy);
			if (!IsInUseArea(Ox, Oy) && !objects[i]->GetisOriginObj())
			{
				objects[i]->SetActive(false);
				objects.erase(objects.begin() + i);
			}
		}

		grid->GetObjects(objects, cx, cy);
		if (player != NULL)
			player->GetPosition(cx, cy);


		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &objects);
		}

	}
	
	
	//CGame::GetInstance()->SetCamPos((int)0, (int)220);
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	if (player->x < 0) player->x = 0; //Chống lùi qa trái

	// Update camera to follow mario


}

void CPlayScene::Render()
{
	if (map)
	{
		this->map->Render();
	}
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	if (id == 4)
	{
		vector<LPGAMEOBJECT> render[MAX_RENDER_LAYER];

		for (size_t i = 0; i < objects.size(); i++)
		{
			render[objects[i]->GetRenderLayer() - 1].push_back(objects[i]);
		}
		for (int i = 0; i < MAX_RENDER_LAYER; i++)
		{
			for (size_t j = 0; j < render[i].size(); j++)
				render[i][j]->Render();
		}
	}
	else
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render();
		}
	}
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;
	grid->Unload();

	grid = nullptr;

	delete grid;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

bool CPlayScene::IsInUseArea(float Ox, float Oy)
{
	float CamX, CamY;

	CamX = CGame::GetInstance()->GetCamPosX();

	CamY = CGame::GetInstance()->GetCamPosY();

	if (((CamX < Ox + 50) && (Ox < CamX + 380)) && ((CamY < Oy) && (Oy < CamY + 250)))
		return true;
	return false;
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CGame* game = CGame::GetInstance();
	int ids = CGame::GetInstance()->GetCurrentScene()->GetId();


	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario != NULL)
	{
		if (mario->GetState() != MARIO_STATE_DRAIN_1 && mario->GetState() != MARIO_STATE_DRAIN_2&& mario->GetState() != MARIO_STATE_DRAIN_3 && mario->checkEnd == false && mario->GetState() != MARIO_STATE_DIE)
		{
			switch (KeyCode)
			{
			case DIK_S:
				if (mario->checkjumping == 0)
				{
					if (mario->GetSpeed() == 7 && mario->GetLevel() == MARIO_LEVEL_FOX)
					{
						mario->flyCan = true;
						mario->SetState(MARIO_STATE_FLY);
						mario->timeFly = GetTickCount();
					}
					else if (game->IsKeyDown(DIK_LSHIFT))
					{
						mario->SetState(MARIO_STATE_JUMP_HIGH);
					}
					else
					{
						mario->SetState(MARIO_STATE_JUMP);
					}

				}
				else
				{
					if (mario->GetLevel() == MARIO_LEVEL_FOX)
					{
						mario->landingCheck = true;
					}
				}
				break;
			case DIK_R:
				mario->Reset();
				break;
			case DIK_E:
				if (ids == 4)
				{
					mario->MovetoLocation();
				}
				break;
			case DIK_A:
				if (mario->GetLevel() == MARIO_LEVEL_FIRE)
				{
					if (mario->vx == 0)
						mario->SetState(MARIO_STATE_SHOOT_FIRE);
				}
				if (mario->GetLevel() == MARIO_LEVEL_FOX)
				{
					mario->attackCheck = GetTickCount();
					mario->attack = true;

				}
				mario->holdKoopas = true;
				break;
			case DIK_I:
				mario->y -= MARIO_BIG_BBOX_HEIGHT;
				mario->SetLevel(MARIO_LEVEL_FIRE);
				break;
			case DIK_DOWN:
				mario->sit = true;
				break;
			case DIK_O:
				mario->y -= MARIO_BIG_BBOX_HEIGHT;
				mario->SetLevel(MARIO_LEVEL_FOX);
				break;
			}
		}
	}
	else
	{
		switch (KeyCode)
		{
		case DIK_RIGHT:
		{
			((CPlayScene*)scence)->runRight();
			break;
		}
		case DIK_LEFT:
		{
			((CPlayScene*)scence)->runLeft();
			break;
		}


		case DIK_UP:
		{
			((CPlayScene*)scence)->runUp();
			((CPlayScene*)scence)->SwapButton();
			break;
		}
		case DIK_DOWN:
		{
			((CPlayScene*)scence)->runDown();
			((CPlayScene*)scence)->SwapButton();
			break;
		}
		case DIK_A:
		{
			((CPlayScene*)scence)->ChoosePlayer();
			((CPlayScene*)scence)->ChooseMap();
			break;
		}
		default:
			break;
		}
	}


}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CGame* game = CGame::GetInstance();


	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario != NULL)
	{
		if (mario->GetState() != MARIO_STATE_DRAIN_1 && mario->GetState() != MARIO_STATE_DRAIN_2&& mario->GetState() != MARIO_STATE_DRAIN_3 && mario->GetState() != MARIO_STATE_DIE && mario->checkEnd == false)
		{
			switch (KeyCode)
			{

			case DIK_A:
				mario->holdKoopas = false;
				mario->holdKoopasCol = false;
				mario->attack = false;
				mario->stopRun = GetTickCount();
				mario->startRun = 0;
				break;
			case DIK_S:
				if (mario->flyCan == true)
				{
					mario->SetState(MARIO_STATE_LANDING);
					mario->landingCheck = true;
				}
				mario->flyCan = false;
				mario->timeFly = 0;
				mario->landingCheck = false;
				/*mario->holdKoopasCol = false;*/
				break;
			case DIK_DOWN:
				mario->sit = false;
				if (mario->GetLevel() != MARIO_LEVEL_SMALL)
					mario->y -= MARIO_SIT_BBOX_HEIGHT;
				break;
			case DIK_RIGHT:
				mario->stopRun = GetTickCount();
				mario->startRun = 0;
			case DIK_LEFT:
				mario->stopRun = GetTickCount();
				mario->startRun = 0;

			default:
				break;
			}
		}
	}


}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario != NULL)
	{
		if (mario->GetState() == MARIO_STATE_DIE) return;

		if (mario->GetState() != MARIO_STATE_DRAIN_1 && mario->GetState() != MARIO_STATE_DRAIN_2&& mario->GetState() != MARIO_STATE_DRAIN_3)
		{
			if (game->IsKeyDown(DIK_RIGHT))
			{
				if (game->IsKeyDown(DIK_A))
				{
					mario->SetState(MARIO_STATE_WALKING_RIGHT_FAST);
					if (mario->vx != 0)
					{
						if (mario->startRun == 0)
						{
							mario->startRun = GetTickCount();
							mario->stopRun = 0;
						}

					}
				}
				else
					mario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
			else if (game->IsKeyDown(DIK_LEFT))
			{
				if (game->IsKeyDown(DIK_A))
				{
					mario->SetState(MARIO_STATE_WALKING_LEFT_FAST);
					if (mario->vx != 0)
					{
						if (mario->startRun == 0)
						{
							mario->startRun = GetTickCount();
							mario->stopRun = 0;
						}
					}
				}
				else
					mario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			/*else if (game->IsKeyDown(DIK_R))
			{
				if (mario->GetLevel() == MARIO_LEVEL_FOX)
					mario->SetState(MARIO_STATE_ATTACK);
			}*/
			else
				mario->SetState(MARIO_STATE_IDLE);
		}
	}


}

