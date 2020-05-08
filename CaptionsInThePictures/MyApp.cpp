#include "MyApp.h"
#include"CaptionsMyFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	m_frame = new CaptionsMyFrame(nullptr);
	m_frame->Show(true);
	SetTopWindow(m_frame);

	return true;
}
