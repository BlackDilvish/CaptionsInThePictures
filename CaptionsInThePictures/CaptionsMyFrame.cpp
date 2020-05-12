#include "CaptionsMyFrame.h"
#include <wx/dirdlg.h>
#include <wx/dir.h>
#include <exiv2/exiv2.hpp>

#include <iomanip>
#include <cassert>
#include <sstream>
#include <memory>

CaptionsMyFrame::CaptionsMyFrame( wxWindow* parent )
:
MyFrame( parent )
{
	SetTitle("Napisy na zdjeciach");
}

void CaptionsMyFrame::m_btnChooseDirectoryOnButtonClick( wxCommandEvent& event )
{
	std::unique_ptr<wxDirDialog> dirDialog{ new wxDirDialog(this, "Choose input directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST) };

	if (dirDialog->ShowModal() == wxID_OK)
	{
		wxDir dir(dirDialog->GetPath());

		wxString filename;
		bool cont = dir.GetFirst(&filename, _T("*.jpg"));
		while (cont)
		{
			m_tbExifInfo->AppendText(getExifData(std::string(dirDialog->GetPath() + "/" + filename)));
			m_tbExifInfo->AppendText(getIptcData(std::string(dirDialog->GetPath() + "/" + filename)));

			cont = dir.GetNext(&filename);
		}
	}
}

std::string CaptionsMyFrame::getExifData(const std::string& filepath)
{
	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filepath);
	assert(image.get() != 0);
	image->readMetadata();

	std::stringstream ss;

	ss << std::setw(60) << std::setfill(' ') << std::left
		<< "Nazwa pliku:" << " " << filepath << "\n";

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

std::string CaptionsMyFrame::getIptcData(const std::string& filepath)
{
	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filepath);
	assert(image.get() != 0);
	image->readMetadata();

	std::stringstream ss;

	ss << std::setw(60) << std::setfill(' ') << std::left
		<< "Nazwa pliku:" << " " << filepath << "\n";

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

