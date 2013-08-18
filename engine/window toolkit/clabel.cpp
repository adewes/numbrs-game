#include "clabel.h"

CLabel::CLabel(CWindow *parent) : CWindow(parent)
{
	_Scale=1;
	SetDimensions(300,20);
	Image=NULL;
}

CLabel::~CLabel()
{

}


void CLabel::SetImage(sf::Image *image,float left,float bottom,float right,float top)
{
	imageRect.Left=left/(float)image->GetWidth();
	imageRect.Right=right/(float)image->GetWidth();
	imageRect.Top=bottom/(float)image->GetHeight();
	imageRect.Bottom=top/(float)image->GetHeight();
	Image=image;
}

int CLabel::OnDraw()
{
	if (Image!=NULL)
	{
		Image->Bind();
		glColor3f(1,1,1);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_QUADS);
			glTexCoord2f(imageRect.Left,imageRect.Bottom);
			glVertex2f(0,0);

			glTexCoord2f(imageRect.Right,imageRect.Bottom);
			glVertex2f(GetWidth(),0);

			glTexCoord2f(imageRect.Right,imageRect.Top);
			glVertex2f(GetWidth(),GetHeight());

			glTexCoord2f(imageRect.Left,imageRect.Top);
			glVertex2f(0,GetHeight());


		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		sf::String Text(_Text,Screen->ScreenFont,20);
		sf::FloatRect rect = Text.GetRect();
		SetDimensions(fabs(rect.Right-rect.Left),fabs(rect.Top-rect.Bottom));
		float OffsetX=0;
		if (_Alignment==ALIGNMENT_RIGHT)
		{
			OffsetX=-(rect.Right-rect.Left);
		}
		Text.SetPosition(AbsoluteX()+OffsetX,Screen->GetHeight()-AbsoluteY()-Text.GetFont().GetCharacterSize());
		Text.SetColor(sf::Color(255, 255, 255));

		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		Text.SetScale(_Scale,_Scale);
		Screen->App.Draw(Text);
	}
	return true;
}