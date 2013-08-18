#ifndef _OBJECT
#define _OBJECT
#include <iostream>
#include <vector>
#include <cmath>

#include <box2d.h>

#include <engine/window toolkit/cscreen.h>
#include <engine/scriptmanager.h>

using namespace std;

class Object;


class CString : public sf::String
{
public:
	CString();
	~CString();
	virtual void Draw(void);
private:
	float _Scale;
protected:
};


#define OP_ADD 1
#define OP_SUB 2
#define OP_MUL 3
#define OP_DIV 4

class Vector
{
public:
	float operator*(Vector b){return x*(b.x)+y*(b.y)+z*(b.z);};
	bool Parallel(Vector b){if (fabs(Normalize()*b.Normalize()-1.f)<1e-3)return true;return false;};
	Vector rotate(float angle){Vector r;r.x=cos(angle)*x-sin(angle)*y;r.y=sin(angle)*x+cos(angle)*y;return r;};
	Vector operator*(float b){Vector r;r.x=x*b;r.y=y*b;r.z=z*b;return r;};
	Vector operator/(float b){Vector r;r.x=x/b;r.y=y/b;r.z=z/b;return r;};
	float Norm(){return sqrt((float)(x*x+y*y+z*z));};
	Vector operator+(Vector b){Vector r;r.x=x+b.x;r.y=y+b.y;r.z=z+b.z;return r;};
	Vector operator-(Vector b){Vector r;r.x=x-b.x;r.y=y-b.y;r.z=z-b.z;return r;};
	Vector operator-(){Vector r;r.x=-x;r.y=-y;r.z=-z;return r;}
	Vector cross(Vector b){Vector r;r.x=y*b.z-z*b.y;r.y=z*b.x-x*b.z;r.z=x*b.y-y*b.x;};
	Vector Normalize(){Vector r=*this;float norm=Norm();r.x/=norm;r.y/=norm;r.z/=norm;return r;};
	Vector operator*=(float a){x*=a;y*=a;z*=a;return *this;}
	Vector operator/=(float a){x/=a;y/=a;z/=a;return *this;}
	Vector(){x=0;y=0;z=0;};
	float x,y,z;

	friend ostream& operator<<(ostream& os,Vector a)
	{
		os << "(" << a.x << "," << a.y << "," << a.z << ")";
		return os;
	}
	friend Vector operator*(float a,Vector b){return b*a;}
};


#define _USE_BOX2D

class Shape
{
public:
	b2ShapeDef *shape;
	void Circle(float radius,float x,float y){if (shape!=NULL)delete shape;b2CircleDef *cd=new b2CircleDef;cd->radius=radius;cd->localPosition.x=x;cd->localPosition.y=y;cd->density=1.0;shape=(b2ShapeDef *)cd;};
	void Polygon(){if (shape!=NULL)delete shape;shape=new b2PolygonDef;shape->density=1.0;shape->friction=1.0;};
	void AddVector(float x,float y){if (shape==NULL)Polygon();b2PolygonDef *pd=(b2PolygonDef *)shape;int i=pd->vertexCount;pd->vertexCount++;pd->vertices[i].Set(x,y);};
	Shape(){shape=NULL;};
	~Shape(){};
};

class Object
{
public:
	vector<Vector> Vertices,RotatedVertices;

	Vector p,v,a;

	float m,MaxRadius,Rotation,VertexRotation;

	b2BodyDef *bodydef;
	b2Body *body;

	vector<b2ShapeDef *> shapes;

	Object();

	void Delete();
	void SetStatic(bool state);

	~Object();

	virtual Object *Duplicate();

	virtual void Evolve(float dt);

	virtual void Collide(Object *obj);

	virtual Vector Position();
	vector<Vector> RotateVertices();

	virtual void SetPosition(float x,float y);
	virtual void Draw();
	virtual void DrawShape();
	void SetName(std::string name);
	float Angle();

	void SetScale(float s);
	virtual void AttachToWorld();
	void AddShape(Shape *s);
	void SetOperator(int op);
	void SetNumber(float n);
	std::string GetText();
	void SetRadius(float r){_Radius=r;};
	float _R,_G,_B;
	float _Scale;
	float _Radius;
	bool IsOperator;
private:
	int Operator;
	float Number;
	bool HasCollisionCallback;
	std::string Name;
	std::string Text;
	std::string CollisionCallback;
	bool IsStatic;
	void Create();
	CString MyString;
protected:
};

#endif