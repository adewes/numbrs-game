#include "cbutton.h"
#include "clabel.h"
#include "csignal.h"

CButton::CButton(CWindow *parent) : CWindow(parent)
{
	r=1.0;
	g=1.0;
	b=1.0;
	Callback=NULL;
	Image = NULL;
	Label = NULL;
	SetDimensions(32,32);
}

int CButton::OnMouseMove(float x,float y)
{
	return true;
}

void CButton::SetText(std::string text)
{
	if (Label==NULL)
		Label = new CLabel(this);
	Label->Text(text);
}

void CButton::SetImage(sf::Image *image,float left,float bottom,float right,float top)
{
	imageRect.Left=left/(float)image->GetWidth();
	imageRect.Right=right/(float)image->GetWidth();
	imageRect.Top=bottom/(float)image->GetHeight();
	imageRect.Bottom=top/(float)image->GetHeight();
	Image=image;
}

int CButton::OnMouseDown(float x,float y,int button)
{
	if (IsActive()==false)
		return 0;
	if (Parent!=NULL)
		Parent->OnButton(_ID);
	Signal *s=new Signal();
	s->source=this;
	s->data=NULL;
	s->ID=ID();
	s->type=SIGNAL_MOUSEDOWN;
	Emit(s);
	return 1;
}

int CButton::OnMouseUp(float x,float y,int button)
{
	return 1;
}

int CButton::OnMouseIn()
{
	return 1;
}

int CButton::OnMouseOut()
{
	return 1;
}


#define PI 3.1415
int CButton::OnDraw()
{
	if (IsActive())
		glColor3f(r,g,b);
	else
		glColor4f(0.5,0.5,0.5,1.0);
	if (Image!=NULL)
	{
		Image->Bind();
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
		float margin=10;
		if (Label)
		{	
			Label->OnDraw();
			SetDimensions(Label->GetWidth()*1.2,Label->GetHeight()*1.2);
			Label->SetPosition(Label->GetWidth()*0.1,Label->GetHeight()*0.1);
		}
		glBegin(GL_POLYGON);
			for(float i=0;i<PI/2;i+=PI/10)
				glVertex2f(GetWidth()-margin*(1-sin(i)),margin*(1-cos(i)));
			for(float i=0;i<PI/2;i+=PI/10)
				glVertex2f(GetWidth()-margin*(1-cos(i)),GetHeight()-margin*(1-sin(i)));
			for(float i=0;i<PI/2;i+=PI/10)
				glVertex2f(margin*(1-sin(i)),GetHeight()-margin*(1-cos(i)));
			for(float i=0;i<PI/2;i+=PI/10)
				glVertex2f(margin*(1-cos(i)),margin*(1-sin(i)));
		glEnd();
	}
	return 1;
}

CButton::~CButton()
{

}