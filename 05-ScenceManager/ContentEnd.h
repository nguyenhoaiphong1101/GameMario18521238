#pragma once
#include "GameObject.h"

#define TYPECONTENT 0
#define TYPEMUSH 1
#define TYPESTAR 2
#define TYPETREE 3

class ContentEnd : public CGameObject
{
	bool show=false;
public:
	int type;
	ContentEnd(int a) { type = a; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
};