#include "PlayScence.h"
#include "Grid.h"

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

#define OBJECT_TYPE_PORTAL	50

CGrid::CGrid(LPCWSTR filePath)
{
	Load(filePath);
}

void CGrid::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens.size() < 4) return; // skip invalid lines

	cellWidth = atoi(tokens[0].c_str());
	cellHeight = atoi(tokens[1].c_str());
	numCol = atoi(tokens[2].c_str());
	numRow = atoi(tokens[3].c_str());

	cells = new LPCELL[numCol];
	for (int i = 0; i < numCol; i++)
	{
		cells[i] = new Cell[numRow];
	}
}

void CGrid::_ParseSection_OBJECTS(string line)
{
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	if (tokens.size() < 4) return; // skip invalid lines

	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());

	int cellX = atoi(tokens[5].c_str());
	int cellY = atoi(tokens[6].c_str());

	int type = atoi(tokens[0].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CGameObject* obj = NULL;
	switch (type)
	{
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
		int boomerang_id = atof(tokens[4].c_str());
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
		DebugOut(L"[ERR] Invalid object type: %d\n", type);
		return;
	}
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	if (obj != NULL)
	{
		int add = 0;
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		if (id == 4)
			obj->SetRenderLayer(atoi(tokens[4].c_str()));
		obj->SetOrigin(x, y, obj->GetState());
		cells[cellX][cellY].Add(obj);
		obj->SetisOriginObj(false);
	}

}

void CGrid::Load(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading grid resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section;

	char str[MAX_GRID_LINE];

	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") {
			section = GRID_SECTION_SETTINGS; continue;
		}
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		//
		// data section
		//
		switch (section)
		{
		case GRID_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GRID_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);
}

void CGrid::GetObjects(vector<LPGAMEOBJECT>& listObject, int CamX, int CamY)
{
	//listObject.clear();

	int left, top, right, bottom;
	int i, j, k;

	left = ((CamX) / cellWidth);
	right = (CamX + 380) / cellWidth;
	if (((CamX + 380) % cellWidth) != 0)
		right++;
	top = (CamY) / cellHeight;
	bottom = (CamY + 250) / cellHeight;

	LPGAMEOBJECT obj;

	if (right < 0 || left > numCol || bottom < 0 && top > numRow)
	{
		return;
	}

	if (right > numCol)
	{
		right = numCol;
	}
	if (bottom > numRow)
	{
		bottom = numRow;
	}
	if (left < 0)
	{
		left = 0;
	}
	if (top < 0)
	{
		top = 0;
	}

	for (i = left; i < right; i++)
	{
		for (j = top; j < bottom; j++)
		{
			if (cells)
				if (cells[i][j].GetListObjects().size() > 0)
				{
					for (k = 0; k < cells[i][j].GetListObjects().size(); k++)
					{
						if (!cells[i][j].GetListObjects().at(k)->Actived)
						{
							float Ox, Oy;
							cells[i][j].GetListObjects().at(k)->GetOriginLocation(Ox, Oy);

							listObject.push_back(cells[i][j].GetListObjects().at(k));

							if (!((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->IsInUseArea(Ox, Oy))// && cells[i][j].GetListObjects().at(k)->GetState() > 10)
							{
								cells[i][j].GetListObjects().at(k)->reset();
							}





							cells[i][j].GetListObjects().at(k)->SetActive(true);
						}
					}
				}
		}
	}
}

void CGrid::Unload()
{
	if (this != nullptr)
		if (cells)
		{
			for (int i = 0; i < numCol; i++)
			{
				for (int j = 0; j < numRow; j++)
				{
					cells[i][j].Unload();
				}
			}
			delete cells;
			cells = NULL;
		}
}