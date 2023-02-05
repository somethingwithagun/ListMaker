#pragma once
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/button.h>
#endif

class MainWindow : public wxFrame
{
public:
	MainWindow(
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE,
		const wxString& name = wxASCII_STR(wxFrameNameStr));
	~MainWindow();

	wxBoxSizer* sizer = nullptr;
	wxTextCtrl* InFilePathInput = nullptr;
	wxStaticText* FilePathLabel = nullptr;
	wxButton* button = nullptr;
	wxButton* HelpButton = nullptr;
	wxButton* OpenBtn = nullptr;
	wxButton* PrintPrevBtn = nullptr;
	wxButton* About = nullptr;
	wxPanel* panel = nullptr;
	wxRadioBox* SortTypeCheck = nullptr;
	wxRadioBox* OrderTypeCheck = nullptr;
	wxArrayString SortTypeArray;
	wxArrayString OrderTypeArray;
	wxArrayString PrevOptionsArray;
	wxCheckBox* PrevOptionsCheckOrder = nullptr;
	wxCheckBox* PrevOptionsCheckSort = nullptr;
	bool HaveLog = false;
	int SortTypeIndex = 0;
	int OrderTypeIndex = 0;

	void onOpen(wxCommandEvent& event);
	void onQuit(wxCommandEvent& event);
	void onPrint(wxCommandEvent& event);
	void onHelp(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);
	void onIdle(wxIdleEvent& event);
	DECLARE_EVENT_TABLE()

};

