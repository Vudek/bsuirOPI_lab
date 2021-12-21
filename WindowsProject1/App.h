#pragma once

#include "wx/wx.h"
#include "cMain.h"

class App: public wxApp
{
private:
	cMain* mFrame; // Main frame
public:
	App();
	~App();
public:
	virtual bool OnInit();
	virtual int OnExit();
};

