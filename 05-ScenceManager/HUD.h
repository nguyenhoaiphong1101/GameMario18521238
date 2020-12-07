
#include "GameObject.h"

class HUD : public CGameObject
{
	float x_default;
	float y_default;

public:
	HUD(float x, float y) 
	{
		this->x = x;
		this->y = y;
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};