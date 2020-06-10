#include "CaptionsMyFrame.h"

CaptionsMyFrame::CaptionsMyFrame( wxWindow* parent )
:
MyFrame( parent )
{
	SetTitle("Napisy na zdjêciach");
}

void CaptionsMyFrame::m_btnChooseDirectoryOnButtonClick( wxCommandEvent& event )
{
	std::unique_ptr<wxDirDialog> dirDialog{ new wxDirDialog(this, "Wybierz folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST) };

	if (dirDialog->ShowModal() == wxID_OK)
	{
		m_name.clear();
		auto paths = getImages(dirDialog->GetPath());

		if (m_leftSizer->GetItemCount() > 1)
			m_leftSizer->Hide(m_leftSizer->GetItemCount() - 1);


		m_scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
		m_scrolledWindow->SetScrollRate(5, 5);

		m_buttonsSizer = new wxGridSizer(0, 4, 15, 15);
		m_scrolledWindow->SetSizer(m_buttonsSizer);
		m_scrolledWindow->Layout();
		m_buttonsSizer->Fit(m_scrolledWindow);
		m_leftSizer->Add(m_scrolledWindow, 1, wxEXPAND | wxALL, 5);

		m_loadedImages.clear();
		for (size_t i = 0; i < paths.size(); i++)
		{
			m_loadedImages.push_back(std::unique_ptr<LoadedImage>(new LoadedImage(paths[i], this, m_tbExifInfo, m_leftSizer, m_buttonsSizer, m_scrolledWindow)));
			m_buttonsSizer->Add(m_loadedImages[i]->GetButton());
		}

		Refresh();
		Layout();
	}
}

void CaptionsMyFrame::m_itemExportToTxtOnMenuSelection( wxCommandEvent& event )
{
	if (!m_name.empty() && !m_loadedImages.empty())
	{
		std::unique_ptr<wxMultiChoiceDialog> choiceDialog{ new wxMultiChoiceDialog(this, "Wybierz zdjecia", "Eksportuj informacje o zdjeciach", m_name.size(), m_name.data()) };
		std::stringstream toSave;

		for (const wxString& filename : m_name)
			toSave << filename << "\n";

		if (choiceDialog->ShowModal() == wxID_OK)
		{
			auto selections = choiceDialog->GetSelections();
			for (const int& x : selections)
			{
				std::pair <wxString, bool> p = openSelectWindow(x);
				if(p.second)
					toSave << "\n" << m_name[x] << ":\n" << p.first;
			}
				
			std::unique_ptr<wxFileDialog> saveDialog{ new wxFileDialog(this, _("Zapisz plik"), "", "","txt files (*.txt)|*.txt", wxFD_SAVE) };

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

void CaptionsMyFrame::m_itemExportToImageOnMenuSelection( wxCommandEvent& event )
{
	if (!m_name.empty() && !m_loadedImages.empty())
	{
		for(unsigned int i = 0; i < m_loadedImages.size(); ++i)
			if (m_loadedImages[i]->isBig())
			{
				std::stringstream toSave;
				std::pair <wxString, bool> p = openSelectWindow(i);
				if (p.second)
				{
					toSave << m_name[i] << ":\n" << p.first;
					openSaveWindow(i, toSave);
				}
				break;
			}
			else if (i == m_loadedImages.size() - 1)
			{
				std::unique_ptr<wxMultiChoiceDialog> choiceDialog{ new wxMultiChoiceDialog(this, "Wybierz zdjecia", "Eksportuj informacje o zdjeciach", m_name.size(), m_name.data()) };

				if (choiceDialog->ShowModal() == wxID_OK)
				{
					auto selections = choiceDialog->GetSelections();
					std::vector<std::stringstream> captionsVector(selections.GetCount());
					int index = 0;

					for (const int& x : selections)
					{
						std::pair <wxString, bool> p = openSelectWindow(x);
						if (p.second)
						{
							captionsVector[index] << m_name[x] << ":\n" << p.first;
							openSaveWindow(x, captionsVector[index++]);
						}
					}

					if (index)
					{
						std::unique_ptr<wxMessageDialog> messageDialog{ new wxMessageDialog(this, "Pomyslnie zapisano " + std::to_string(index) + " nowych zdjec", "Sukces") };
						messageDialog->ShowModal();
					}
					else
					{
						std::unique_ptr<wxMessageDialog> messageDialog{ new wxMessageDialog(this, "Nie wybrano zdjec do zapisania", "Ostrzezenie") };
						messageDialog->ShowModal();
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

void CaptionsMyFrame::m_menuLoadCaptionsOnMenuSelection( wxCommandEvent& event )
{
	std::unique_ptr<wxFileDialog> fileDialog{ new wxFileDialog(this, _("Otworz plik txt"), "", "", "TXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST) };
	if (fileDialog->ShowModal() == wxID_OK)
	{
		wxFileInputStream inputStream(fileDialog->GetPath());
		wxTextFile file;
		if (inputStream.IsOk() && file.Open(fileDialog->GetPath()))
		{
			std::string line(file.GetFirstLine());
			int index = isFilename(line);
			std::stringstream toSave;

			while (index == -1)
			{
				line = file.GetNextLine();
				index = isFilename(line);
				if (file.Eof())
				{
					std::unique_ptr<wxMessageDialog> messageDialog{ new wxMessageDialog(this, "Nie znaleziono pasujacych zdjec!", "Ostrzezenie") };
					messageDialog->ShowModal();
					break;
				}
			}

			while (!file.Eof())
			{
				line = file.GetNextLine();
				if (isFilename(line) == -1)
					toSave << line << "\n";
				else
				{
					openSaveWindow(index, toSave);
					index = isFilename(line);
					toSave.str(std::string());
				}
				if (file.Eof())
					openSaveWindow(index, toSave);
			}
		}
		else
		{
			std::unique_ptr<wxMessageDialog> messageDialog{ new wxMessageDialog(this, "Nie udalo sie otworzyc pliku", "Ostrzezenie") };
			messageDialog->ShowModal();
		}
	}
}

void CaptionsMyFrame::m_menuAuthorsOnMenuSelection( wxCommandEvent& event )
{
	std::string authorsInfo = "Projekt 21: \"Napisy na zdjêciach\"\nAutorzy:\nOlga Kubiszyn\nGabriel Naleznik\nJan Zajda";

	std::unique_ptr<wxMessageDialog> messageDialog{ new wxMessageDialog(this, authorsInfo, "Autorzy") };
	messageDialog->ShowModal();
}

void CaptionsMyFrame::openSaveWindow(int index, const std::stringstream& toSave)
{
	wxMemoryDC mdc;
	std::unique_ptr<wxBitmap> bmp{ new wxBitmap(*m_loadedImages[index]->GetBitmap()) };
	mdc.SelectObject(*bmp);
	wxColour colour(255 - bmp->ConvertToImage().GetRed(10, 10), 255 - bmp->ConvertToImage().GetGreen(10, 10), 255 - bmp->ConvertToImage().GetBlue(10, 10));
	mdc.SetTextForeground(colour);
	wxFont font;
	wxSize size = bmp->GetSize();
	font.SetPixelSize(wxSize(0, size.y / 50));
	mdc.SetFont(font);
	mdc.DrawText(toSave.str(), wxPoint(10, 10));

	std::unique_ptr<wxFileDialog> saveDialog{ new wxFileDialog(this, std::string("Zapisz nowe " + m_name[index]), "", "","jpg files (*.jpg)|*.jpg", wxFD_SAVE) };

	if (saveDialog->ShowModal() == wxID_OK)
		bmp->SaveFile(saveDialog->GetPath(), wxBITMAP_TYPE_JPEG);

	mdc.SelectObject(wxNullBitmap);
}

std::pair <wxString, bool> CaptionsMyFrame::openSelectWindow(int index)
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
		return std::make_pair<wxString, bool>(toSave.str(), true);
	}
	else
		return std::make_pair<wxString, bool>(toSave.str(), false);
}

int CaptionsMyFrame::isFilename(std::string str) const
{
	if (str.back() == ':')
	{
		str.pop_back();
		wxString tmp(str);
		for(unsigned int index = 0; index < m_name.size(); ++index)
			if (tmp == m_name[index])
				return index;
	}
	return -1;
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