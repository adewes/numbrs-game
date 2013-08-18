#ifndef _LOGIC

#define _LOGIC

#include "object.h"
#include <engine/singleton.h>
#include <vector>
#include <box2d.h>

using namespace std;


class MyContactListener : public b2ContactListener
{
public:
	void Add(const b2ContactPoint* point)
    {
// are touching heavier bodies.
	    b2Body* body1 = point->shape1->GetBody();
		b2Body* body2 = point->shape2->GetBody();
		float32 mass1 = body1->GetMass();
		float32 mass2 = body2->GetMass();
		Object *obj1=(Object *)body1->GetUserData();
		Object *obj2=(Object *)body2->GetUserData();
/*		obj1->Collide(obj2);
		obj2->Collide(obj1);*/
	}
	void Result(const b2ContactPoint* point)
    {
        // handle persist point
    }
    
	void Remove(const b2ContactPoint* point)
    {
        // handle remove point
    }
    
    void Persist(const b2ContactResult* point)
    {
        // handle results
    }
};


class Rect
{
public:
	float Left,Top,Bottom,Right;
};

class Logic: public Singleton<Logic>
{
public:
    b2AABB worldAABB;
    MyContactListener CL;
    b2World *world;
	void Setup();
	void DeleteObject(Object *obj);
	Object *GetObjectAt(float x,float y);
	void SetGravity(float gx,float gy);
    void Evolve(float dt);
	bool CheckEquation();
	int nObjects(){return Objects.size();};
	void Toggle(Object *obj,bool left);
	void AddObject(Object *obj);
	vector<Object *> Objects;
	vector<Object *> LeftSide,RightSide;
	Rect Box;
	float Points,PointsToAdd;
private:
};

#endif