#include "game.h"
#include "logic.h"

#include <sstream>

Game::Game(CWindow *parent,float w,float h) : CWindow(parent)
{
	Logic *ML=ML->i();
	SetDimensions(w,h);
	ML->Box.Left=w/5-20;
	ML->Box.Right=w*4/5-20;
	ML->Box.Bottom=h/10;
	ML->Box.Top=h;
	TimeElapsed=0;
	Equation=new CLabel(this);
	Equation->SetPosition(w/5*2+30,0);
	Equation->SetDimensions(300,40);
	Equation->SetScale(2.0);
	Equation->Show();
	AddChildWindow(Equation);
	Equation->Text("Test");
	Points=new CLabel(this);
	Points->SetPosition(20,0);
	AddChildWindow(Points);
	Points->Text("Test");
	Points->SetScale(2.0);
}

int Game::OnEvent(sf::Event Event)
{
	float mx,my;
	Logic *ML=ML->i();
	CScreen *Screen=Screen->i();
	switch(Event.Type)
	{
	case sf::Event::MouseButtonPressed:
		if (Event.MouseButton.Button==sf::Mouse::Button::Left || Event.MouseButton.Button==sf::Mouse::Button::Right)
		{
			TimeElapsed=0.0;
			mx=Screen->GetMouseX();
			my=Screen->GetMouseY();
			cout << "Mouse pressed at " << mx << ", " << my << "\n";
			Object *obj=ML->GetObjectAt(mx-ML->Box.Left,my);
			if (obj!=NULL)
			{
				ML->Toggle(obj,Event.MouseButton.Button==sf::Mouse::Button::Left?true:false);
			}
		}
		break;
	};
	return 0;
}


void Game::Setup()
{
	Logic *MyLogic=MyLogic->i();
	float w=MyLogic->Box.Right-MyLogic->Box.Left;
	Vector p;
	Object *floor=new Object;
	Shape *floorshape=new Shape;
	floorshape->AddVector(p.x,p.y);
	p.y=400.0;
	floorshape->AddVector(p.x,p.y);
	p.x=0.0;
	p.y=50.0;
	floorshape->AddVector(p.x,p.y);
	p.x=800.0;
	p.y=400.0;
	floorshape->AddVector(p.x,p.y);
	p.y=-50.0;
	floorshape->AddVector(p.x,p.y);
	floor->AddShape(floorshape);
	floor->SetPosition(500,0);

	Object *Box=new Object();
	Shape *BoxShape=new Shape();

	Box->SetName("box");
	Box->SetPosition(Width/2.0,20);
	p.x=-w/2;
	p.y=-10;
	BoxShape->AddVector(p.x,p.y);
	p.x=w/2;
	BoxShape->AddVector(p.x,p.y);
	p.y=10;
	BoxShape->AddVector(p.x,p.y);
	p.x=-w/2;
	BoxShape->AddVector(p.x,p.y);
	Box->AddShape(BoxShape);
	Box->SetStatic(true);
	MyLogic->AddObject(Box);

	Box=new Object();
	BoxShape=new Shape();
	Box->SetPosition(Width/2-w/2,Height/2.f);
	p.x=-10;
	p.y=-Height/2.f;
	BoxShape->AddVector(p.x,p.y);
	p.x=10;
	BoxShape->AddVector(p.x,p.y);
	p.y=Height/2.f;
	BoxShape->AddVector(p.x,p.y);
	p.x=-10;
	BoxShape->AddVector(p.x,p.y);
	Box->AddShape(BoxShape);
	Box->SetStatic(true);
	MyLogic->AddObject(Box);

	Box=new Object();
	BoxShape=new Shape();
	Box->SetPosition(Width/2+w/2,Height/2.f);
	p.x=-10;
	p.y=-Height/2.f;
	BoxShape->AddVector(p.x,p.y);
	p.x=10;
	BoxShape->AddVector(p.x,p.y);
	p.y=Height/2.f;
	BoxShape->AddVector(p.x,p.y);
	p.x=-10;
	BoxShape->AddVector(p.x,p.y);
	Box->AddShape(BoxShape);
	Box->SetStatic(true);
	MyLogic->AddObject(Box);

}

int Game::OnTimer(float interval)
{
	Logic *ML=ML->i();
	TimeElapsed+=interval/1000;
	if (TimeElapsed>2)
	{	
		ML->LeftSide.clear();
		ML->RightSide.clear();
	}
	ML->Evolve(0.01);
	std::string text;
	for(int i=0;i<ML->LeftSide.size();i++)
		text.append(ML->LeftSide[i]->GetText());
	text.append(" = ");
	for(int i=0;i<ML->RightSide.size();i++)
		text.append(ML->RightSide[i]->GetText());
	Equation->Text(text);
	return 1;
}

int Game::OnDraw()
{
	int i;
	Logic *ML=ML->i();
	CScreen *Screen=Screen->i();
	glColor3f(1,1,1);
	vector<Object *> MyObjects=ML->Objects;
	glPushMatrix();
	glTranslatef(ML->Box.Left,0,0);
	for(i=0;i<MyObjects.size();i++)
	{
		Object *obj=MyObjects[i];
		glPushMatrix();
			Vector pos=obj->Position();
			glTranslatef(pos.x,pos.y,0);
			glRotatef(obj->Angle()*180.0/3.1415,0,0,1);
			glColor3f(obj->_R,obj->_G,obj->_B);
			obj->Draw();
		glPopMatrix();
	}
	Screen->ActivateGlow();
	for(i=0;i<ML->LeftSide.size();i++)
	{
		Object *obj=ML->LeftSide[i];
		glPushMatrix();
			Vector pos=obj->Position();
			glTranslatef(pos.x,pos.y,0);
			glRotatef(obj->Angle()*180.0/3.1415,0,0,1);
			glColor3f(1,0,0);
			obj->DrawShape();
		glPopMatrix();
	}
	for(i=0;i<ML->RightSide.size();i++)
	{
		Object *obj=ML->RightSide[i];
		glPushMatrix();
			Vector pos=obj->Position();
			glTranslatef(pos.x,pos.y,0);
			glRotatef(obj->Angle()*180.0/3.1415,0,0,1);
			glColor3f(0,0,1);
			obj->DrawShape();
		glPopMatrix();
	}
	Screen->DeactivateGlow();

	if (ML->LeftSide.size()>1)
	{
		glColor4f(1,0,0,0.5);
		glLineWidth(5.0);
		glBegin(GL_LINE_STRIP);
		Object *obj=ML->LeftSide[0];
		Vector pos=obj->Position();
		glVertex2f(pos.x,pos.y);
		for(i=1;i<ML->LeftSide.size();i++)
		{
			Object *obj2=ML->LeftSide[i];
			Vector pos2=obj2->Position();
			glVertex2f(pos2.x,pos2.y);
		}
		glEnd();
	}

	if (ML->RightSide.size()>1)
	{
		glColor4f(0,0,1,0.5);
		glLineWidth(5.0);
		glBegin(GL_LINE_STRIP);
		Object *obj=ML->RightSide[0];
		Vector pos=obj->Position();
		glVertex2f(pos.x,pos.y);
		for(i=1;i<ML->RightSide.size();i++)
		{
			Object *obj2=ML->RightSide[i];
			Vector pos2=obj2->Position();
			glVertex2f(pos2.x,pos2.y);
		}
		glEnd();
	}

	glPopMatrix();
	stringstream stream;
	stream << (int)ML->Points;
	Points->Text(stream.str());
	return 1;
}