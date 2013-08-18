// impressionism.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "game.h"
#include <engine/window toolkit/cscreen.h>
#include <engine/logger.h>


#define WIN32_LEAN_AND_MEAN             // Selten verwendete Teile der Windows-Header nicht einbinden.
// Windows-Headerdateien:
#include <windows.h>

// C RunTime-Headerdateien
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "logic.h"

#define MAX_LOADSTRING 100

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstanc,LPTSTR    lpCmdLine,int       nCmdShow)
{
	Logger *LL=LL->i();
	LL->Setup();

	srand(time(NULL));

	CScreen *MyScreen=MyScreen->i();
	MyScreen->SetDimensions(1024,768);
	MyScreen->Setup();
	
	Logic *MyLogic=MyLogic->i();
	MyLogic->Setup();

	Game *MyGame=new Game(NULL,1024,768);
	MyGame->Setup();


	MyScreen->SetWindow(MyGame);
	MyScreen->Loop();

	return 0;
}