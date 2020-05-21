#pragma once

#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include<string>
#include<memory>
#include <wx\richtext\richtextctrl.h>
#include <wx/sizer.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

class LoadedImage
{
public:
	LoadedImage(const std::string& path, wxWindow* parent, wxRichTextCtrl* textPanel, wxSizer* sizer, wxGridSizer* m_buttonsSizer);

	wxBitmapButton* GetButton() const;

private:
	void m_btnLoadedImageOnButtonClick(wxCommandEvent& event);
	void m_btnLoadedImageDoubleClick(wxMouseEvent& event);
	void m_btnLoadedImageDoubleClickBack(wxMouseEvent& event);
	std::string getExifInfo() const;
	std::string getIptcInfo() const;

	std::string m_path;
	wxRichTextCtrl* m_textPanel;
	std::unique_ptr<wxBitmap> m_bmpImage;
	std::unique_ptr<wxBitmap> m_bmpBig;
	std::unique_ptr<wxBitmapButton> m_btnImage;
	std::unique_ptr<wxBitmapButton> m_btnBig;
	int m_clickedCount = 0;
	wxSizer* m_leftSizer;
	wxGridSizer* m_buttonsSizer;
	wxWindow* m_parent;

};

