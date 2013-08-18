#include "object.h"
#include "logic.h"
#include <engine/window toolkit/cscreen.h>
#include "object.h"
#include <engine/logger.h>
#include <engine/window toolkit/cscreen.h>
#include <cmath>
#include <sstream>
#include "logic.h"

void Object::SetOperator(int op)
{
	IsOperator=true;
	Operator=op;
	switch(Operator)
	{
	case OP_ADD:
		MyString.SetText("+");
		_R=0.7;
		_G=1.0;
		_B=0.7;
		break;
	case OP_SUB:
		MyString.SetText("-");
		_R=0.7;
		_G=0.7;
		_B=1.0;
		break;
	case OP_MUL:
		_R=1.0;
		_G=0.7;
		_B=0.7;
		MyString.SetText("*");
		break;
	case OP_DIV:
		_R=1.0;
		_G=1.0;
		_B=1.0;
		MyString.SetText("/");
		break;
	};
	Text=MyString.GetText();
}

void Object::SetNumber(float n)
{
	IsOperator=false;
	Number=n;
	stringstream stream;
	stream << (int)Number;
	Text=stream.str();
	if ((int)Number==9 || (int)Number==6)
		stream << ".";
	MyString.SetText(stream.str());
		switch((int)Number)
		{
		case 0:
			_R=1.0;_G=0.0;_B=0.0;
			break;
		case 1:
			_R=0.0;_G=1.0;_B=0.0;
			break;
		case 2:
			_R=0.0;_G=0.0;_B=1.0;
			break;
		case 3:
			_R=1.0;_G=1.0;_B=0.0;
			break;
		case 4:
			_R=1.0;_G=0.0;_B=1.0;
			break;
		case 5:
			_R=.0;_G=1.0;_B=1.0;
			break;
		case 6:
			_R=1.0;_G=0.5;_B=0.0;
			break;
		case 7:
			_R=1.0;_G=0.0;_B=0.5;
			break;
		case 8:
			_R=1.0;_G=0.5;_B=0.5;
			break;
		case 9:
			_R=0.5;_G=0.1;_B=0.5;
			break;
		};
}

void CString::Draw()
{
	CScreen *Screen=Screen->i();
	int length=0;
	float height=0;
	glPushMatrix();
	std::string str=(std::string)(GetText());
	for(int i=0;i<str.size();i++)
	{
		sf::Glyph MyGlyph=GetFont().GetGlyph(str[i]);
		length+=MyGlyph.Advance;
		height+=MyGlyph.Rectangle.GetHeight();
	}
	height/=(float)str.size();
	sf::Vector2f s=GetScale();
	glScalef(s.x,s.y,1);
	glTranslatef(-length/2,-height,0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	Render(Screen->App);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
}

CString::CString()
{
	CScreen *Screen=Screen->i();
	SetFont(Screen->ScreenFont);
}

CString::~CString()
{

}


float Object::Angle()
{
#ifdef _USE_BOX2D
	if (body==NULL)
		return 0.f;
	return body->GetAngle();
#else
	return Rotation;
#endif
}

vector<Vector> Object::RotateVertices()
{
	if (VertexRotation==Angle() && RotatedVertices.size()==Vertices.size())
		return RotatedVertices;
	RotatedVertices.clear();
	for(unsigned int i=0;i<Vertices.size();i++)
	{
		RotatedVertices.push_back(Vertices[i].rotate(Angle()));
	}
	VertexRotation=Angle();
	return RotatedVertices;
}


void Object::Evolve(float dt)
{

}

void Object::Create()
{
	_Radius=-1.0;
	_Scale=1.0;
	HasCollisionCallback=false;
	v.x=400.f;
	v.y=400.f;
	IsStatic=false;
	MaxRadius=0.0;
	m=1.0;
	body=NULL;
	_R=(float)(rand()%1000)/1000.f;
	_G=(float)(rand()%1000)/1000.f;
	_B=(float)(rand()%1000)/1000.f;
	bodydef=new b2BodyDef;
	bodydef->linearDamping=0.4;
	bodydef->angularDamping=0.1;
}

void Object::AddShape(Shape *s)
{
	shapes.push_back(s->shape);
}


Object::Object()
{
	Create();
}

void Object::SetStatic(bool state)
{
	IsStatic=true;
	if (state)	
	{
		for(int i=0;i<shapes.size();i++)
			shapes[i]->density=0.0;
	}
	else
	{
		for(int i=0;i<shapes.size();i++)
			shapes[i]->density=1.0;
	}
}

void Object::Delete()
{
	if (body!=NULL)
	{
		Logic *L=L->i();
		L->world->DestroyBody(body);
		delete bodydef;
	}
	
}

Object::~Object()
{
	if (body!=NULL)
	{
		Logic *L=L->i();
		L->world->DestroyBody(body);
		delete bodydef;
	}
}

std::string Object::GetText()
{
	return Text;
}

void Object::AttachToWorld()
{
	Logger *LL=LL->i();
	Logic *L=L->i();
	body=L->world->CreateBody(bodydef);
	body->SetUserData((void *)this);
	for(int i=0;i<shapes.size();i++)
		body->CreateShape(shapes[i]);
	body->SetMassFromShapes();
}

void Object::SetName(std::string name)
{
	Name=name;
}

void Object::Collide(Object *obj)
{
}

Object *Object::Duplicate()
{
	return NULL;	
}

#define PI 3.1415

void Object::DrawShape()
{
	int i,j;
	glBegin(GL_POINTS);
		glVertex2f(0,0);
	glEnd();
	glLineWidth(4.0f);
	for(i=0;i<shapes.size();i++)
	{
		if (shapes[i]->type==e_polygonShape)
		{
			glBegin(GL_POLYGON);
			for(j=0;j<((b2PolygonDef *)(shapes[i]))->vertexCount;j++)
				glVertex2f(((b2PolygonDef *)shapes[i])->vertices[j].x,((b2PolygonDef *)shapes[i])->vertices[j].y);
			glEnd();
		}
		else
		{
			glPushMatrix();
			b2CircleDef *cd=(b2CircleDef *)shapes[i]; 
			glTranslatef(cd->localPosition.x,cd->localPosition.y,0);
			float angle;
			glBegin(GL_POLYGON);
			for(angle=0;angle<=2.0*PI;angle+=PI/20)
				glVertex2f(cos(angle)*cd->radius,sin(angle)*cd->radius);
			glEnd();
			glPopMatrix();
		}
	}
}

void Object::SetScale(float s)
{
	_Scale=s;
}

void Object::Draw()
{
	glColor4f(_R,_G,_B,1.0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	DrawShape();


	glColor4f(_R*0.6,_G*0.6,_B*0.6,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	DrawShape();

	MyString.SetScale(_Scale,_Scale);
	glPushMatrix();
//	glRotatef(180.0-Angle()*180.0/PI,0,0,1);
	glScalef(-1,1,1);
	glColor3f(1-_R,1-_G,1-_B);
	MyString.Draw();
	glPopMatrix();

}


Vector Object::Position()
{
	Vector vp;
#ifdef _USE_BOX2D
	b2Vec2 v;
	if (body!=NULL)
	{
		v=body->GetPosition();
		vp.x=v.x;
		vp.y=v.y;
	}
	return vp;
#else
	return p;
#endif
}
void Object::SetPosition(float x,float y)
{
	p.x=x;
	p.y=y;
#ifdef _USE_BOX2D
	if (body!=NULL)
	{
		b2Vec2 v;
		v.x=x;
		v.y=y;
		float angle=Angle();
		body->SetXForm(v,angle);
	}
	else
		bodydef->position.Set(x,y);
#endif
}
