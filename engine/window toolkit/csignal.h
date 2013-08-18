#ifndef _CSIGNAL
#define _CSIGNAL 1

#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>

#define SIGNAL_NONE 0
#define SIGNAL_MOUSEDOWN 1
#define SIGNAL_MOUSEUP 2
#define SIGNAL_KEYDOWN 3

using namespace std;

class CWindow;

class Signal
{
public:
	Signal(){};
	unsigned int type;
	unsigned int ID;
	CWindow *source;
	void *data;
};
#endif