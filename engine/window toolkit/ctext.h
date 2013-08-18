#ifndef _CTEXT

#define _CTEXT

#include "cwindow.h"

class CText : public sf::String
{
public:
	CText(std::string text) : sf::String() {SetText(text);};
	void DrawPlain(){
		CScreen *MyScreen=MyScreen->i();
		SetFont(MyScreen->ScreenFont);
		glPushMatrix();
		Render(MyScreen->App);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	};
};

#endif