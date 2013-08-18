#ifndef _SOUNDMANAGER
#define _SOUNDMANAGER 1

#include "manager.h"

#include <vector>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

typedef struct
{
	sf::SoundBuffer *MySound;
	std::string Filename;
} SoundEntry;

class SoundManager : public Manager<SoundEntry,SoundManager>
{
public:
 ~SoundManager();
 void Setup();
 sf::Sound *GetSound(std::string name);
 SoundEntry Load(std::string FileHandle);
private:
	vector<sf::Sound *> Sounds;
};

#endif
