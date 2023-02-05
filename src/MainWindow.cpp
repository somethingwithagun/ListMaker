#include "MainWindow.h"
#include "AppLogic.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_IDLE(MainWindow::onIdle)
EVT_MENU(wxID_NEW, MainWindow::onOpen)
EVT_MENU(wxID_EXIT, MainWindow::onQuit)
END_EVENT_TABLE()

void onClose(wxCloseEvent &event);

MainWindow::MainWindow(

	wxWindow *parent,
	wxWindowID id,
	const wxString &title,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxString &name) : wxFrame(parent, id, title, pos, size, style, name)
{
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(330, 230));

	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(panel, 1, wxEXPAND | wxALL, 5);
	this->SetSizerAndFit(sizer);

	FilePathLabel = new wxStaticText(panel, wxID_ANY, "Input path to the file", wxPoint(40, 46));
	InFilePathInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(40, 10), wxSize(250, 25), wxTE_READONLY);
	OpenBtn = new wxButton(panel, wxID_ANY, "Open", wxPoint(210, 45));
	OpenBtn->Bind(wxEVT_BUTTON, &MainWindow::onOpen, this);

	OrderTypeArray.Add("none");
	OrderTypeArray.Add("1), 2), X) ...");
	OrderTypeArray.Add("1., 2., X. ...");
	OrderTypeCheck = new wxRadioBox(panel, wxID_ANY, "Order type:", wxPoint(40, 70), wxDefaultSize, OrderTypeArray);

	SortTypeArray.Add("none");
	SortTypeArray.Add("reverse");
	SortTypeCheck = new wxRadioBox(panel, wxID_ANY, "Sort type:", wxPoint(40, 120), wxDefaultSize, SortTypeArray);

	PrevOptionsCheckOrder = new wxCheckBox(panel, wxID_ANY, "Previous order", wxPoint(180, 130), wxDefaultSize);
	PrevOptionsCheckSort = new wxCheckBox(panel, wxID_ANY, "Previous sort", wxPoint(180, 150), wxDefaultSize);

	button = new wxButton(panel, wxID_ANY, "Print", wxPoint(40, 190));
	button->Bind(wxEVT_BUTTON, &MainWindow::onPrint, this);

	HelpButton = new wxButton(panel, wxID_ANY, "Help", wxPoint(120, 190));
	HelpButton->Bind(wxEVT_BUTTON, &MainWindow::onHelp, this);
	About = new wxButton(panel, wxID_ANY, "About", wxPoint(200, 190));
	About->Bind(wxEVT_BUTTON, &MainWindow::onAbout, this);

	SortTypeCheck->SetSelection(0);
	OrderTypeCheck->SetSelection(0);

	// Bind(wxEVT_CLOSE_WINDOW, &onClose);
	// Unbind(wxEVT_CLOSE_WINDOW, &onClose);*/
}

void MainWindow::onOpen(wxCommandEvent &WXUNUSED(event))
{

	wxFileDialog *openFileDialog = new wxFileDialog(this, _("Open text file"), "", "",
													"text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog->ShowModal() == wxID_CANCEL)
		return;
	else
		InFilePathInput->SetValue(openFileDialog->GetPath());
}
void MainWindow::onIdle(wxIdleEvent &WXUNUSED(event))
{
	if (std::filesystem::exists("Logs"))
	{
		PrevOptionsCheckOrder->Enable(true);
		PrevOptionsCheckSort->Enable(true);

		if (PrevOptionsCheckOrder->IsChecked())
		{
			OrderTypeCheck->Enable(false);
		}
		else
		{
			OrderTypeCheck->Enable(true);
		}
		if (PrevOptionsCheckSort->IsChecked())
		{
			SortTypeCheck->Enable(false);
		}
		else
		{
			SortTypeCheck->Enable(true);
		}
	}
	else
	{
		HaveLog = false;
		PrevOptionsCheckOrder->Enable(false);
		PrevOptionsCheckSort->Enable(false);

		PrevOptionsCheckSort->SetValue(false);
		PrevOptionsCheckOrder->SetValue(false);

		PrevOptionsCheckOrder->Enable(false);
		PrevOptionsCheckSort->Enable(false);

		OrderTypeCheck->Enable(true);

		SortTypeCheck->Enable(true);
	}
}
void MainWindow::onHelp(wxCommandEvent &WXUNUSED(event))
{
	wxMessageBox("You have to select the file you would numerate and select all options you want, then choose where the file will appear");
}
void MainWindow::onAbout(wxCommandEvent &WXUNUSED(event))
{
	wxMessageBox("ListMaker Gui, version 0.2.3, release, Author: somethingwithagun(github)");
}
void MainWindow::onPrint(wxCommandEvent &event)
{
	std::string Filename;
	std::string Filepath = std::string(InFilePathInput->GetValue().mb_str());
	std::string SortType;
	std::string path;
	std::string OrderType;
	if (Filepath == "")
	{
		wxMessageBox("Enter path");
		return;
		event.Skip();
	}
	wxFileDialog *openFileDialog = new wxFileDialog(this, _("Save text file"), "", "",
													"text files |*.txt", wxFD_SAVE);
	if (openFileDialog->ShowModal() == wxID_CANCEL)
		return;
	else
	{
		Filename = openFileDialog->GetFilename();
		path = openFileDialog->GetDirectory();
	}
	if (Filename == "")
	{
		wxMessageBox("Enter name");
		return;
		event.Skip();
	}
	if (PrevOptionsCheckOrder->GetValue() == true)
	{
		OrderType = "prev";
	}
	else
	{
		int OrderTypeIndex = OrderTypeCheck->wxRadioBox::GetSelection();
		if (OrderTypeIndex == 0)
			OrderType = "none";
		else if (OrderTypeIndex == 1)
			OrderType = "brackets";
		else if (OrderTypeIndex == 2)
			OrderType = "dots";
	}
	if (PrevOptionsCheckSort->GetValue() == true)
	{
		SortType = "prev";
	}
	else
	{
		int SortTypeIndex = SortTypeCheck->wxRadioBox::GetSelection();
		if (SortTypeIndex == 0)
			SortType = "none";
		else if (SortTypeIndex == 1)
			SortType = "reverse";
	}

	int result = Magic(Filepath, OrderType, SortType, Filename, path);
	if (result == -1)
		wxMessageBox("Error: File not found");
	else if (result == 1)
		wxMessageBox("Error: File is empty");

	event.Skip();
}
void MainWindow::onQuit(wxCommandEvent &WXUNUSED(event))
{
	bool veto = Close();
}
void onClose(wxCloseEvent &event)
{
	if (event.CanVeto())
	{
		int answer = wxMessageBox(_("Are you leaving?"), _("Leaving"), wxYES_NO);
		if (answer != wxYES)
		{
			event.Veto();
			return;
		}
	}

	event.Skip();
}

MainWindow::~MainWindow()
{
}