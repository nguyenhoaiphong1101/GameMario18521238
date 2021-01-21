
#include "GameObject.h"
#define KHOANGCACH_X 31
#define KHOANGCACH_Y 31

class CMarioSwitchMap : public CGameObject
{
	bool first = false;
	bool second = false;
	bool fourth = false;
	DWORD time;
public:
	CMarioSwitchMap() { vx = 0; vy = 0; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	
	bool getFirst() { return first; };
	bool getSecond() { return second; };
	bool getFourth() { return fourth; };
	void runLeft();
	void runRight();
	void runUp();
	void runDown();
};
