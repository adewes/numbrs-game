#ifndef _CINPUT
#define _CINPUT 1

#include "singleton.h"

class Input : public Singleton <Input>
{
public:
  int Mouse[5];
  int Keys[512];
  float Zoom,MouseX,MouseY;
  void Setup(void);

private:
};

#endif
