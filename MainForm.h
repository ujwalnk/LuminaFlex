#pragma once

#include "FileSentinel.h"
#include "gammaramp.h"

#include <string>
#include <cstring>

namespace AutoGlow {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	FileSentinel fSentinel;
	CGammaRamp gSentinel;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		NotifyIcon^ trayIcon;
		System::Windows::Forms::ContextMenuStrip^ trayMenu;

	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			InitializeComponent();
			InitializeTrayIcon();

			this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
	
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// 
		
		void InitializeTrayIcon();
		void RestoreForm(Object^ sender, EventArgs^ e);
		void ExitApplication(Object^ sender, EventArgs^ e);
		void MainForm_FormClosing(Object^ sender, FormClosingEventArgs^ e);


		~MainForm()
		{
			if (components)
			{
				delete components;
			}

			delete trayIcon;
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ lblLum;

	private: System::Windows::Forms::TextBox^ txtInterval;

	private: System::Windows::Forms::TextBox^ txtDelta;
	private: System::Windows::Forms::CheckBox^ chkGammaRamp;
	private: System::Windows::Forms::Button^ btnConfigure;
	private: System::Windows::Forms::Button^ btnDisable;
	private: System::Windows::Forms::Button^ btnEnable;
	private: System::Windows::Forms::Label^ label5;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lblLum = (gcnew System::Windows::Forms::Label());
			this->txtInterval = (gcnew System::Windows::Forms::TextBox());
			this->txtDelta = (gcnew System::Windows::Forms::TextBox());
			this->chkGammaRamp = (gcnew System::Windows::Forms::CheckBox());
			this->btnConfigure = (gcnew System::Windows::Forms::Button());
			this->btnDisable = (gcnew System::Windows::Forms::Button());
			this->btnEnable = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->label1->Location = System::Drawing::Point(12, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(96, 19);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Gamma Ramp";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->label2->Location = System::Drawing::Point(67, 47);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 19);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Delta";
			this->label2->Click += gcnew System::EventHandler(this, &MainForm::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->label3->Location = System::Drawing::Point(53, 81);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 19);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Interval";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->label4->Location = System::Drawing::Point(33, 117);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(75, 19);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Luminance";
			// 
			// lblLum
			// 
			this->lblLum->AutoSize = true;
			this->lblLum->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->lblLum->Location = System::Drawing::Point(126, 117);
			this->lblLum->Name = L"lblLum";
			this->lblLum->Size = System::Drawing::Size(40, 19);
			this->lblLum->TabIndex = 4;
			this->lblLum->Text = L"{0, 0}";
			// 
			// txtInterval
			// 
			this->txtInterval->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->txtInterval->Location = System::Drawing::Point(130, 75);
			this->txtInterval->Name = L"txtInterval";
			this->txtInterval->Size = System::Drawing::Size(100, 25);
			this->txtInterval->TabIndex = 5;
			// 
			// txtDelta
			// 
			this->txtDelta->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->txtDelta->Location = System::Drawing::Point(130, 41);
			this->txtDelta->Name = L"txtDelta";
			this->txtDelta->Size = System::Drawing::Size(100, 25);
			this->txtDelta->TabIndex = 6;
			// 
			// chkGammaRamp
			// 
			this->chkGammaRamp->AutoSize = true;
			this->chkGammaRamp->ForeColor = System::Drawing::Color::Green;
			this->chkGammaRamp->Location = System::Drawing::Point(130, 14);
			this->chkGammaRamp->Name = L"chkGammaRamp";
			this->chkGammaRamp->Size = System::Drawing::Size(15, 14);
			this->chkGammaRamp->TabIndex = 7;
			this->chkGammaRamp->UseVisualStyleBackColor = true;
			// 
			// btnConfigure
			// 
			this->btnConfigure->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnConfigure->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->btnConfigure->Location = System::Drawing::Point(130, 149);
			this->btnConfigure->Name = L"btnConfigure";
			this->btnConfigure->Size = System::Drawing::Size(100, 30);
			this->btnConfigure->TabIndex = 10;
			this->btnConfigure->Text = L"Configure";
			this->btnConfigure->UseVisualStyleBackColor = true;
			this->btnConfigure->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// btnDisable
			// 
			this->btnDisable->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnDisable->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->btnDisable->Location = System::Drawing::Point(130, 198);
			this->btnDisable->Name = L"btnDisable";
			this->btnDisable->Size = System::Drawing::Size(100, 30);
			this->btnDisable->TabIndex = 12;
			this->btnDisable->Text = L"Disable";
			this->btnDisable->UseVisualStyleBackColor = true;
			// 
			// btnEnable
			// 
			this->btnEnable->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnEnable->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->btnEnable->Location = System::Drawing::Point(16, 198);
			this->btnEnable->Name = L"btnEnable";
			this->btnEnable->Size = System::Drawing::Size(100, 30);
			this->btnEnable->TabIndex = 13;
			this->btnEnable->Text = L"Enable";
			this->btnEnable->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->label5->Location = System::Drawing::Point(173, 11);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(57, 19);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Caution";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(248, 247);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->btnEnable);
			this->Controls->Add(this->btnDisable);
			this->Controls->Add(this->btnConfigure);
			this->Controls->Add(this->chkGammaRamp);
			this->Controls->Add(this->txtDelta);
			this->Controls->Add(this->txtInterval);
			this->Controls->Add(this->lblLum);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"AutoGlow";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
		}
	
		/**
		* Load the stored values to the forms  
		**/
		private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		
			// Load the stored values for Delta and Interval
			txtDelta->Text = fSentinel.getDelta().ToString();
			txtInterval->Text = fSentinel.getInterval().ToString();

			// Set the Luminance measured
			this->lblLum->Text = "{" + fSentinel.getMinLum().ToString() + ", " + fSentinel.getMaxLum().ToString() + "}";

			gSentinel.SetBrightness(NULL, fSentinel.getDelta());
	
		}

		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		}


};
}
