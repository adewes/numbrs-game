#ifndef _MUSICMANAGER
#define _MUSICMANAGER 1

#include "manager.h"

#include <vector>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

typedef struct
{
	std::string Filename;
//	sf::Music MyMusic;
} MusicEntry;

class MusicManager : public Manager<MusicEntry,MusicManager>
{
public:
 ~MusicManager();
 void Setup();
 MusicEntry Load(std::string FileHandle);
private:
};

#endif
