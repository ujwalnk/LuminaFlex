#include "MainForm.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace AutoGlow;

int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	AutoGlow::MainForm form;

	Application::Run(% form);

	return 0;
}

/**
 * Core Functionality
**/
void core() {

}

void MainForm::InitializeTrayIcon()
{
	trayIcon = gcnew NotifyIcon();
	trayIcon->Icon = gcnew System::Drawing::Icon("./icon.ico");
	trayIcon->Text = "Minimized to Tray";
	trayIcon->Visible = true;

	trayMenu = gcnew System::Windows::Forms::ContextMenuStrip();
	trayMenu->Items->Add("Restore", nullptr, gcnew EventHandler(this, &MainForm::RestoreForm));
	trayMenu->Items->Add("Exit", nullptr, gcnew EventHandler(this, &MainForm::ExitApplication));
	trayIcon->DoubleClick += gcnew EventHandler(this, &MainForm::RestoreForm);
	trayIcon->ContextMenuStrip = trayMenu;

}

void MainForm::RestoreForm(Object^ sender, EventArgs^ e)
{
	this->Show();
	this->WindowState = FormWindowState::Normal;
}

void MainForm::ExitApplication(Object^ sender, EventArgs^ e)
{
	trayIcon->Visible = false;
	Application::Exit();
}

void MainForm::MainForm_FormClosing(Object^ sender, FormClosingEventArgs^ e){

	// Save userdata
	fSentinel.setDelta(System::Int32::Parse(this->txtDelta->Text));
	fSentinel.setInterval(System::Int32::Parse(this->txtInterval->Text));
	fSentinel.setUseGammaRamp(this->chkGammaRamp->Checked);

	if (e->CloseReason == CloseReason::UserClosing)
	{
		e->Cancel = true;
		this->Hide();
	}
}