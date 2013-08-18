#include "musicmanager.h"
#include <iostream>

MusicEntry MusicManager::Load(std::string Filename)
{
	MusicEntry MyEntry;
/*	if (!MyEntry.MyMusic.OpenFromFile(Filename))
	{
		cerr << "Can't open music file: " << Filename << "\n";
	}*/
	MyEntry.Filename=Filename;
	return MyEntry;
}

void MusicManager::Setup()
{

}

MusicManager::~MusicManager()
{

}