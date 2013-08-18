/*
** Lua binding: tolua
** Generated automatically by tolua++-1.0.92 on 05/01/09 18:58:05.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_tolua_open (lua_State* tolua_S);

#include "window toolkit/cscreen.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_sf__Image (lua_State* tolua_S)
{
 sf::Image* self = (sf::Image*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"sf::Image");
}

/* method: new of class  sf::Image */
#ifndef TOLUA_DISABLE_tolua_tolua_sf_Image_new00
static int tolua_tolua_sf_Image_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"sf::Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   sf::Image* tolua_ret = (sf::Image*)  Mtolua_new((sf::Image)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"sf::Image");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  sf::Image */
#ifndef TOLUA_DISABLE_tolua_tolua_sf_Image_new00_local
static int tolua_tolua_sf_Image_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"sf::Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   sf::Image* tolua_ret = (sf::Image*)  Mtolua_new((sf::Image)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"sf::Image");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSmooth of class  sf::Image */
#ifndef TOLUA_DISABLE_tolua_tolua_sf_Image_SetSmooth00
static int tolua_tolua_sf_Image_SetSmooth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"sf::Image",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  sf::Image* self = (sf::Image*)  tolua_tousertype(tolua_S,1,0);
  bool smooth = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSmooth'", NULL);
#endif
  {
   self->SetSmooth(smooth);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSmooth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadFromFile of class  sf::Image */
#ifndef TOLUA_DISABLE_tolua_tolua_sf_Image_LoadFromFile00
static int tolua_tolua_sf_Image_LoadFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"sf::Image",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  sf::Image* self = (sf::Image*)  tolua_tousertype(tolua_S,1,0);
  const std::string Filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFromFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadFromFile(Filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)Filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_tolua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"sf",0);
  tolua_beginmodule(tolua_S,"sf");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Image","sf::Image","",tolua_collect_sf__Image);
   #else
   tolua_cclass(tolua_S,"Image","sf::Image","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Image");
    tolua_function(tolua_S,"new",tolua_tolua_sf_Image_new00);
    tolua_function(tolua_S,"new_local",tolua_tolua_sf_Image_new00_local);
    tolua_function(tolua_S,".call",tolua_tolua_sf_Image_new00_local);
    tolua_function(tolua_S,"SetSmooth",tolua_tolua_sf_Image_SetSmooth00);
    tolua_function(tolua_S,"LoadFromFile",tolua_tolua_sf_Image_LoadFromFile00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_tolua (lua_State* tolua_S) {
 return tolua_tolua_open(tolua_S);
};
#endif

