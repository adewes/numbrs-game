/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "cscreen.h"
#include "../logger.h"

#include <sstream>

int CScreen::OnTimer(void)
{
	ActiveWindow->OnTimer(20);
	return 1;
}

void CScreen::UpdateObjectPosition(void)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)MouseX;
	winY = (float)MouseY;
	glReadPixels( MouseX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &ObjX, &ObjY, &ObjZ);
}


void CScreen::UpdateMousePosition(float x,float y)
{
	MouseX=x;
	MouseY=y;
}

void CScreen::Clear()
{
	static int cnt=0;
	ActivateGlow();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DeactivateGlow();

	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glClear(GL_COLOR_BUFFER_BIT);
/*	glColor4f(0.0,0.0,0.0,0.5);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(Width,0);
		glVertex2f(Width,Height);
		glVertex2f(0,Height);
	glEnd();
*/	
}


void CScreen::SetFocus(CWindow *wnd)
{
	Focus=wnd;
}

int CScreen::HandleKeyUp(CWindow *window,sf::Event::KeyEvent key)
{
	return KeyDown->OnKeyUp(key);
}

int CScreen::HandleKeyDown(CWindow *window,sf::Event::KeyEvent key)
{
	KeyDown=window;
	return window->OnKeyDown(key);
}

int CScreen::HandleMouseDown(CWindow *window,float x,float y,int button)
{
	float posx,posy;
	if (window->IsVisible()==false)
		return 0;
	for(int i=0;i<window->GetChildren().size();i++)
	{
		CWindow *Child=window->GetChildren().at(i);
		if (x>=Child->X() && x<=Child->X()+Child->GetWidth() && y>=Child->Y() && y<=Child->Y()+Child->GetHeight())
		{
			if (HandleMouseDown(Child,x-Child->X(),y-Child->Y(),button)==1)
				return 1;
			if (Child->IsVisible())
				if (Child->OnMouseDown(x-Child->X(),y-Child->Y(),button)==1)
				{
					MouseDown=Child;
					return 1;
				}
		}
	}
	if (window->OnMouseDown(x,y,button)==1)
	{
		MouseDown=window;
		return 1;
	}
	return 0;
}

int CScreen::HandleMouseMove(CWindow *window,float x,float y)
{
	float posx,posy;
	if (window->IsVisible()==false)
		return 0;
	for(int i=0;i<window->GetChildren().size();i++)
	{
		CWindow *Child=window->GetChildren().at(i);
		if (x>=Child->X() && x<=Child->X()+Child->GetWidth() && y>=Child->Y() && y<=Child->Y()+Child->GetHeight())
		{
			if (HandleMouseMove(Child,x-Child->X(),y-Child->Y())==1)
				return 1;
			if (Child->IsVisible())
				if (Child->OnMouseMove(x-Child->X(),y-Child->Y())==1)
				{
					return 1;
				}
		}
	}
	if (window->OnMouseMove(x,y)==1)
	{
		return 1;
	}
	return 0;
}


int CScreen::HandleWindowEvent(CWindow *window,sf::Event Event)
{
	float posx,posy;
	for(int i=0;i<window->GetChildren().size();i++)
	{
		CWindow *Child=window->GetChildren().at(i);
		if (HandleWindowEvent(Child,Event)==1)
			return 1;
		if (Child->OnEvent(Event)==1)
			return 1;
	}
	if(window->OnEvent(Event)==1)
		return 1;
	return 0;
}

int CScreen::HandleMouseUp(CWindow *window,float x,float y,int button)
{
	float posx,posy;
	if (window->IsVisible()==false)
		return 0;
	for(int i=0;i<window->GetChildren().size();i++)
	{
		CWindow *Child=window->GetChildren().at(i);
		if (x>=Child->X() && x<=Child->X()+Child->GetWidth() && y>=Child->Y() && y<=Child->Y()+Child->GetHeight())
		{
			if (HandleMouseUp(Child,x-Child->X(),y-Child->Y(),button)==1)
				return 1;
			if (Child->IsVisible())
				if (Child->OnMouseUp(x-Child->X(),y-Child->Y(),button)==1)
				{
					if (Child==MouseDown)
						Child->OnClick(x-Child->X(),y-Child->Y(),button);
					else if (MouseDown!=NULL)
						MouseDown->OnMouseOut();
					return 1;
				}
		}
	}
	if(window->OnMouseUp(x,y,button)==1)
	{
		if (window==MouseDown)
			window->OnClick(x,y,button);
		else if (MouseDown!=NULL)
			MouseDown->OnMouseOut();
		return 1;
	}
	return 0;
}

int CScreen::HandleEvent(sf::Event Event)
{
	int i=0;
	switch(Event.Type)
	{
	case sf::Event::MouseMoved:
		if (HandleMouseMove(ActiveWindow,Event.MouseMove.X,Height-Event.MouseMove.Y))
			return 1;
		UpdateMousePosition(Event.MouseMove.X,Height-Event.MouseMove.Y);
		break;
	case sf::Event::KeyPressed:
		if (HandleKeyDown(ActiveWindow,Event.Key))
			return 1;
		break;
	case sf::Event::MouseButtonPressed:
		if (HandleMouseDown(ActiveWindow,Event.MouseButton.X,Height-Event.MouseButton.Y,Event.MouseButton.Button))
			return 1;
		break;
	case sf::Event::MouseButtonReleased:
		if (HandleMouseUp(ActiveWindow,Event.MouseButton.X,Height-Event.MouseButton.Y,Event.MouseButton.Button))
			return 1;
		break;
	};

	HandleWindowEvent(ActiveWindow,Event);
	return 1;
}

void CScreen::Crossfade(CWindow *window)
{
	BackgroundWindow=NULL;
	SetWindow(window);
}

void CScreen::SetWindow(CWindow *window)
{
	ActiveWindow=window;
	Focus=window;
	Invalidate(ActiveWindow);
}

void CScreen::ProcessSignals()
{
	for(int i=0;i<Signals.size();i++)
	{
		Signal *s = Signals[i];
		CWindow *w=s->source;
		if (w!=NULL)
			w=w->GetParent();
		while (w!=NULL)
		{
			if (w->Process(s))
				break;
			w=w->GetParent();
		}
	}
	Signals.clear();
}

int CScreen::Loop()
{
	int cnt=0;
	while (App.IsOpened())
	{
		float time=Clock.GetElapsedTime();
		ProcessSignals();
		if (time>=0.02)
		{
			Invalidate(ActiveWindow);
			Clock.Reset();
			OnTimer();
		}
		fr=0.99f*fr+0.01f/time;
		if (App.GetInput().IsKeyDown(sf::Key::Escape))
		{
			ActiveWindow->OnClose();
			return 0;
		}
		sf::Event Event;
		while (App.GetEvent(Event))
		{	
			HandleEvent(Event);
		}
//		Sleep(1);
	}
	return 0;
}

void CScreen::Emit(Signal *s)
{
	Signals.push_back(s);
}

void CScreen::DrawWindowAndChilds(CWindow *window)
{
	if (window->IsVisible()==false)
		return;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(window->X(),window->Y(),1);
/*	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(window->GetWidth(),0);
		glVertex2f(window->GetWidth(),window->GetHeight());
		glVertex2f(0,window->GetHeight());
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);*/
	window->ScreenSetup();
	window->OnDraw();
	window->ScreenCleanup();
	for(int i=0;i<window->GetChildren().size();i++)
	{	
		CWindow *Child=window->GetChildren().at(i);
		DrawWindowAndChilds(Child);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//We always redraw the whole screen, due to the present glow effect (which bleeds into adjacent elements). Without the glow, a more efficient drawing algorithm could be devised!
void CScreen::Invalidate(CWindow *window)
{
	if (BackgroundWindow!=NULL)
	{
		DrawWindowAndChilds(BackgroundWindow);
//		glColor4f(0,0,0,0.8);
		glClear(GL_COLOR_BUFFER_BIT);
/*		glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(0,Height);
		glVertex2f(Width,Height);
		glVertex2f(Width,0);
		glEnd();
*/		
		glColor4f(0,0,0,1.0);
		
		ActivateGlow();
			glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(0,Height);
			glVertex2f(Width,Height);
			glVertex2f(Width,0);
			glEnd();
		DeactivateGlow();
	}
	glDisable(GL_DEPTH_TEST);

	if (ActiveWindow!=NULL)
		DrawWindowAndChilds(ActiveWindow);


	glEnable(GL_DEPTH_TEST);

	Flip();
	Clear();
}

void CScreen::MovePosition(float x,float y)
{
	glPushMatrix();
	glTranslatef(x,y,0);
}

void CScreen::RevertPosition(void)
{
	glPopMatrix();
}

float CScreen::Glow()
{
	return _Glow;
}

float CScreen::Glow(float g)
{
	_Glow=g;
	return _Glow;
}


int CScreen::Flip()
{
	pFilterBox->Draw(_Glow);
	stringstream stream;
/*
	stream << "Framerate:" << (int)fr << "\n";
	sf::String Text(stream.str(),ScreenFont,20);
	Text.SetPosition(GetWidth()-200,60);
	Text.SetColor(sf::Color(255, 255, 255));

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	App.Draw(Text);
*/
	App.Display();
	static int screenshots=0;

	if (App.GetInput().IsKeyDown(sf::Key::F10))
	{
	    sf::Image Screen = App.Capture();
		stream.str("");
		stream << "screenshot_" << screenshots++ << ".jpg";
		Screen.SaveToFile(stream.str());
	}

	return 1;
}

void CScreen::Screenshot()
{
}

void CScreen::ActivateGlow()
{
	pFilterBox->Activate(0,0,Width,Height); 
}

void CScreen::DeactivateGlow()
{
	pFilterBox->Deactivate();
}

int CScreen::GetWidth(void)
{
	return Width;
}

int CScreen::GetHeight(void)
{
	return Height;
}

float CScreen::GetMouseX()
{
	return MouseX;
}
float CScreen::GetMouseY()
{
	return MouseY;
}


int CScreen::Setup()
{
	ActiveWindow=NULL;
	MouseDown=NULL;
	BackgroundWindow=NULL;
	fr=0.0;

	_Glow=0.3;

	static wchar_t ourDefaultCharset[] ={
     31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,
     44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,
     57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
     70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,
     83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
     96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
    109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
    148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
    161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173,
    174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
    187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212,
    213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225,
    226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238,
    239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251,
    252, 253, 254, 255, 0
};
	ScreenFont=ScreenFont.GetDefaultFont();
	ScreenFont.LoadFromFile("data/fonts/SAVEDBYZ.TTF",30,ourDefaultCharset);

	FontTexture=ScreenFont.GetImage();
	
	sf::WindowSettings Settings;
	Settings.DepthBits         = 16; // Request a 24 bits depth buffer
	Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 1;  // Request 2 levels of antialiasing

	App.Create(sf::VideoMode(Width, Height, 16), "Strategy",sf::Style::Close,Settings); //,sf::Style::Fullscreen
	App.PreserveOpenGLStates(true);
	App.UseVerticalSync(false);
//	App.SetFramerateLimit(50);
	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
			printf("Ready for OpenGL 2.0\n");
		else {
			MessageBox(NULL,"OpenGL 2.0 not supported\n","",MB_OK);
			exit(1);
		}


	/*Here we setup the OpenGL stuff...*/

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	glOrtho (0, GetWidth(), 0, GetHeight(), -100.0, 20000.0);
	
	glMatrixMode (GL_MODELVIEW);

	glLoadIdentity(); 
		
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	pFilterBox = new FilterBox();
	if (!pFilterBox->Initialize(256,256))
	{
		MessageBox(NULL,"Cannot initialize filterbox!\n","",MB_OK);
		exit(0);
	}
	pFilterBox->setWindowViewPort(0, 0, Width,Height);

	return 0;
}

void CScreen::SetDimensions(int my_w,int my_h)
{
  Width=my_w;
  Height=my_h;
}
      

