#include "LoadedImage.h"
#include <exiv2/exiv2.hpp>
#include <sstream>

LoadedImage::LoadedImage(const std::string& path, wxWindow* parent, wxRichTextCtrl* textPanel, wxSizer* sizer, wxGridSizer* m_buttonsSizer)
	: m_path(path),
	m_textPanel(textPanel),
	m_bmpImage(std::unique_ptr<wxBitmap>(new wxBitmap(path, wxBITMAP_TYPE_JPEG))),
	m_btnImage(std::unique_ptr<wxBitmapButton>(new wxBitmapButton(parent, wxID_ANY, m_bmpImage->ConvertToImage().Rescale(100, 100), wxDefaultPosition, wxSize(100, 100)))),
	m_leftSizer(sizer),
	m_buttonsSizer(m_buttonsSizer),
	m_parent(parent)
{
	m_bmpBig = std::unique_ptr<wxBitmap>(new wxBitmap(path, wxBITMAP_TYPE_JPEG));
	m_btnImage->Bind(wxEVT_BUTTON, &LoadedImage::m_btnLoadedImageOnButtonClick, this);
	m_btnImage->Bind(wxEVT_LEFT_DCLICK, &LoadedImage::m_btnLoadedImageDoubleClick, this);
}

wxBitmapButton* LoadedImage::GetButton() const
{
	return m_btnImage.get();
}

void LoadedImage::m_btnLoadedImageOnButtonClick(wxCommandEvent& event)
{
	m_textPanel->Clear();
	m_textPanel->AppendText(getExifInfo());
	m_textPanel->AppendText(getIptcInfo());
}

void LoadedImage::m_btnLoadedImageDoubleClick(wxMouseEvent& event)
{
	wxSize size = m_leftSizer->GetSize();
	m_leftSizer->Hide(m_buttonsSizer);
	wxImage temp = m_bmpBig->ConvertToImage();
	int h = temp.GetHeight();
	int w = temp.GetWidth();
	int new_w = size.x;
	int new_h = size.x*h / static_cast<double>(w);
	m_btnBig = std::unique_ptr<wxBitmapButton>(new wxBitmapButton(m_parent, wxID_ANY, m_bmpBig->ConvertToImage().Rescale(new_w, new_h), wxPoint(0, 40), wxSize(new_w, new_h)));
	m_btnBig->Bind(wxEVT_LEFT_DCLICK, &LoadedImage::m_btnLoadedImageDoubleClickBack, this);
}

void LoadedImage::m_btnLoadedImageDoubleClickBack(wxMouseEvent& event)
{
	m_leftSizer->Show(m_buttonsSizer);
	m_btnBig = nullptr;
}

std::string LoadedImage::getExifInfo() const
{
	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(m_path);
	assert(image.get() != 0);
	image->readMetadata();

	std::stringstream ss;

	ss << std::setw(60) << std::setfill(' ') << std::left
		<< "Sciezka pliku:" << " " << m_path << "\n";

	Exiv2::ExifData& exifData = image->exifData();
	if (exifData.empty())
		ss << "No Exif data found in file";

	Exiv2::ExifData::const_iterator end = exifData.end();
	for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i)
	{
		const char* tn = i->typeName();
		if (std::string(tn) != "Undefined")
			ss << std::setw(60) << std::setfill(' ') << std::left
			<< i->key() << " " << i->value() << std::endl;
	}

	return ss.str();
}

std::string LoadedImage::getIptcInfo() const
{
	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(m_path);
	assert(image.get() != 0);
	image->readMetadata();

	std::stringstream ss;

	ss << std::setw(60) << std::setfill(' ') << std::left
		<< "Sciezka pliku:" << " " << m_path << "\n";

	Exiv2::IptcData& iptcData = image->iptcData();
	if (iptcData.empty())
		ss << ": No IPTC data found in the file\n";

	Exiv2::IptcData::iterator end2 = iptcData.end();
	for (Exiv2::IptcData::iterator md = iptcData.begin(); md != end2; ++md) {
		ss << std::setw(60) << std::setfill(' ') << std::left
			<< md->key() << " " << md->value() << std::endl;
	}

	return ss.str();
}
