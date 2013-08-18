#ifndef _CWINDOW
#define _CWINDOW 1

#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>


#define NO_SDL_GLEXT
#include <GL/glew.h>

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <time.h>
#include <GL/glu.h>

#include <CG/cg.h>

#include "cscreen.h"
#include "csignal.h"

using namespace std;

class CWindow
{
public:
	CWindow(CWindow *parent);
	~CWindow();
	/*Event handlers*/
	virtual void OnClose();
	virtual int OnTimer(float interval);
	virtual int OnClick(float x,float y,int button);
	virtual int OnMouseDown(float x,float y,int button);
	virtual int OnMouseUp(float x,float y,int button);
	virtual int OnKeyDown(sf::Event::KeyEvent key);
	virtual int OnKeyUp(sf::Event::KeyEvent key);
	virtual int OnDraw(void);
	virtual int OnMouseIn(void);
	virtual int OnMouseOut(void);
	virtual int OnMouseMove(float x,float y);
	virtual bool OnButton(int _ID);

	virtual int CWindow::OnEvent(sf::Event Event);

	virtual int OnCreate();
	virtual void ScreenSetup(void);
	virtual void ScreenCleanup(void);
	vector<CWindow *> GetChildren();

	int ID(){return _ID;};
	int ID(int id){_ID=id;return _ID;};
	void AddChildWindow(CWindow *window);
	void Invalidate(void);
	void SetPosition(float x,float y);
	void SetDimensions(float w,float h);
	CWindow *GetParent();
	void SetParent(CWindow *parent);
	float GetWidth();
	bool IsVisible(){return _IsVisible;};
	bool IsFocused(){return _IsFocused;};
	void Emit(Signal *s);
	virtual bool Process(Signal *s);
	bool IsInvalid(){return _IsInvalid;};
	bool IsActive(){return _IsActive;};
	void Hide(){_IsVisible=false;};
	void Show(){_IsVisible=true;};
	void Activate(){_IsActive=true;};
	void Deactivate(){_IsActive=false;};
	float GetHeight();
	float X();
	float Y();
	float AbsoluteX();
	float AbsoluteY();
private:
protected:
	int _ID;
	CScreen *Screen;
	CWindow *Parent;
	float _X,_Y;
	bool _IsVisible;
	bool _IsActive;
	float Width,Height;
	vector<CWindow *> ChildWindows;
	bool _IsFocused,_IsInvalid;
};

#endif
