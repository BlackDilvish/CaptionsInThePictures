#include "LoadedImage.h"
#include <exiv2/exiv2.hpp>
#include <sstream>

LoadedImage::LoadedImage(const std::string& path, wxWindow* parent, wxRichTextCtrl* textPanel)
	: m_path(path),
	m_textPanel(textPanel),
	m_bmpImage(std::unique_ptr<wxBitmap>(new wxBitmap(path, wxBITMAP_TYPE_JPEG))),
	m_btnImage(std::unique_ptr<wxBitmapButton>(new wxBitmapButton(parent, wxID_ANY, m_bmpImage->ConvertToImage().Rescale(100, 100), wxDefaultPosition, wxSize(100, 100))))
{
	m_btnImage->Bind(wxEVT_BUTTON, &LoadedImage::m_btnLoadedImageOnButtonClick, this);
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
