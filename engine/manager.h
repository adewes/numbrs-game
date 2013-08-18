#ifndef _MANAGER
#define _MANAGER 1


#include "singleton.h"

#include <vector>
#include <string>
#include <windows.h>

using namespace std;

template <typename C,typename T>

class Manager : public Singleton<T>
{
public:
	struct Entry
	{
		int valid;
		std::string name;
		C data;
	};

	void Setup(void);
  Entry Search(string Name)
	{
	unsigned int i;
	for(i=0;i<Entries.size();i++)
	{
		Entry MyEntry=Entries.at(i);
		if (MyEntry.name==Name)
			return MyEntry;
	}
	Entry ret;
	ret.valid=0;
	return ret;
	};
  C Get(string Name)
  {
	Entry MyEntry=Search(Name);
	return MyEntry.data;
  }
  C Require(string Name,string FileHandle)
  {
		Entry MyEntry=Search(Name);
		if (!MyEntry.valid)
		{		
			MyEntry.data=Load(FileHandle);
			MyEntry.name=Name;
			MyEntry.valid=1;
			Entries.push_back(MyEntry);
		}
		return MyEntry.data;
  };
  void Add(string Name,C Entity)
  {
	  Entry MyEntry;
	  MyEntry.name=Name;
	  MyEntry.data=Entity;
	  Entries.push_back(MyEntry);
	  cout << "Added new entry \"" << Name << "\"\n";
  };
  virtual C Load(std::string Filename) {C ret;return ret;};
private:
	vector<Entry> Entries;
};


#endif
