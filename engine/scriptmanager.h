#ifndef _SCRIPTMANAGER
#define _SCRIPTMANAGER 1

#include "manager.h"
#include "luna.h"

#include <vector>
#include <string>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using namespace std;

typedef struct
{
	string script;
} ScriptEntry;

class ScriptManager : public Manager<ScriptEntry,ScriptManager>
{
public:
 ~ScriptManager();
 void Setup();
 int Run(std::string name);
 float Getfloat(std::string name);
 int Getint(std::string name);
 int RegisterFunction(std::string name,lua_CFunction f);
 int RegisterFunction(std::string name,std::string package,lua_CFunction f);
 ScriptEntry Load(std::string FileHandle);
 lua_State* Lua;
private:
};

#endif
