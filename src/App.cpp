#include "App.h"
#include "id.h"
#include "MainWindow.h"

IMPLEMENT_APP(App);

App::App()
{
}

bool App::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}
	MainWindow* main = new MainWindow(nullptr, window::id::MAINWINDOW, _("ListMaker"), wxDefaultPosition, wxSize(330, 230), wxMINIMIZE_BOX | wxSYSTEM_MENU
		| wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN);
	main->Show();
	return true;
}
App::~App()
{
}