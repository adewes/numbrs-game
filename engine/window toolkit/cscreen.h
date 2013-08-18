#ifndef _CSCREEN

#define _CSCREEN

#include <math.h>
#include <iostream>

#include <GL/glew.h>


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/String.hpp>
 

#include <time.h>


#include <GL/glu.h>

#include <CG/cg.h>
#include "../opengl/filterbox.h"

class CScreen;
class CWindow; 
class CEvent;

#include "cwindow.h"
#include "csignal.h"
#include "../singleton.h"


class CScreen : public Singleton <CScreen>
{
  public:
  GLdouble ObjX,ObjY,ObjZ;
  void SetDimensions(int my_w,int my_h);
  double T;
  double spaceship;
  void DeactivateGlow();
  void ActivateGlow();
  void Screenshot();
  int GetWidth();
  int GetHeight();
  int Setup();
  int Flip();
  void Crossfade(CWindow *window);

  int Loop();
  void DrawWindowAndChilds(CWindow *window);

  void Invalidate(CWindow *window);

  void SetWindow(CWindow *window);
  void MovePosition(float x,float y);
  float GetMouseX();
  float GetMouseY();
  void RevertPosition(void);
  void UpdateObjectPosition(void);
  void Clear();
  void Emit(Signal *s);
  void SetFocus(CWindow *wnd);
  
  float Glow();
  float Glow(float g);

  int HandleMouseDown(CWindow *window,float x,float y,int button);
  int HandleMouseUp(CWindow *window,float x,float y,int button);
  int HandleMouseMove(CWindow *window,float x,float y);
  int HandleKeyDown(CWindow *window,sf::Event::KeyEvent key);
  int HandleKeyUp(CWindow *window,sf::Event::KeyEvent key);

  void UpdateMousePosition(float x,float y);
  int HandleWindowEvent(CWindow *window,sf::Event Event);
  int HandleEvent(sf::Event Event);

  int OnTimer(void);

  void ProcessSignals();

  CWindow *MouseDown,*KeyDown;
  CWindow *BackgroundWindow;
  CWindow *ActiveWindow;

  vector<Signal *> Signals;
  sf::RenderWindow App;
  sf::Clock Clock;
  sf::Font ScreenFont;
  sf::Image FontTexture;

private:
  float _Glow;
  float fr;
  CWindow *Focus;
  GLuint texture,fb,texture2,fb2;
  GLuint v,f,p;
  FilterBox*	pFilterBox;
  int Width,Height;
  float MouseX,MouseY;
  protected:
};


#endif