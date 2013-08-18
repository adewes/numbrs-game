#include "logic.h"
#include <iostream>
#include "tolua/objects.h"
#include <engine/scriptmanager.h>

void Logic::AddObject(Object *obj)
{
	cout << "Adding new object...\n";
	obj->AttachToWorld();
	Objects.push_back(obj);
}

void Logic::SetGravity(float gx,float gy)
{
	b2Vec2 g;
	g.x=gx;
	g.y=gy;
	world->SetGravity(g);	
}

void Logic::Setup()
{
	ScriptManager *SM=SM->i();
	SM->Setup();

	Points=0.f;
	PointsToAdd=0.f;

	tolua_open(SM->Lua);
	tolua_objects_open(SM->Lua);

	worldAABB.lowerBound.Set(0.f,0.f);
	worldAABB.upperBound.Set(1024.f, 1000.f);
	b2Vec2 gravity(0.0f, 0.0f);
	bool doSleep = false;
	world=new b2World(worldAABB,gravity,doSleep);
	world->SetContactListener(&CL);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(500.0f, 0.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonDef groundShapeDef;
	groundShapeDef.SetAsBox(1000.f, 10.0f);
	groundBody->CreateShape(&groundShapeDef);


	SM->Require("startup","data/scripts/startup.lua");
	SM->Require("evolve","data/scripts/evolve.lua");
	SM->Run("startup");
}

bool Logic::CheckEquation()
{
	int i;
	int operators=0;
	int numbers=0;
	std::string str="rv=(";
	std::string left,right;
	for(int i=0;i<LeftSide.size();i++)
	{
		if (LeftSide[i]->IsOperator)
			operators++;
		else
			numbers++;
		left.append(LeftSide[i]->GetText());
		str.append(LeftSide[i]->GetText());
	}
	str.append(" )-( ");
	for(int i=0;i<RightSide.size();i++)
	{
		if (RightSide[i]->IsOperator)
			operators++;
		else
			numbers++;
		str.append(RightSide[i]->GetText());
		right.append(RightSide[i]->GetText());
	}
	ScriptManager *SM=SM->i();
	str.append(");");
	bool hasError=false;
	if (luaL_dostring(SM->Lua,(const char *)str.data())!=0)
		hasError=true;
	lua_getglobal(SM->Lua,"rv");
	float result=lua_tonumber(SM->Lua,-1);
	if (result==0 && !hasError)
	{
		for(i=0;i<LeftSide.size();i++)
			DeleteObject(LeftSide[i]);
		for(i=0;i<RightSide.size();i++)
			DeleteObject(RightSide[i]);
		if (left.compare(right))
		{
			std::string leval="res="+left+";";
			luaL_dostring(SM->Lua,(const char *)leval.data());
			lua_getglobal(SM->Lua,"res");
			float value=lua_tonumber(SM->Lua,-1);
			PointsToAdd+=10.0*value*pow(2.f,(float)operators);
			}
		LeftSide.clear();
		RightSide.clear();
	}
}

void Logic::DeleteObject(Object *obj)
{
	for(int i=0;i<Objects.size();i++)
	{
		if (Objects[i]==obj)
		{
			if (obj->body!=NULL)
				world->DestroyBody(obj->body);
			Objects.erase(Objects.begin()+i);
			return;
		}
	}
}

void Logic::Toggle(Object *obj,bool left)
{
	int i;
	bool found=false;
	if (left)
	{
		for(i=0;i<RightSide.size();i++)
		{
			if (RightSide[i]==obj)
				return;
		}
		for(i=0;i<LeftSide.size();i++)
			if (LeftSide[i]==obj)
			{
				LeftSide.erase(LeftSide.begin()+i);
				return;
			}
		LeftSide.push_back(obj);
	}
	else
	{
		for(i=0;i<LeftSide.size();i++)
		{
			if (LeftSide[i]==obj)
				return;
		}
		for(i=0;i<RightSide.size();i++)
			if (RightSide[i]==obj)
			{
				RightSide.erase(RightSide.begin()+i);
				return;
			}
		RightSide.push_back(obj);
	}
}


Object *Logic::GetObjectAt(float x,float y)
{
	Object *obj=NULL;
	float r_min=0;
	for(int i=0;i<Objects.size();i++)
	{
		Vector p=Objects[i]->Position();
		float r=Objects[i]->_Radius;
		float d=sqrt(pow(x-p.x,2.f)+pow(y-p.y,2.f));
		if (d<=r && (d<r_min || obj==NULL))
		{
			r_min=d;
			obj=Objects[i];
		}
	}
	return obj;
}

void Logic::Evolve(float dt)
{
	int i;
	ScriptManager *SM=SM->i();
	for(i=0;i<4;i++)
		world->Step(1.f/20.f,1);
	SM->Run("evolve");
	CheckEquation();
	if (PointsToAdd>0)
	{
		Points+=PointsToAdd*0.1;
		PointsToAdd*=0.9;
		if (PointsToAdd<1)
		{
			Points+=PointsToAdd;
			PointsToAdd=0.0;
		}
	}
}