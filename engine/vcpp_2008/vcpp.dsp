# Microsoft Developer Studio Project File - Name="vcpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=vcpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vcpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vcpp.mak" CFG="vcpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vcpp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vcpp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vcpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "FLUX_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 SDL.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "vcpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "FLUX_WINDOWS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SDL.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "vcpp - Win32 Release"
# Name "vcpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Objects"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\Objects\asteroid.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\blackhole.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\bomb.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\bullet.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\Invader.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\Minimap.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\shield.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\spaceship.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\star.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\template.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\tower.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\app.cpp
# End Source File
# Begin Source File

SOURCE=..\game.cpp
# End Source File
# Begin Source File

SOURCE=..\utils\glfont.cpp
# End Source File
# Begin Source File

SOURCE=..\graphics.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\grid.cpp
# End Source File
# Begin Source File

SOURCE=..\input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\sine_g_new\interpret_class.cpp
# End Source File
# Begin Source File

SOURCE=..\object.cpp
# End Source File
# Begin Source File

SOURCE=..\sound.cpp
# End Source File
# Begin Source File

SOURCE=..\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=..\Objects\text.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Objects headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\Objects\asteroid.h
# End Source File
# Begin Source File

SOURCE=..\Objects\blackhole.h
# End Source File
# Begin Source File

SOURCE=..\Objects\bomb.h
# End Source File
# Begin Source File

SOURCE=..\Objects\bullet.h
# End Source File
# Begin Source File

SOURCE=..\Objects\Invader.h
# End Source File
# Begin Source File

SOURCE=..\Objects\Minimap.h
# End Source File
# Begin Source File

SOURCE=..\Objects\shield.h
# End Source File
# Begin Source File

SOURCE=..\Objects\spaceship.h
# End Source File
# Begin Source File

SOURCE=..\Objects\star.h
# End Source File
# Begin Source File

SOURCE=..\Objects\tower.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\game.h
# End Source File
# Begin Source File

SOURCE=..\utils\glfont.h
# End Source File
# Begin Source File

SOURCE=..\graphics.h
# End Source File
# Begin Source File

SOURCE=..\Objects\grid.h
# End Source File
# Begin Source File

SOURCE=..\input.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\sine_g_new\interpret_class.h
# End Source File
# Begin Source File

SOURCE=..\object.h
# End Source File
# Begin Source File

SOURCE=..\sound.h
# End Source File
# Begin Source File

SOURCE=..\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Objects\template.h
# End Source File
# Begin Source File

SOURCE=..\Objects\text.h
# End Source File
# Begin Source File

SOURCE=..\types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
