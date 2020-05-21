///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame
///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame
{
	private:

	protected:
		wxButton* m_btnChooseDirectory;
		wxButton* m_btnExportInfo;
		wxButton* m_btnWriteInfoInPicture;
		wxRichTextCtrl* m_tbExifInfo;

		// Virtual event handlers, overide them in your derived class
		virtual void m_btnChooseDirectoryOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_btnExportInfoOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_btnWriteInfoInPictureOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1030,533 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame();

};

