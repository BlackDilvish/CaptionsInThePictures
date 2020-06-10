#pragma once

#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <wx\richtext\richtextctrl.h>
#include <wx/sizer.h>

class LoadedImage
{
public:
	LoadedImage(const std::string& path, wxWindow* parent, wxRichTextCtrl* textPanel, wxSizer* sizer, wxGridSizer* m_buttonsSizer, wxScrolledWindow *scrolledWindow);

	wxBitmapButton* GetButton() const;
	const wxBitmap* GetBitmap() const;

	std::vector < std::pair <wxString, wxString> > getInfoArr() const;

	bool isBig() const;
private:
	void m_btnLoadedImageOnButtonClick(wxCommandEvent& event);
	void m_btnLoadedImageDoubleClick(wxMouseEvent& event);
	void m_btnLoadedImageDoubleClickBack(wxMouseEvent& event);

	int rotationCode() const;
	void rotateBitmap(int code);

	std::string getExifInfo() const;
	std::string getIptcInfo() const;

	std::string m_path;
	wxRichTextCtrl* m_textPanel;
	std::unique_ptr<wxBitmap> m_bmpImage;
	std::unique_ptr<wxBitmapButton> m_btnImage;
	std::unique_ptr<wxBitmapButton> m_btnBig;
	wxSizer* m_leftSizer;
	wxGridSizer* m_buttonsSizer;
	wxWindow* m_parent;
	wxScrolledWindow* m_scrolledWindow;
};

