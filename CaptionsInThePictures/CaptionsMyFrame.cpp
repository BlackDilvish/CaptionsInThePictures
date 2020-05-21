#include "CaptionsMyFrame.h"

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
		m_name.clear();
		auto paths = getImages(dirDialog->GetPath());

		if(m_leftSizer->GetItemCount() > 1)
			m_leftSizer->Hide(m_leftSizer->GetItemCount()-1);

		m_buttonsSizer = new wxGridSizer(2, 2, 0, 0);
		m_leftSizer->Add(m_buttonsSizer);

		m_loadedImages.clear();
		for (size_t i=0; i<paths.size(); i++)
		{
			m_loadedImages.push_back(std::unique_ptr<LoadedImage>(new LoadedImage(paths[i], this, m_tbExifInfo, m_leftSizer, m_buttonsSizer)));
			m_buttonsSizer->Add(m_loadedImages[i]->GetButton());
		}

		Refresh();
		Layout();
	}
}

void CaptionsMyFrame::m_btnExportInfoOnButtonClick( wxCommandEvent& event )
{
	if (!m_name.empty() && !m_loadedImages.empty())
	{
		std::unique_ptr<wxMultiChoiceDialog> choiceDialog{ new wxMultiChoiceDialog(this, "Wybierz zdjeca", "Eksportuj informacje o zdjeciach", m_name.size(), m_name.data()) };
		std::stringstream toSave;

		for (const wxString& filename : m_name)
			toSave << filename << "\n";

		if (choiceDialog->ShowModal() == wxID_OK)
		{
			auto selections = choiceDialog->GetSelections();
			for (const int& x : selections)
				toSave << "\n" << m_name[x] << ":\n" << openSelectWindow(x);

			std::unique_ptr<wxFileDialog> saveDialog{ new wxFileDialog(this, _("Save info file"), "", "","txt files (*.txt)|*.txt", wxFD_SAVE) };

			if (saveDialog->ShowModal() == wxID_OK)
			{
				wxFile file(saveDialog->GetPath(), wxFile::write);
				if (file.IsOpened())
				{
					file.Write(toSave.str());
					file.Close();
				}
			}
		}
	}
	else
	{
		std::unique_ptr<wxMessageDialog> messageDialog{ new wxMessageDialog(this, "Nie znaleziono zdjec!", "Ostrzezenie") };
		messageDialog->ShowModal();
	}
}

std::vector<std::string> CaptionsMyFrame::getImages(const wxString& dirPath)
{
	std::vector<std::string> paths;
	wxDir dir(dirPath);

	wxString filename;
	bool cont = dir.GetFirst(&filename, _T("*.jpg"));
	while (cont)
	{
		paths.push_back(std::string(dirPath + "\\" + filename));
		m_name.push_back(filename);
		cont = dir.GetNext(&filename);
	}

	return paths;
}

wxString CaptionsMyFrame::openSelectWindow(int index) 
{
	auto infoVec = m_loadedImages[index]->getInfoArr();
	auto infoKeys = std::make_unique<wxString[]>(infoVec.size());
	std::stringstream toSave;

	const int infoSize = infoVec.size();

	for (int i = 0; i < infoSize; i++)
		infoKeys[i] = infoVec[i].first;

	std::unique_ptr<wxMultiChoiceDialog> choiceDialog{ new wxMultiChoiceDialog(this, "Wybierz informacje dla " + m_name[index], "Eksportuj informacje o zdjeciach", infoSize, infoKeys.get()) };

	if (choiceDialog->ShowModal() == wxID_OK)
	{
		auto selections = choiceDialog->GetSelections();
		for (const int& x : selections)
			toSave << infoVec[x].first << ": " << infoVec[x].second << std::endl;
	}
	return toSave.str();
}