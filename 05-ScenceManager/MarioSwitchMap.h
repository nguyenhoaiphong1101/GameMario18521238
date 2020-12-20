
#include "GameObject.h"
#define KHOANGCACH_X 31
#define KHOANGCACH_Y 31

class CMarioSwitchMap : public CGameObject
{
	bool first = false;
	bool second = false;
	DWORD time;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void swapbutton()
	{
		if (first == true)
		{
			second = true;
			first = false;
		}
		else
		{
			first = true;
			second = false;
		}
	};
	bool getFirst() { return first; };
	bool getSecond() { return second; };
	void runLeft();
	void runRight();
	void runUp();
	void runDown();
};
