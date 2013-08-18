#ifndef _IMAGEMANAGER
#define _IMAGEMANAGER 1

#include "manager.h"

#include <vector>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

typedef struct
{
	std::string Filename;
	sf::Image *Image;
} ImageEntry;

class ImageManager : public Manager<ImageEntry,ImageManager>
{
public:
 ~ImageManager(){};
 void Setup(){};
 ImageEntry Load(std::string Filename)
 {
	ImageEntry MyEntry;
	MyEntry.Filename=Filename;
	MyEntry.Image = new sf::Image;
	if(!MyEntry.Image->LoadFromFile(Filename))
	{
		//Failed to load the image...
	}
	return MyEntry;

 }
private:
};

#endif
