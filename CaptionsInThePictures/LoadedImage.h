#pragma once

#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <wx\richtext\richtextctrl.h>

class LoadedImage
{
public:
	LoadedImage(const std::string& path, wxWindow* parent, wxRichTextCtrl* textPanel);

	wxBitmapButton* GetButton() const;

	std::vector < std::pair <wxString, wxString> > getInfoArr() const;
private:
	void m_btnLoadedImageOnButtonClick(wxCommandEvent& event);

	std::string getExifInfo() const;
	std::string getIptcInfo() const;

	std::string m_path;
	wxRichTextCtrl* m_textPanel;
	std::unique_ptr<wxBitmap> m_bmpImage;
	std::unique_ptr<wxBitmapButton> m_btnImage;
	int m_clickedCount = 0;
};

