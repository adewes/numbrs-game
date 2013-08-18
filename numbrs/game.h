#ifndef _GAME

#define _GAME

#include <engine/window toolkit/cwindow.h>
#include <engine/window toolkit/clabel.h>

class Game : public CWindow
{
public:
	Game(CWindow *parent,float w,float h);
	void Setup();
	virtual int OnEvent(sf::Event Event);
	virtual int OnTimer(float interval);
	virtual int OnDraw();
private:
	CLabel *Equation;
	CLabel *Points;
	float TimeElapsed;
};

#endif