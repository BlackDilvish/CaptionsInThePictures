///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyFrame.h"

///////////////////////////////////////////////////////////////////////////

MyFrame::MyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 650,350 ), wxSize( -1,-1 ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_btnChooseDirectory = new wxButton( this, wxID_ANY, wxT("Wybierz folder ze zdjeciami"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_btnChooseDirectory, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_btnExportInfo = new wxButton( this, wxID_ANY, wxT("Eksportuj dane Exiv2 do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_btnExportInfo, 0, wxALIGN_CENTER|wxALL, 5 );

	m_btnWriteInfoInPicture = new wxButton( this, wxID_ANY, wxT("Eksportuj dane Exiv2 na zdjeciu"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_btnWriteInfoInPicture, 0, wxALIGN_CENTER|wxALL, 5 );

	m_btnReadCaptionsFromFile = new wxButton( this, wxID_ANY, wxT("Wczytaj napisy z pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_btnReadCaptionsFromFile, 0, wxALIGN_CENTER|wxALL, 5 );

	m_tbExifInfo = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_tbExifInfo->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	bSizer3->Add( m_tbExifInfo, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_btnChooseDirectory->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnChooseDirectoryOnButtonClick ), NULL, this );
	m_btnExportInfo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnExportInfoOnButtonClick ), NULL, this );
	m_btnWriteInfoInPicture->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnWriteInfoInPictureOnButtonClick ), NULL, this );
	m_btnReadCaptionsFromFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnReadCaptionsFromFileOnButtonClick ), NULL, this );
}

MyFrame::~MyFrame()
{
	// Disconnect Events
	m_btnChooseDirectory->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnChooseDirectoryOnButtonClick ), NULL, this );
	m_btnExportInfo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnExportInfoOnButtonClick ), NULL, this );
	m_btnWriteInfoInPicture->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnWriteInfoInPictureOnButtonClick ), NULL, this );
	m_btnReadCaptionsFromFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnReadCaptionsFromFileOnButtonClick ), NULL, this );

}
