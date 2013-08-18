#include "soundmanager.h"
#include <iostream>

SoundEntry SoundManager::Load(std::string Filename)
{
	SoundEntry MyEntry;
	MyEntry.MySound=new sf::SoundBuffer;
	if (!MyEntry.MySound->LoadFromFile(Filename))
	{
		cerr << "Can't open sound file: " << Filename << "\n";
	}
	MyEntry.Filename=Filename;
	return MyEntry;
}

sf::Sound *SoundManager::GetSound(std::string name)
{
	SoundEntry MyEntry=Get(name);
	sf::Sound *SH=NULL;
	for(unsigned int i=0;i<Sounds.size();i++)
	{
		if (Sounds[i]->GetStatus()==sf::Sound::Status::Stopped || Sounds[i]->GetStatus()==sf::Sound::Status::Paused)
		{
			SH=Sounds[i];
			break;
		}
	}
	if (SH==NULL)
	{
		cout << "Creating new sound slot...\n";
		SH=new sf::Sound();
		Sounds.push_back(SH);
	}
	cout << "Sound slots:" << Sounds.size() << "\n";
	SH->SetBuffer(*(MyEntry.MySound));
	return SH;
}

void SoundManager::Setup()
{

}

SoundManager::~SoundManager()
{

}