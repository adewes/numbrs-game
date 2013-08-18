#ifndef _CLABEL

#define _CLABEL

#include "cwindow.h"

#define ALIGNMENT_LEFT 0
#define ALIGNMENT_RIGHT 1
#define ALIGNMENT_CENTER 2

class CLabel : public CWindow
{
public:
//	virtual int OnTimer(float interval);
//	virtual int OnMouseDown(float x,float y,int button);
//	virtual void SetCallback(void (*cb)(int ID,void *userdata),void *ud);
//	virtual int OnMouseUp(float x,float y,int button);
//	virtual int OnKeyDown(int key);
//	virtual int OnKeyUp(int key);
	virtual int OnDraw(void);
//	virtual int OnMouseIn(void);
//	virtual int OnMouseOut(void);
//	virtual int OnMouseMove(float x,float y);
	void SetImage(sf::Image *image,float left,float bottom,float right,float top);
	void SetScale(float s){_Scale=s;};
	std::string Text(){return _Text;};
	void SetAlignment(unsigned int Alignment){_Alignment=Alignment;};
	std::string Text(std::string t){_Text=t;return _Text;};
	CLabel(CWindow *parent);
	~CLabel();
private:
	unsigned int _Alignment;
	sf::FloatRect imageRect;
	sf::Image *Image;
	float _Scale;
	std::string _Text;
	float r,g,b;
	int _ID;
protected:
};

#endif