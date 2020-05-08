#pragma once

#include"wx/wx.h"
#include"CaptionsMyFrame.h"

class MyApp : public wxApp
{
public:
	MyApp() = default;
	~MyApp() = default;

	virtual bool OnInit();
	virtual int OnExit() { return 0; }

private:
	wxFrame* m_frame = nullptr;
};

