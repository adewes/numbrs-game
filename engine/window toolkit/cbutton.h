#ifndef _CBUTTON

#define _CBUTTON

#include "cwindow.h"

class CLabel;

class CButton : public CWindow
{
public:
//	virtual int OnTimer(float interval);
	virtual int OnMouseDown(float x,float y,int button);
	virtual int OnMouseUp(float x,float y,int button);
//	virtual int OnKeyDown(int key);
//	virtual int OnKeyUp(int key);
	virtual int OnDraw(void);
	void SetText(std::string text);
	void SetImage(sf::Image *image,float left,float bottom,float right,float top);
	virtual int OnMouseIn(void);
	virtual int OnMouseOut(void);
	virtual int OnMouseMove(float x,float y);
	int ID(){return _ID;};
	int ID(int id){_ID=id;return _ID;};
	CButton(CWindow *parent);
	~CButton();
private:
	sf::FloatRect imageRect;
	sf::Image *Image;
	CLabel *Label;
	float r,g,b;
	CWindow *CallbackWindow;
	void (CWindow::*Callback)( int ID,void *userdata ); 
	void *CallbackUserdata;
protected:
};

#endif