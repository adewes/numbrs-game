#ifndef _TEXTUREMANAGER
#define _TEXTUREMANAGER 1

#include "manager.h"

#include <vector>
#include <string>
#ifndef _MSC_VER
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#else
#include <windows.h>
#include <sdl.h>
#endif
#include <SDL_image.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>



using namespace std;



typedef struct
{
	unsigned int GL_texture;
	string filename;
} TextureEntry;

class TextureManager : public Manager<TextureEntry,TextureManager>
{
public:
	void Setup();
	TextureEntry Load(std::string FileHandle);
private:
};

#endif
