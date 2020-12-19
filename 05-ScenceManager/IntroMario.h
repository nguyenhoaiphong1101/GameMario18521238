
#include "GameObject.h"

#define INTRO_TYPE_BACKGROUNDBLACK 0
#define INTRO_TYPE_FLOOR 1
#define INTRO_TYPE_ICON_BLACK 2
#define INTRO_TYPE_ICON_COLOR 3
#define INTRO_TYPE_ICON_CHANGE_COLOR 4
#define INTRO_TYPE_ARROW 5
#define INTRO_TYPE_CURTAIN 6
#define INTRO_TYPE_MARIO_LEFT 7
#define INTRO_TYPE_MARIO_RIGHT 8


#define INTRO_ANI_BACKGROUNDBLACK 0
#define INTRO_ANI_FLOOR 1
#define INTRO_ANI_ICON_BLACK 2
#define INTRO_ANI_ICON_COLOR 3
#define INTRO_ANI_ICON_CHANGE_COLOR 4
#define INTRO_ANI_ARROW 5
#define INTRO_ANI_CURTAIN 6
#define INTRO_ANI_MARIO_LEFT 7
#define INTRO_ANI_MARIO_RIGHT 8


class CIntroMario : public CGameObject
{
	int typeIntro;
	bool first = false;
	bool second = false;
	DWORD time;
public:
	CIntroMario(int type);
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
	int getType() { return typeIntro; }
};
