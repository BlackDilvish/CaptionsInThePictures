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

	m_tbExifInfo = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_tbExifInfo->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	bSizer3->Add( m_tbExifInfo, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar2 = new wxMenuBar( 0 );
	m_menuSave = new wxMenu();
	wxMenuItem* m_itemExportToTxt;
	m_itemExportToTxt = new wxMenuItem( m_menuSave, wxID_ANY, wxString( wxT("Eksportuj dane exif do &pliku") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSave->Append( m_itemExportToTxt );

	wxMenuItem* m_itemExportToImage;
	m_itemExportToImage = new wxMenuItem( m_menuSave, wxID_ANY, wxString( wxT("Eksportuj dane exif na &zdjeciu") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSave->Append( m_itemExportToImage );

	m_menubar2->Append( m_menuSave, wxT("&Zapisz") );

	m_menuLoad = new wxMenu();
	wxMenuItem* m_menuLoadCaptions;
	m_menuLoadCaptions = new wxMenuItem( m_menuLoad, wxID_ANY, wxString( wxT("&Wczytaj napisy z pliku") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuLoad->Append( m_menuLoadCaptions );

	m_menubar2->Append( m_menuLoad, wxT("&Wczytaj") );

	m_menuInfo = new wxMenu();
	wxMenuItem* m_menuAuthors;
	m_menuAuthors = new wxMenuItem( m_menuInfo, wxID_ANY, wxString( wxT("&Autorzy") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuInfo->Append( m_menuAuthors );

	m_menubar2->Append( m_menuInfo, wxT("&Info") );

	this->SetMenuBar( m_menubar2 );


	this->Centre( wxBOTH );

	// Connect Events
	m_btnChooseDirectory->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnChooseDirectoryOnButtonClick ), NULL, this );
	m_menuSave->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::m_itemExportToTxtOnMenuSelection ), this, m_itemExportToTxt->GetId());
	m_menuSave->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::m_itemExportToImageOnMenuSelection ), this, m_itemExportToImage->GetId());
	m_menuLoad->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::m_menuLoadCaptionsOnMenuSelection ), this, m_menuLoadCaptions->GetId());
	m_menuInfo->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame::m_menuAuthorsOnMenuSelection ), this, m_menuAuthors->GetId());
}

MyFrame::~MyFrame()
{
	// Disconnect Events
	m_btnChooseDirectory->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::m_btnChooseDirectoryOnButtonClick ), NULL, this );

}
