#include "scriptmanager.h"
#include "logger.h"
#include "tolua/tolua.h"

#include <fstream>

namespace LuaScript
{
	int print(lua_State* L)
	{
		Logger *ML=ML->i();
		int n=lua_gettop(L);
		for(int i=0;i<n;i++)
		{
			if (lua_isstring(L,-n+i))
			{
				std::string msg=lua_tostring(L,-n+i);
				ML->PlainScript(msg);
			}
		}
		return 1;
	}
};

void ScriptManager::Setup(void)
{
	Lua = lua_open();
	luaopen_base(Lua);
	luaopen_math(Lua);
	luaopen_os(Lua);
	luaopen_string(Lua);
	luaopen_table(Lua);
//	luaopen_io(Lua);
	luaopen_debug(Lua);
	//We overwrite the print function and redirect the output to a log file.

	lua_pushcfunction(Lua,LuaScript::print);
	lua_setglobal(Lua,"print");
	tolua_open(Lua);
	tolua_tolua_open(Lua);
}

ScriptManager::~ScriptManager()
{
	
}
int ScriptManager::Getint(std::string name)
{
	lua_getglobal(Lua,(const char *)name.data());
	int n=lua_tointeger(Lua,0);
	return n;
}


float ScriptManager::Getfloat(std::string name)
{
	lua_getglobal(Lua,(const char *)name.data());
	lua_Number n=lua_tonumber(Lua,0);
	return (float)n;
}

int ScriptManager::Run(std::string name)
{
	Entry MyEntry=Search(name);
	if (MyEntry.valid)
	{
		luaL_dostring(Lua,MyEntry.data.script.data());
		return 0;
	}
	return -1;
}

int ScriptManager::RegisterFunction(std::string name,lua_CFunction f)
{
	//Isn't that easy ;-)
	Logger *ML=ML->i();
	std::string msg="Registering function ";
	msg.append(name);
	ML->Script(msg);
	lua_register(Lua,(const char *)name.data(),f);
	return 0;
}

int ScriptManager::RegisterFunction(std::string name,std::string package,lua_CFunction f)
{
	Logger *ML=ML->i();
	std::string msg="Registering function ";
	msg.append(package);
	msg.append(".");
	msg.append(name);
	ML->Script(msg);

	lua_getglobal(Lua,(const char *)package.data());
	if (lua_isnil(Lua,-1))
	{
		lua_newtable(Lua);//We create a new table...
		lua_setglobal(Lua,(const char *)package.data());//We set the table name...
	}

	lua_getglobal(Lua,(const char *)package.data());
	lua_pushstring(Lua,(const char *)name.data());//We set the name of the new function

	lua_pushcfunction(Lua , f);//We push the function onto the stack
	lua_settable(Lua,-3);//We set the table value to the function.
	return 0;
}


ScriptEntry ScriptManager::Load(std::string Filename)
{
	ScriptEntry MyEntry;
	ifstream file((const char *)Filename.data());
	std::string buffer;
	char string[1024];
	while(file.getline(string,1024)){MyEntry.script.append(string);MyEntry.script.append("\n");}
	return MyEntry;
}