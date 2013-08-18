#include "texturemanager.h"
#include "scriptmanager.h"

#include <fstream>

namespace LuaTexture
{
	void Setup(void)
	{
		ScriptManager *SM=SM->i();

/*		SM->RegisterFunction("Require","Sound",Require);
		SM->RegisterFunction("Play","Sound",Play);*/

	}
}

void TextureManager::Setup()
{
	LuaTexture::Setup();
}

TextureEntry TextureManager::Load(std::string Filename)
{
	TextureEntry MyEntry;
	MyEntry.filename=Filename;
	MyEntry.GL_texture=0; 

	glGenTextures( 1, &MyEntry.GL_texture );
	glBindTexture( GL_TEXTURE_2D, MyEntry.GL_texture );

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	SDL_Surface *TextureImage;
	TextureImage=IMG_Load((const char *)Filename.data());

	if (TextureImage==NULL)
		return MyEntry;

	glTexImage2D( GL_TEXTURE_2D,0, 4, TextureImage->w, TextureImage->h,0,
                   GL_RGB, GL_UNSIGNED_BYTE, (void *)TextureImage->pixels );
	SDL_FreeSurface(TextureImage);
	return MyEntry;
}
