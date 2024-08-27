#pragma once
#include"database.h"
#include<mysql.h>
#include"CrimeDetails.h"
#include"Criminals.h"
#include"Weapons.h"
#include"Forensics.h"
#include"FIR.h"
#include"Cases.h"
#include"Evidences.h"
#include"Officers.h"


namespace CMS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();
			notipanel->Hide(); 
			dbPanel->Hide(); 
			//
			//TODO: Add the constructor code here
			//
		}
	private: System::Windows::Forms::Button^ dbPnlClose;
	private: System::Windows::Forms::TextBox^ dbUsrNameTxtBox;

	private: System::Windows::Forms::Label^ passwordLbl;
	private: System::Windows::Forms::Label^ usernamelbl;
	private: System::Windows::Forms::TextBox^ dbPsBox;

	private: System::Windows::Forms::Button^ dbPnlHelpBtn;
	private: System::Windows::Forms::Label^ notiLabel;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ notipanel;
	private: System::Windows::Forms::Button^ notiPnlBtn1;
	private: System::Windows::Forms::Label^ label3;


	public: bool isDbEnabled = false;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Label^ notificationbell;
	private: System::Windows::Forms::Button^ crimedetailsbtn;
	private: System::Windows::Forms::Button^ criminalbtn;
	private: System::Windows::Forms::Button^ weaponsbtn;
	private: System::Windows::Forms::Button^ casesbtn;
	private: System::Windows::Forms::Button^ firbtn;
	private: System::Windows::Forms::Button^ officersbtn;
	private: System::Windows::Forms::Button^ evidencebtn;
	private: System::Windows::Forms::Button^ forensicbtn;
	private: System::Windows::Forms::ToolStripMenuItem^ logoutToolStripMenuItem;
	private: System::Windows::Forms::Label^ logouticon;
	private: System::Windows::Forms::Button^ db_btn;
	private: System::Windows::Forms::Label^ db_label;
	private: System::Windows::Forms::Button^ dbPnlBtn;
	private: System::Windows::Forms::Panel^ dbPanel;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::CheckBox^ csvCheck;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->logoutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notificationbell = (gcnew System::Windows::Forms::Label());
			this->crimedetailsbtn = (gcnew System::Windows::Forms::Button());
			this->criminalbtn = (gcnew System::Windows::Forms::Button());
			this->weaponsbtn = (gcnew System::Windows::Forms::Button());
			this->casesbtn = (gcnew System::Windows::Forms::Button());
			this->firbtn = (gcnew System::Windows::Forms::Button());
			this->officersbtn = (gcnew System::Windows::Forms::Button());
			this->evidencebtn = (gcnew System::Windows::Forms::Button());
			this->forensicbtn = (gcnew System::Windows::Forms::Button());
			this->logouticon = (gcnew System::Windows::Forms::Label());
			this->db_btn = (gcnew System::Windows::Forms::Button());
			this->db_label = (gcnew System::Windows::Forms::Label());
			this->dbPnlBtn = (gcnew System::Windows::Forms::Button());
			this->dbPanel = (gcnew System::Windows::Forms::Panel());
			this->passwordLbl = (gcnew System::Windows::Forms::Label());
			this->usernamelbl = (gcnew System::Windows::Forms::Label());
			this->dbPsBox = (gcnew System::Windows::Forms::TextBox());
			this->dbUsrNameTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->dbPnlHelpBtn = (gcnew System::Windows::Forms::Button());
			this->dbPnlClose = (gcnew System::Windows::Forms::Button());
			this->csvCheck = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->notiLabel = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->notipanel = (gcnew System::Windows::Forms::Panel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->notiPnlBtn1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->dbPanel->SuspendLayout();
			this->notipanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->fileToolStripMenuItem,
					this->editToolStripMenuItem, this->aboutToolStripMenuItem, this->exitToolStripMenuItem, this->logoutToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1188, 38);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->fileToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(57, 34);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->editToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(61, 34);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->aboutToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(82, 34);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->exitToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(60, 34);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main::exitToolStripMenuItem_Click);
			// 
			// logoutToolStripMenuItem
			// 
			this->logoutToolStripMenuItem->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->logoutToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
			this->logoutToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->logoutToolStripMenuItem->Name = L"logoutToolStripMenuItem";
			this->logoutToolStripMenuItem->Size = System::Drawing::Size(98, 34);
			this->logoutToolStripMenuItem->Text = L"Logout";
			this->logoutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main::logoutToolStripMenuItem_Click);
			// 
			// notificationbell
			// 
			this->notificationbell->BackColor = System::Drawing::Color::Transparent;
			this->notificationbell->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->notificationbell->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"notificationbell.Image")));
			this->notificationbell->Location = System::Drawing::Point(-15, 594);
			this->notificationbell->Name = L"notificationbell";
			this->notificationbell->Size = System::Drawing::Size(62, 49);
			this->notificationbell->TabIndex = 11;
			this->notificationbell->Click += gcnew System::EventHandler(this, &Main::notificationbell_Click);
			// 
			// crimedetailsbtn
			// 
			this->crimedetailsbtn->AutoSize = true;
			this->crimedetailsbtn->BackColor = System::Drawing::Color::Transparent;
			this->crimedetailsbtn->FlatAppearance->BorderSize = 0;
			this->crimedetailsbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->crimedetailsbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crimedetailsbtn->ForeColor = System::Drawing::Color::Transparent;
			this->crimedetailsbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->crimedetailsbtn->Location = System::Drawing::Point(179, 63);
			this->crimedetailsbtn->Name = L"crimedetailsbtn";
			this->crimedetailsbtn->Size = System::Drawing::Size(218, 46);
			this->crimedetailsbtn->TabIndex = 13;
			this->crimedetailsbtn->Text = L"1. Crime Details";
			this->crimedetailsbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->crimedetailsbtn->UseVisualStyleBackColor = false;
			this->crimedetailsbtn->Click += gcnew System::EventHandler(this, &Main::crimedetailsbtn_Click);
			// 
			// criminalbtn
			// 
			this->criminalbtn->AutoSize = true;
			this->criminalbtn->BackColor = System::Drawing::Color::Transparent;
			this->criminalbtn->FlatAppearance->BorderSize = 0;
			this->criminalbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->criminalbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->criminalbtn->ForeColor = System::Drawing::Color::Transparent;
			this->criminalbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->criminalbtn->Location = System::Drawing::Point(179, 133);
			this->criminalbtn->Name = L"criminalbtn";
			this->criminalbtn->Size = System::Drawing::Size(218, 46);
			this->criminalbtn->TabIndex = 13;
			this->criminalbtn->Text = L"2. Criminals";
			this->criminalbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->criminalbtn->UseVisualStyleBackColor = false;
			this->criminalbtn->Click += gcnew System::EventHandler(this, &Main::criminalbtn_Click);
			// 
			// weaponsbtn
			// 
			this->weaponsbtn->AutoSize = true;
			this->weaponsbtn->BackColor = System::Drawing::Color::Transparent;
			this->weaponsbtn->FlatAppearance->BorderSize = 0;
			this->weaponsbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->weaponsbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->weaponsbtn->ForeColor = System::Drawing::Color::Transparent;
			this->weaponsbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->weaponsbtn->Location = System::Drawing::Point(179, 203);
			this->weaponsbtn->Name = L"weaponsbtn";
			this->weaponsbtn->Size = System::Drawing::Size(218, 46);
			this->weaponsbtn->TabIndex = 13;
			this->weaponsbtn->Text = L"3. Weapons";
			this->weaponsbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->weaponsbtn->UseVisualStyleBackColor = false;
			this->weaponsbtn->Click += gcnew System::EventHandler(this, &Main::weaponsbtn_Click);
			// 
			// casesbtn
			// 
			this->casesbtn->AutoSize = true;
			this->casesbtn->BackColor = System::Drawing::Color::Transparent;
			this->casesbtn->FlatAppearance->BorderSize = 0;
			this->casesbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->casesbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->casesbtn->ForeColor = System::Drawing::Color::Transparent;
			this->casesbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->casesbtn->Location = System::Drawing::Point(179, 273);
			this->casesbtn->Name = L"casesbtn";
			this->casesbtn->Size = System::Drawing::Size(218, 46);
			this->casesbtn->TabIndex = 13;
			this->casesbtn->Text = L"4. Cases";
			this->casesbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->casesbtn->UseVisualStyleBackColor = false;
			this->casesbtn->Click += gcnew System::EventHandler(this, &Main::casesbtn_Click);
			// 
			// firbtn
			// 
			this->firbtn->AutoSize = true;
			this->firbtn->BackColor = System::Drawing::Color::Transparent;
			this->firbtn->FlatAppearance->BorderSize = 0;
			this->firbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->firbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->firbtn->ForeColor = System::Drawing::Color::Transparent;
			this->firbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->firbtn->Location = System::Drawing::Point(179, 343);
			this->firbtn->Name = L"firbtn";
			this->firbtn->Size = System::Drawing::Size(218, 46);
			this->firbtn->TabIndex = 13;
			this->firbtn->Text = L"5. FIR";
			this->firbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->firbtn->UseVisualStyleBackColor = false;
			this->firbtn->Click += gcnew System::EventHandler(this, &Main::firbtn_Click);
			// 
			// officersbtn
			// 
			this->officersbtn->AutoSize = true;
			this->officersbtn->BackColor = System::Drawing::Color::Transparent;
			this->officersbtn->FlatAppearance->BorderSize = 0;
			this->officersbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->officersbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->officersbtn->ForeColor = System::Drawing::Color::Transparent;
			this->officersbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->officersbtn->Location = System::Drawing::Point(179, 413);
			this->officersbtn->Name = L"officersbtn";
			this->officersbtn->Size = System::Drawing::Size(218, 46);
			this->officersbtn->TabIndex = 13;
			this->officersbtn->Text = L"6. Officers";
			this->officersbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->officersbtn->UseVisualStyleBackColor = false;
			this->officersbtn->Click += gcnew System::EventHandler(this, &Main::officersbtn_Click);
			// 
			// evidencebtn
			// 
			this->evidencebtn->AutoSize = true;
			this->evidencebtn->BackColor = System::Drawing::Color::Transparent;
			this->evidencebtn->FlatAppearance->BorderSize = 0;
			this->evidencebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->evidencebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->evidencebtn->ForeColor = System::Drawing::Color::Transparent;
			this->evidencebtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->evidencebtn->Location = System::Drawing::Point(179, 483);
			this->evidencebtn->Name = L"evidencebtn";
			this->evidencebtn->Size = System::Drawing::Size(218, 46);
			this->evidencebtn->TabIndex = 13;
			this->evidencebtn->Text = L"7. Evidence";
			this->evidencebtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->evidencebtn->UseVisualStyleBackColor = false;
			this->evidencebtn->Click += gcnew System::EventHandler(this, &Main::evidencebtn_Click);
			// 
			// forensicbtn
			// 
			this->forensicbtn->AutoSize = true;
			this->forensicbtn->BackColor = System::Drawing::Color::Transparent;
			this->forensicbtn->FlatAppearance->BorderSize = 0;
			this->forensicbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->forensicbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->forensicbtn->ForeColor = System::Drawing::Color::Transparent;
			this->forensicbtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->forensicbtn->Location = System::Drawing::Point(179, 553);
			this->forensicbtn->Name = L"forensicbtn";
			this->forensicbtn->Size = System::Drawing::Size(259, 46);
			this->forensicbtn->TabIndex = 13;
			this->forensicbtn->Text = L"8. Forensic Analysis";
			this->forensicbtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->forensicbtn->UseVisualStyleBackColor = false;
			this->forensicbtn->Click += gcnew System::EventHandler(this, &Main::forensicbtn_Click);
			// 
			// logouticon
			// 
			this->logouticon->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->logouticon->ForeColor = System::Drawing::Color::White;
			this->logouticon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logouticon.Image")));
			this->logouticon->Location = System::Drawing::Point(1049, 0);
			this->logouticon->Name = L"logouticon";
			this->logouticon->Size = System::Drawing::Size(34, 36);
			this->logouticon->TabIndex = 14;
			// 
			// db_btn
			// 
			this->db_btn->AutoSize = true;
			this->db_btn->BackColor = System::Drawing::Color::White;
			this->db_btn->FlatAppearance->BorderSize = 2;
			this->db_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->db_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->db_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->db_btn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->db_btn->Location = System::Drawing::Point(24, 298);
			this->db_btn->Name = L"db_btn";
			this->db_btn->Size = System::Drawing::Size(189, 54);
			this->db_btn->TabIndex = 13;
			this->db_btn->Text = L"Connect to Database";
			this->db_btn->UseVisualStyleBackColor = false;
			this->db_btn->Click += gcnew System::EventHandler(this, &Main::db_btn_Click);
			// 
			// db_label
			// 
			this->db_label->AutoSize = true;
			this->db_label->BackColor = System::Drawing::Color::Silver;
			this->db_label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->db_label->ForeColor = System::Drawing::Color::DarkRed;
			this->db_label->Location = System::Drawing::Point(343, 314);
			this->db_label->Name = L"db_label";
			this->db_label->Size = System::Drawing::Size(132, 25);
			this->db_label->TabIndex = 21;
			this->db_label->Text = L"Not Connected";
			// 
			// dbPnlBtn
			// 
			this->dbPnlBtn->AutoSize = true;
			this->dbPnlBtn->BackColor = System::Drawing::Color::White;
			this->dbPnlBtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->dbPnlBtn->FlatAppearance->BorderSize = 2;
			this->dbPnlBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->dbPnlBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dbPnlBtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->dbPnlBtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->dbPnlBtn->Location = System::Drawing::Point(957, 113);
			this->dbPnlBtn->Name = L"dbPnlBtn";
			this->dbPnlBtn->Size = System::Drawing::Size(191, 42);
			this->dbPnlBtn->TabIndex = 13;
			this->dbPnlBtn->Text = L"Storage Options";
			this->dbPnlBtn->UseVisualStyleBackColor = false;
			this->dbPnlBtn->Click += gcnew System::EventHandler(this, &Main::dbPnlBtn_Click);
			// 
			// dbPanel
			// 
			this->dbPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->dbPanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"dbPanel.BackgroundImage")));
			this->dbPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->dbPanel->Controls->Add(this->passwordLbl);
			this->dbPanel->Controls->Add(this->usernamelbl);
			this->dbPanel->Controls->Add(this->dbPsBox);
			this->dbPanel->Controls->Add(this->dbUsrNameTxtBox);
			this->dbPanel->Controls->Add(this->dbPnlHelpBtn);
			this->dbPanel->Controls->Add(this->dbPnlClose);
			this->dbPanel->Controls->Add(this->csvCheck);
			this->dbPanel->Controls->Add(this->label1);
			this->dbPanel->Controls->Add(this->db_btn);
			this->dbPanel->Controls->Add(this->db_label);
			this->dbPanel->Location = System::Drawing::Point(655, 161);
			this->dbPanel->Name = L"dbPanel";
			this->dbPanel->Size = System::Drawing::Size(493, 438);
			this->dbPanel->TabIndex = 22;
			// 
			// passwordLbl
			// 
			this->passwordLbl->AutoSize = true;
			this->passwordLbl->BackColor = System::Drawing::Color::Transparent;
			this->passwordLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->passwordLbl->ForeColor = System::Drawing::Color::White;
			this->passwordLbl->Location = System::Drawing::Point(25, 225);
			this->passwordLbl->Name = L"passwordLbl";
			this->passwordLbl->Size = System::Drawing::Size(149, 21);
			this->passwordLbl->TabIndex = 26;
			this->passwordLbl->Text = L"MySQL\'s Password :";
			// 
			// usernamelbl
			// 
			this->usernamelbl->AutoSize = true;
			this->usernamelbl->BackColor = System::Drawing::Color::Transparent;
			this->usernamelbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->usernamelbl->ForeColor = System::Drawing::Color::White;
			this->usernamelbl->Location = System::Drawing::Point(20, 170);
			this->usernamelbl->Name = L"usernamelbl";
			this->usernamelbl->Size = System::Drawing::Size(154, 21);
			this->usernamelbl->TabIndex = 26;
			this->usernamelbl->Text = L"MySQL\'s Username :";
			// 
			// dbPsBox
			// 
			this->dbPsBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dbPsBox->ForeColor = System::Drawing::Color::Black;
			this->dbPsBox->Location = System::Drawing::Point(186, 225);
			this->dbPsBox->Name = L"dbPsBox";
			this->dbPsBox->Size = System::Drawing::Size(141, 29);
			this->dbPsBox->TabIndex = 25;
			this->dbPsBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Main::dbPsBox_KeyPress);
			// 
			// dbUsrNameTxtBox
			// 
			this->dbUsrNameTxtBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dbUsrNameTxtBox->ForeColor = System::Drawing::Color::Black;
			this->dbUsrNameTxtBox->Location = System::Drawing::Point(186, 167);
			this->dbUsrNameTxtBox->Name = L"dbUsrNameTxtBox";
			this->dbUsrNameTxtBox->Size = System::Drawing::Size(141, 29);
			this->dbUsrNameTxtBox->TabIndex = 25;
			this->dbUsrNameTxtBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Main::dbUsrNameTxtBox_KeyPress);
			// 
			// dbPnlHelpBtn
			// 
			this->dbPnlHelpBtn->BackColor = System::Drawing::Color::Gray;
			this->dbPnlHelpBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->dbPnlHelpBtn->Location = System::Drawing::Point(415, 3);
			this->dbPnlHelpBtn->Name = L"dbPnlHelpBtn";
			this->dbPnlHelpBtn->Size = System::Drawing::Size(75, 23);
			this->dbPnlHelpBtn->TabIndex = 24;
			this->dbPnlHelpBtn->Text = L"Help";
			this->dbPnlHelpBtn->UseVisualStyleBackColor = false;
			this->dbPnlHelpBtn->Click += gcnew System::EventHandler(this, &Main::dbPnlHelpBtn_Click);
			// 
			// dbPnlClose
			// 
			this->dbPnlClose->BackColor = System::Drawing::Color::Gray;
			this->dbPnlClose->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->dbPnlClose->Location = System::Drawing::Point(415, 412);
			this->dbPnlClose->Name = L"dbPnlClose";
			this->dbPnlClose->Size = System::Drawing::Size(75, 23);
			this->dbPnlClose->TabIndex = 24;
			this->dbPnlClose->Text = L"Close";
			this->dbPnlClose->UseVisualStyleBackColor = false;
			this->dbPnlClose->Click += gcnew System::EventHandler(this, &Main::dbPnlClose_Click);
			// 
			// csvCheck
			// 
			this->csvCheck->AutoSize = true;
			this->csvCheck->BackColor = System::Drawing::Color::Transparent;
			this->csvCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 17, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->csvCheck->ForeColor = System::Drawing::Color::Silver;
			this->csvCheck->Location = System::Drawing::Point(13, 70);
			this->csvCheck->Name = L"csvCheck";
			this->csvCheck->Size = System::Drawing::Size(242, 35);
			this->csvCheck->TabIndex = 23;
			this->csvCheck->Text = L"Use CSV File Storage";
			this->csvCheck->UseVisualStyleBackColor = false;
			this->csvCheck->CheckedChanged += gcnew System::EventHandler(this, &Main::csvCheck_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(147, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(221, 30);
			this->label1->TabIndex = 22;
			this->label1->Text = L"DataBase & Storage";
			this->label1->UseMnemonic = false;
			// 
			// notiLabel
			// 
			this->notiLabel->AutoSize = true;
			this->notiLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->notiLabel->ForeColor = System::Drawing::Color::White;
			this->notiLabel->Location = System::Drawing::Point(3, 11);
			this->notiLabel->Name = L"notiLabel";
			this->notiLabel->Size = System::Drawing::Size(94, 17);
			this->notiLabel->TabIndex = 0;
			this->notiLabel->Text = L"Notifications";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(3, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(99, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"-----------------------";
			// 
			// notipanel
			// 
			this->notipanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->notipanel->Controls->Add(this->label3);
			this->notipanel->Controls->Add(this->notiPnlBtn1);
			this->notipanel->Controls->Add(this->notiLabel);
			this->notipanel->Controls->Add(this->label2);
			this->notipanel->Location = System::Drawing::Point(0, 175);
			this->notipanel->Name = L"notipanel";
			this->notipanel->Size = System::Drawing::Size(173, 424);
			this->notipanel->TabIndex = 12;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(20, 182);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(138, 13);
			this->label3->TabIndex = 26;
			this->label3->Text = L"No notifications available";
			// 
			// notiPnlBtn1
			// 
			this->notiPnlBtn1->BackColor = System::Drawing::Color::DimGray;
			this->notiPnlBtn1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->notiPnlBtn1->Location = System::Drawing::Point(95, 396);
			this->notiPnlBtn1->Name = L"notiPnlBtn1";
			this->notiPnlBtn1->Size = System::Drawing::Size(75, 23);
			this->notiPnlBtn1->TabIndex = 25;
			this->notiPnlBtn1->Text = L"Close";
			this->notiPnlBtn1->UseVisualStyleBackColor = false;
			this->notiPnlBtn1->Click += gcnew System::EventHandler(this, &Main::notiPnlBtn1_Click);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1188, 634);
			this->Controls->Add(this->dbPanel);
			this->Controls->Add(this->notipanel);
			this->Controls->Add(this->logouticon);
			this->Controls->Add(this->forensicbtn);
			this->Controls->Add(this->evidencebtn);
			this->Controls->Add(this->officersbtn);
			this->Controls->Add(this->firbtn);
			this->Controls->Add(this->casesbtn);
			this->Controls->Add(this->weaponsbtn);
			this->Controls->Add(this->criminalbtn);
			this->Controls->Add(this->dbPnlBtn);
			this->Controls->Add(this->crimedetailsbtn);
			this->Controls->Add(this->notificationbell);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseUp);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->dbPanel->ResumeLayout(false);
			this->dbPanel->PerformLayout();
			this->notipanel->ResumeLayout(false);
			this->notipanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void notificationbell_Click(System::Object^ sender, System::EventArgs^ e) {
	if (notipanel->Visible)
	{
		notipanel->Hide();
	}
	else
	{
		notipanel->Show(); 
	}
}
private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit(); 
}
private: System::Void logoutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Restart();
}
private: System::Void crimedetailsbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	CrimeDetails^ crimedetails = gcnew CrimeDetails(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	crimedetails->Show(); 
}


private: System::Void criminalbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Criminals^ criminals = gcnew Criminals(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	criminals->Show();
}



private: System::Void db_btn_Click(System::Object^ sender, System::EventArgs^ e) {

	MYSQL* connection = connecting(dbUsrNameTxtBox->Text, dbPsBox->Text); 
	
	if (connection)
	{
		db_label->Text = "Connected"; 
		db_label->ForeColor = System::Drawing::Color::Lime; 
		isDbEnabled = true; 
		MessageBox::Show("Connected to MYSQL SERVER 8.0", "Database Connection", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		db_label->Text = "Not Connected";
		MessageBox::Show("Incorrect Credentials", "Database Connection", MessageBoxButtons::OK, MessageBoxIcon::Error); 
	}
}

	   bool dragging; 
	   Point offset; 
private: System::Void Main_Load(System::Object^ sender, System::EventArgs^ e) {
	dragging = false; 

}

private: System::Void dbPnlBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	dbPanel->Show();
	dbUsrNameTxtBox->Focus(); 
}

private: System::Void dbPnlClose_Click(System::Object^ sender, System::EventArgs^ e) {
	dbPanel->Hide();
}

private: System::Void csvCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (csvCheck->Checked==true)
	{
		db_btn->Enabled = false;
		isDbEnabled = false;
	}
	else
	{
		db_btn->Enabled = true;
		isDbEnabled = true;
	}
}


private: System::Void weaponsbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Weapons^ weapons = gcnew Weapons(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	weapons->Show();
}


private: System::Void dbPnlHelpBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("If you have installed MySql 8.0 on your system then enter your credentials. Otherwise use store your data in CSV file format ", "Help", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void forensicbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Forensics^ forensics = gcnew Forensics(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	forensics->Show();
}
private: System::Void firbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	FIR^ fir = gcnew FIR(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	fir->Show();
}


private: System::Void notiPnlBtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	notipanel->Hide(); 
}
private: System::Void dbUsrNameTxtBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {

	if (e->KeyChar == int(Keys::Enter))
	{
		dbPsBox->Focus(); 
	}
}
private: System::Void dbPsBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == int(Keys::Enter))
	{
		db_btn->PerformClick(); 
	}
}
private: System::Void Main_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	dragging = true; 
	offset = Point(e->X, e->Y); 
}
private: System::Void Main_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (dragging)
	{
		Point currentScreenPos = PointToScreen(e->Location); 
		Location = Point(currentScreenPos.X - offset.X, currentScreenPos.Y - offset.Y); 
	}
}
private: System::Void Main_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	dragging = false; 
}
private: System::Void casesbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Cases^ casesobj = gcnew Cases(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	casesobj->Show(); 
}

private: System::Void evidencebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Evidences^ evidence = gcnew Evidences(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	evidence->Show(); 

}
private: System::Void officersbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Officers^ officer = gcnew Officers(connecting(dbUsrNameTxtBox->Text, dbPsBox->Text), isDbEnabled);
	officer->Show(); 
	
}
};
}
