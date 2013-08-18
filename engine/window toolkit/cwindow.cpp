#include "cwindow.h"
#include "cscreen.h"

void CWindow::Emit(Signal *s)
{
	CScreen *screen=screen->i();
	screen->Emit(s);
}

bool CWindow::Process(Signal *s)
{
	return false;
}

CWindow::CWindow(CWindow *parent)
{
	_X=0;
	_Y=0;
	Width=0;
	Height=0;
	_IsInvalid=false;
	_IsFocused=false;
	_IsVisible=true;
	Parent=parent;
	if (parent!=NULL)
		parent->AddChildWindow(this);
	Screen=Screen->i();
	OnCreate();
	_ID=0;
	_IsActive=true;
}

float CWindow::AbsoluteX()
{
	float x=X();
	CWindow *w=Parent;
	while(w!=NULL)
	{
		x+=w->X();
		w=w->Parent;
	}
	return x;
}

float CWindow::AbsoluteY()
{
	float y=Y();
	CWindow *w=Parent;
	while(w!=NULL)
	{
		y+=w->Y();
		w=w->Parent;
	}
	return y;
}

void CWindow::SetParent(CWindow *parent)
{
	Parent=parent;
}

bool CWindow::OnButton(int ID)
{
	return true;	
}

float CWindow::GetWidth(){return Width;}

float CWindow::GetHeight(){return Height;}

float CWindow::X(){return _X;}

float CWindow::Y(){return _Y;}

CWindow *CWindow::GetParent()
{
	return Parent;
}


CWindow::~CWindow(void)
{

}

void CWindow::SetPosition(float x,float y)
{
	_X=x;
	_Y=y;
}

void CWindow::OnClose()
{

}


int CWindow::OnTimer(float interval)
{
	return 0;
}

int CWindow::OnClick(float x,float y,int button){return 1;}


int CWindow::OnMouseDown(float x,float y,int button)
{ 
	return 0;
}

void CWindow::ScreenSetup(void)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void CWindow::ScreenCleanup(void)
{
	glEnable(GL_DEPTH_TEST);
}

void CWindow::SetDimensions(float w,float h)
{
	Width=w;
	Height=h;
}


int CWindow::OnMouseUp(float x,float y,int button)
{ 
	if (_IsVisible==false)
		return 0;
	for(int i=0;i<ChildWindows.size();i++)
	{
		CWindow *Child=ChildWindows.at(i);
		if (Child->_X<x && Child->_X+Child->Width>x && Child->_Y<y && Child->_Y+Child->Height>y)
		{
			if (Screen->MouseDown==Child)
				Child->OnClick(x-Child->_X,y-Child->_Y,button);
			Child->OnMouseUp(x-Child->_X,y-Child->_Y,button);
		}
	}
	Screen->MouseDown=NULL;
	return 0;
}

int CWindow::OnCreate()
{
	return 0;
}


int CWindow::OnKeyDown(sf::Event::KeyEvent key){return 0;}

int CWindow::OnKeyUp(sf::Event::KeyEvent key){return 0;}

int CWindow::OnEvent(sf::Event Event)
{
	return 0;
}

void CWindow::AddChildWindow(CWindow *window)
{
	window->SetParent(this);
	for (int i=0;i<ChildWindows.size();i++)
	{
		if (ChildWindows[i]==window)
			return;
	}
	ChildWindows.push_back(window);
}

int CWindow::OnDraw(void)
{ 
	return 0;
}

void CWindow::Invalidate(void)
{
	Screen->Invalidate(this);
}

int CWindow::OnMouseIn(void){return 0;}

int CWindow::OnMouseOut(void){return 0;}

vector<CWindow *> CWindow::GetChildren()
{
	return ChildWindows;
}


int CWindow::OnMouseMove(float x,float y)
{
	int oldfocus;
	if (_IsVisible==false)
		return 0;
	for(int i=0;i<ChildWindows.size();i++)
	{
		CWindow *Child=ChildWindows.at(i);
		oldfocus=Child->_IsFocused;
		if (x>=Child->_X && x<=Child->_X+Child->Width && y>=Child->_Y && y<=Child->_Y+Child->Height)
		{
			Child->_IsFocused=1;
			Screen->SetFocus(Child);
			Child->OnMouseMove(x-Child->_X,y-Child->_Y);
		}
		else
		{
			if (Child->_IsFocused)
				Screen->SetFocus(NULL);
			Child->_IsFocused=0;
		}
	}
	return 0;
}