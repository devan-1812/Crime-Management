#pragma once
#include<sstream>
#include<iostream>
#include<string>
#include<fstream>
#include<msclr/marshal_cppstd.h>
#include<mysql.h>

namespace CMS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for Cases
	/// </summary>
	public ref class Cases : public System::Windows::Forms::Form
	{
	private:
		MYSQL* currentconn;
		bool isDbEnabled;
	private: System::Windows::Forms::Panel^ viewpanel;
	public:
	private: System::Windows::Forms::Panel^ resultpnl;
	private: System::Windows::Forms::TextBox^ descbox2;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ defendbox2;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ datebox2;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ officerbox2;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ viewheading;
	private: System::Windows::Forms::Button^ resetbtn;
	private: System::Windows::Forms::Button^ searchbtn;
	private: System::Windows::Forms::TextBox^ caseBox2;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Button^ closebtn;
	private: System::Windows::Forms::TextBox^ prosbox2;

	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Panel^ removepanel;
	private: System::Windows::Forms::Button^ closebutton;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Button^ removebtn3;
	private: System::Windows::Forms::TextBox^ caseBox3;
	private: System::Windows::Forms::Label^ fir_lbl;
	bool textchange = false;
	public:
		Cases(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			addpanel->Hide();
			viewpanel->Hide();
			resultpnl->Hide();
			removepanel->Hide();
		}
		Cases(MYSQL*db, bool isconn)
		{
			InitializeComponent();
			addpanel->Hide();
			viewpanel->Hide();
			resultpnl->Hide();
			removepanel->Hide();
			currentconn = db;
			isDbEnabled = isconn;

			if (isDbEnabled)
			{
				datalabel->ForeColor = System::Drawing::Color::LawnGreen;
				label1->ForeColor = System::Drawing::Color::Red;
			}
			else
			{
				datalabel->ForeColor = System::Drawing::Color::Red;
				label1->ForeColor = System::Drawing::Color::LawnGreen;
			}
		}

		bool case_nocheck(int case_no)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			stringstream ss;
			ss << "select Case_no from cms.cases where Case_no = " << case_no;
			string c1 = ss.str();
			char* arrayqueue;
			arrayqueue = &c1[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}

		}

		void addCaseDB(int caseNo, int Officerid, String^ date, String^ defence, String^ pros, String^ desc)
		{
			msclr::interop::marshal_context converter;
			string Date, Defence, Pros, Desc;


			Date = converter.marshal_as<string>(datebox1->Text); 
			Defence = converter.marshal_as<string>(defendbox1->Text);
			Pros = converter.marshal_as<string>(prosbox1->Text);
			Desc = converter.marshal_as<string>(descBox1->Text);

			stringstream ss;
			ss << "insert into cms.cases (Case_no, Officer_Id, Date, Defence, Prosecutor, Description ) values (" << caseNo << "," << Officerid << ",'" << Date << "','" << Defence << "', '" << Pros << "', '" << Desc << "')";
			string query = ss.str();
			char* arrayquery;
			arrayquery = &query[0];

			if (mysql_query(currentconn, arrayquery))
			{
				MessageBox::Show("Error");
			}
			else
			{
				MessageBox::Show("Successfully Connected");
			}
		}

		void addCaseCSV(int caseNo, int Officerid, String^ date, String^ defence, String^ pros, String^ desc)
		{
			fstream file1;
			msclr::interop::marshal_context converter;
			string Date, Defence, Pros, Desc;
			Date = converter.marshal_as<string>(datebox1->Text);
			Defence = converter.marshal_as<string>(defendbox1->Text);
			Pros = converter.marshal_as<string>(prosbox1->Text);
			Desc = converter.marshal_as<string>(descBox1->Text);

			file1.open("Cases.csv", ios::out | ios::app);
			file1 << caseNo << "," << Officerid << "," << Date << "," << Defence << "," << Pros << "," << Desc << endl;
			file1.close();
		}

		void viewCaseDB(int caseNo)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			string officer_id, date, defence, pros, desc;
			String^ ID, ^ Date, ^ Defence, ^ Pros, ^ Desc;

			stringstream ss;
			ss << "select * from cms.cases where Case_no = " << caseNo;
			string query = ss.str();
			char* arrayqueue;
			arrayqueue = &query[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);

				if (row == NULL)
				{
					MessageBox::Show("No Record Exists with this Case Number", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);

				}
				else
				{
					resultpnl->Show();
					officer_id = row[1];
					date = row[2];
					defence = row[3];
					pros = row[4];
					desc = row[5];

					ID = gcnew String(officer_id.c_str());
					Date = gcnew String(date.c_str());
					Defence = gcnew String(defence.c_str());
					Pros = gcnew String(pros.c_str());
					Desc = gcnew String(desc.c_str());

					officerbox2->Text = ID;
					datebox2->Text = Date;
					defendbox2->Text = Defence;
					prosbox2->Text = Pros;
					descbox2->Text = Desc;

				}
			}
			else
			{
				MessageBox::Show("Error");

			}
		}

		void viewCaseCSV(int caseNo)
		{
			int caseNo2;
			fstream file1;
			file1.open("Cases.csv", ios::in);

			while (file1.good())
			{
				string line, word;
				getline(file1, word);
				stringstream ss(line);
				getline(ss, word, ',');
				try
				{
					caseNo2 = stoi(word);
				}
				catch (...)
				{
					MessageBox::Show("No Case with this Case Number exists ", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				if (caseNo == caseNo2)
				{
					resultpnl->Show();
					string officer_id, date,day, defence, pros, desc;
					getline(ss, officer_id, ',');
					getline(ss, date, ',');
					getline(ss, day, ',');
					getline(ss, defence, ',');
					getline(ss, pros, ',');
					getline(ss, desc, ',');

					string finaldate = date + day;

					String^ ID, ^ Date, ^ Defence, ^ Pros, ^ Desc;
					ID = gcnew String(officer_id.c_str());
					Date = gcnew String(finaldate.c_str());
					Defence = gcnew String(defence.c_str());
					Pros = gcnew String(pros.c_str());
					Desc = gcnew String(desc.c_str());

					officerbox2->Text = ID;
					datebox2->Text = Date;
					defendbox2->Text = Defence;
					prosbox2->Text = Pros;
					descbox2->Text = Desc;
					break;
				}
				else
				{
					continue;
				}
			}
			file1.close();
		}

		void removeCaseDB(int caseNo)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss, delquery;
			char* arrayqueue;

			ss << "select * from cms.cases where Case_no = " << caseNo;
			std::string query = ss.str();
			arrayqueue = &query[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);

				if (row == NULL)
				{
					MessageBox::Show("No Case Exists with this case number", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					delquery << "delete from cms.cases where Case_no = " << caseNo;
					std::string c2 = delquery.str();
					char* delarrayqueue;
					delarrayqueue = &c2[0];
					mysql_query(currentconn, delarrayqueue);
					mysql_commit(currentconn);
					MessageBox::Show("Case Deleted Successfully", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}

		void removeCaseCSV(int caseNo)
		{
			fstream file1, file2;
			file1.open("Cases.csv", ios::in);
			file2.open("CasesNew.csv", ios::out);
			int caseNo2 = NULL; bool caseFound = false;

			while (file1.good())
			{
				std::string line, word;
				std::getline(file1, line);
				std::stringstream ss(line);
				std::getline(ss, word, ',');
				try
				{
					caseNo2 = std::stoi(word);
				}
				catch (...)
				{
					break;
				}
				if (caseNo == caseNo2)
				{
					caseFound = true;
					continue;
				}
				else
				{
					string officer_id, date, day, defence, pros, desc;
					getline(ss, officer_id, ',');
					getline(ss, date, ',');
					getline(ss, day, ',');
					getline(ss, defence, ',');
					getline(ss, pros, ',');
					getline(ss, desc, ',');

					file2 << caseNo2 << "," << officer_id << "," << date << "," << day << "," << defence << "," << pros << "," << desc << endl;
					break;
				}
				if (caseFound == true)
				{
					MessageBox::Show("Case Successfully Deleted", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
				{
					MessageBox::Show("No case exists with this case number.", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				file1.close();
				file2.close();

				remove("Cases.csv");
				rename("CasesNew.csv", "Cases.csv");

			}
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Cases()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ heading;
	private: System::Windows::Forms::Panel^ bottonPnl;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ datalabel;
	private: System::Windows::Forms::Button^ removebtn;
	private: System::Windows::Forms::Button^ viewbtn;
	private: System::Windows::Forms::Button^ addbtn;
	private: System::Windows::Forms::Button^ dbinfo;
	private: System::Windows::Forms::Button^ abt_Btn;
	private: System::Windows::Forms::Button^ Exitbtn;
	private: System::Windows::Forms::Panel^ addpanel;
	private: System::Windows::Forms::TextBox^ defendbox1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ prosbox1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ officerbox1;
	private: System::Windows::Forms::Button^ resetbtn1;
	private: System::Windows::Forms::Button^ closebtn1;
	private: System::Windows::Forms::Button^ savebtn;
	private: System::Windows::Forms::TextBox^ descBox1;
	private: System::Windows::Forms::DateTimePicker^ datebox1;
	private: System::Windows::Forms::TextBox^ caseBox1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Cases::typeid));
			this->heading = (gcnew System::Windows::Forms::Label());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->removebtn = (gcnew System::Windows::Forms::Button());
			this->viewbtn = (gcnew System::Windows::Forms::Button());
			this->addbtn = (gcnew System::Windows::Forms::Button());
			this->dbinfo = (gcnew System::Windows::Forms::Button());
			this->abt_Btn = (gcnew System::Windows::Forms::Button());
			this->Exitbtn = (gcnew System::Windows::Forms::Button());
			this->addpanel = (gcnew System::Windows::Forms::Panel());
			this->defendbox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->prosbox1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->officerbox1 = (gcnew System::Windows::Forms::TextBox());
			this->resetbtn1 = (gcnew System::Windows::Forms::Button());
			this->closebtn1 = (gcnew System::Windows::Forms::Button());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->descBox1 = (gcnew System::Windows::Forms::TextBox());
			this->datebox1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->caseBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->viewpanel = (gcnew System::Windows::Forms::Panel());
			this->resultpnl = (gcnew System::Windows::Forms::Panel());
			this->prosbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->descbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->defendbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->datebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->officerbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->resetbtn = (gcnew System::Windows::Forms::Button());
			this->searchbtn = (gcnew System::Windows::Forms::Button());
			this->caseBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->closebtn = (gcnew System::Windows::Forms::Button());
			this->removepanel = (gcnew System::Windows::Forms::Panel());
			this->closebutton = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->removebtn3 = (gcnew System::Windows::Forms::Button());
			this->caseBox3 = (gcnew System::Windows::Forms::TextBox());
			this->fir_lbl = (gcnew System::Windows::Forms::Label());
			this->bottonPnl->SuspendLayout();
			this->addpanel->SuspendLayout();
			this->viewpanel->SuspendLayout();
			this->resultpnl->SuspendLayout();
			this->removepanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// heading
			// 
			this->heading->AutoSize = true;
			this->heading->BackColor = System::Drawing::Color::Transparent;
			this->heading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->heading->ForeColor = System::Drawing::Color::White;
			this->heading->Location = System::Drawing::Point(354, 26);
			this->heading->Name = L"heading";
			this->heading->Size = System::Drawing::Size(136, 59);
			this->heading->TabIndex = 9;
			this->heading->Text = L"Cases";
			// 
			// bottonPnl
			// 
			this->bottonPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->bottonPnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->bottonPnl->Controls->Add(this->label1);
			this->bottonPnl->Controls->Add(this->datalabel);
			this->bottonPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottonPnl->Location = System::Drawing::Point(0, 543);
			this->bottonPnl->Name = L"bottonPnl";
			this->bottonPnl->Size = System::Drawing::Size(861, 27);
			this->bottonPnl->TabIndex = 10;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(1, 4);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(159, 19);
			this->label1->TabIndex = 5;
			this->label1->Text = L"WINDOWS FILE SYSTEM";
			// 
			// datalabel
			// 
			this->datalabel->AutoSize = true;
			this->datalabel->BackColor = System::Drawing::Color::Transparent;
			this->datalabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datalabel->ForeColor = System::Drawing::Color::White;
			this->datalabel->Location = System::Drawing::Point(792, 4);
			this->datalabel->Name = L"datalabel";
			this->datalabel->Size = System::Drawing::Size(55, 19);
			this->datalabel->TabIndex = 5;
			this->datalabel->Text = L"MYSQL";
			// 
			// removebtn
			// 
			this->removebtn->BackColor = System::Drawing::Color::DarkGray;
			this->removebtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->removebtn->FlatAppearance->BorderSize = 0;
			this->removebtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->removebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->removebtn->ForeColor = System::Drawing::Color::Black;
			this->removebtn->Location = System::Drawing::Point(69, 356);
			this->removebtn->Name = L"removebtn";
			this->removebtn->Size = System::Drawing::Size(166, 39);
			this->removebtn->TabIndex = 12;
			this->removebtn->Text = L"Remove Case";
			this->removebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->removebtn->UseVisualStyleBackColor = false;
			this->removebtn->Click += gcnew System::EventHandler(this, &Cases::removebtn_Click);
			// 
			// viewbtn
			// 
			this->viewbtn->BackColor = System::Drawing::Color::DarkGray;
			this->viewbtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->viewbtn->FlatAppearance->BorderSize = 0;
			this->viewbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->viewbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewbtn->ForeColor = System::Drawing::Color::Black;
			this->viewbtn->Location = System::Drawing::Point(69, 251);
			this->viewbtn->Name = L"viewbtn";
			this->viewbtn->Size = System::Drawing::Size(166, 39);
			this->viewbtn->TabIndex = 13;
			this->viewbtn->Text = L"View Case";
			this->viewbtn->UseVisualStyleBackColor = false;
			this->viewbtn->Click += gcnew System::EventHandler(this, &Cases::viewbtn_Click);
			// 
			// addbtn
			// 
			this->addbtn->BackColor = System::Drawing::Color::DarkGray;
			this->addbtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->addbtn->FlatAppearance->BorderSize = 0;
			this->addbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->addbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addbtn->ForeColor = System::Drawing::Color::Black;
			this->addbtn->Location = System::Drawing::Point(69, 156);
			this->addbtn->Name = L"addbtn";
			this->addbtn->Size = System::Drawing::Size(166, 39);
			this->addbtn->TabIndex = 14;
			this->addbtn->Text = L"Add Case";
			this->addbtn->UseVisualStyleBackColor = false;
			this->addbtn->Click += gcnew System::EventHandler(this, &Cases::addbtn_Click);
			// 
			// dbinfo
			// 
			this->dbinfo->BackColor = System::Drawing::Color::DarkGray;
			this->dbinfo->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->dbinfo->FlatAppearance->BorderSize = 0;
			this->dbinfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->dbinfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dbinfo->Location = System::Drawing::Point(595, 251);
			this->dbinfo->Name = L"dbinfo";
			this->dbinfo->Size = System::Drawing::Size(166, 39);
			this->dbinfo->TabIndex = 15;
			this->dbinfo->Text = L"Database Info";
			this->dbinfo->UseVisualStyleBackColor = false;
			this->dbinfo->Click += gcnew System::EventHandler(this, &Cases::dbinfo_Click);
			// 
			// abt_Btn
			// 
			this->abt_Btn->BackColor = System::Drawing::Color::DarkGray;
			this->abt_Btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->abt_Btn->FlatAppearance->BorderSize = 0;
			this->abt_Btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->abt_Btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->abt_Btn->Location = System::Drawing::Point(595, 156);
			this->abt_Btn->Name = L"abt_Btn";
			this->abt_Btn->Size = System::Drawing::Size(166, 39);
			this->abt_Btn->TabIndex = 16;
			this->abt_Btn->Text = L"About";
			this->abt_Btn->UseVisualStyleBackColor = false;
			this->abt_Btn->Click += gcnew System::EventHandler(this, &Cases::abt_Btn_Click);
			// 
			// Exitbtn
			// 
			this->Exitbtn->BackColor = System::Drawing::Color::DarkGray;
			this->Exitbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->Exitbtn->FlatAppearance->BorderSize = 0;
			this->Exitbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->Exitbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Exitbtn->Location = System::Drawing::Point(595, 356);
			this->Exitbtn->Name = L"Exitbtn";
			this->Exitbtn->Size = System::Drawing::Size(166, 39);
			this->Exitbtn->TabIndex = 17;
			this->Exitbtn->Text = L"Exit";
			this->Exitbtn->UseVisualStyleBackColor = false;
			this->Exitbtn->Click += gcnew System::EventHandler(this, &Cases::Exitbtn_Click);
			// 
			// addpanel
			// 
			this->addpanel->BackColor = System::Drawing::Color::Silver;
			this->addpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addpanel.BackgroundImage")));
			this->addpanel->Controls->Add(this->defendbox1);
			this->addpanel->Controls->Add(this->label7);
			this->addpanel->Controls->Add(this->prosbox1);
			this->addpanel->Controls->Add(this->label5);
			this->addpanel->Controls->Add(this->officerbox1);
			this->addpanel->Controls->Add(this->resetbtn1);
			this->addpanel->Controls->Add(this->closebtn1);
			this->addpanel->Controls->Add(this->savebtn);
			this->addpanel->Controls->Add(this->descBox1);
			this->addpanel->Controls->Add(this->datebox1);
			this->addpanel->Controls->Add(this->caseBox1);
			this->addpanel->Controls->Add(this->label6);
			this->addpanel->Controls->Add(this->label4);
			this->addpanel->Controls->Add(this->label3);
			this->addpanel->Controls->Add(this->label2);
			this->addpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->addpanel->Location = System::Drawing::Point(0, 0);
			this->addpanel->Name = L"addpanel";
			this->addpanel->Size = System::Drawing::Size(861, 543);
			this->addpanel->TabIndex = 18;
			// 
			// defendbox1
			// 
			this->defendbox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->defendbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->defendbox1->Location = System::Drawing::Point(279, 218);
			this->defendbox1->Multiline = true;
			this->defendbox1->Name = L"defendbox1";
			this->defendbox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->defendbox1->Size = System::Drawing::Size(146, 31);
			this->defendbox1->TabIndex = 12;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(47, 225);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(142, 24);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Defended By :";
			// 
			// prosbox1
			// 
			this->prosbox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->prosbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->prosbox1->Location = System::Drawing::Point(279, 272);
			this->prosbox1->Multiline = true;
			this->prosbox1->Name = L"prosbox1";
			this->prosbox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->prosbox1->Size = System::Drawing::Size(146, 31);
			this->prosbox1->TabIndex = 10;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(47, 280);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(157, 24);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Prosecuted By :";
			// 
			// officerbox1
			// 
			this->officerbox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->officerbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->officerbox1->Location = System::Drawing::Point(279, 115);
			this->officerbox1->Multiline = true;
			this->officerbox1->Name = L"officerbox1";
			this->officerbox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->officerbox1->Size = System::Drawing::Size(146, 31);
			this->officerbox1->TabIndex = 8;
			// 
			// resetbtn1
			// 
			this->resetbtn1->BackColor = System::Drawing::Color::White;
			this->resetbtn1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn1->FlatAppearance->BorderSize = 2;
			this->resetbtn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetbtn1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn1->Location = System::Drawing::Point(707, 207);
			this->resetbtn1->Name = L"resetbtn1";
			this->resetbtn1->Size = System::Drawing::Size(118, 58);
			this->resetbtn1->TabIndex = 7;
			this->resetbtn1->Text = L"Reset";
			this->resetbtn1->UseVisualStyleBackColor = false;
			this->resetbtn1->Click += gcnew System::EventHandler(this, &Cases::resetbtn1_Click);
			// 
			// closebtn1
			// 
			this->closebtn1->BackColor = System::Drawing::Color::White;
			this->closebtn1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closebtn1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn1->FlatAppearance->BorderSize = 2;
			this->closebtn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closebtn1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closebtn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn1->Location = System::Drawing::Point(707, 117);
			this->closebtn1->Name = L"closebtn1";
			this->closebtn1->Size = System::Drawing::Size(118, 58);
			this->closebtn1->TabIndex = 7;
			this->closebtn1->Text = L"Close";
			this->closebtn1->UseVisualStyleBackColor = false;
			this->closebtn1->Click += gcnew System::EventHandler(this, &Cases::closebtn1_Click);
			// 
			// savebtn
			// 
			this->savebtn->BackColor = System::Drawing::Color::White;
			this->savebtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->savebtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->savebtn->FlatAppearance->BorderSize = 2;
			this->savebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->savebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->savebtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->savebtn->Location = System::Drawing::Point(707, 36);
			this->savebtn->Name = L"savebtn";
			this->savebtn->Size = System::Drawing::Size(118, 58);
			this->savebtn->TabIndex = 7;
			this->savebtn->Text = L"Save";
			this->savebtn->UseVisualStyleBackColor = false;
			this->savebtn->Click += gcnew System::EventHandler(this, &Cases::savebtn_Click);
			// 
			// descBox1
			// 
			this->descBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descBox1->Location = System::Drawing::Point(119, 385);
			this->descBox1->Multiline = true;
			this->descBox1->Name = L"descBox1";
			this->descBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descBox1->Size = System::Drawing::Size(598, 134);
			this->descBox1->TabIndex = 6;
			// 
			// datebox1
			// 
			this->datebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox1->Location = System::Drawing::Point(279, 170);
			this->datebox1->Name = L"datebox1";
			this->datebox1->Size = System::Drawing::Size(211, 25);
			this->datebox1->TabIndex = 5;
			// 
			// caseBox1
			// 
			this->caseBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->caseBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->caseBox1->Location = System::Drawing::Point(279, 60);
			this->caseBox1->Multiline = true;
			this->caseBox1->Name = L"caseBox1";
			this->caseBox1->Size = System::Drawing::Size(146, 31);
			this->caseBox1->TabIndex = 1;
			this->caseBox1->TextChanged += gcnew System::EventHandler(this, &Cases::caseBox1_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(47, 335);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(305, 24);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Enter Case Description Below : ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(47, 170);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(122, 24);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Filing Date :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(47, 117);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(159, 24);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Filed By Officer:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(47, 64);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(96, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Case No.";
			// 
			// viewpanel
			// 
			this->viewpanel->BackColor = System::Drawing::Color::Silver;
			this->viewpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"viewpanel.BackgroundImage")));
			this->viewpanel->Controls->Add(this->resultpnl);
			this->viewpanel->Controls->Add(this->viewheading);
			this->viewpanel->Controls->Add(this->resetbtn);
			this->viewpanel->Controls->Add(this->searchbtn);
			this->viewpanel->Controls->Add(this->caseBox2);
			this->viewpanel->Controls->Add(this->label12);
			this->viewpanel->Controls->Add(this->closebtn);
			this->viewpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->viewpanel->Location = System::Drawing::Point(0, 0);
			this->viewpanel->Name = L"viewpanel";
			this->viewpanel->Size = System::Drawing::Size(861, 543);
			this->viewpanel->TabIndex = 19;
			// 
			// resultpnl
			// 
			this->resultpnl->BackColor = System::Drawing::Color::Transparent;
			this->resultpnl->Controls->Add(this->prosbox2);
			this->resultpnl->Controls->Add(this->label13);
			this->resultpnl->Controls->Add(this->descbox2);
			this->resultpnl->Controls->Add(this->label10);
			this->resultpnl->Controls->Add(this->defendbox2);
			this->resultpnl->Controls->Add(this->label9);
			this->resultpnl->Controls->Add(this->datebox2);
			this->resultpnl->Controls->Add(this->label8);
			this->resultpnl->Controls->Add(this->officerbox2);
			this->resultpnl->Controls->Add(this->label11);
			this->resultpnl->Location = System::Drawing::Point(0, 200);
			this->resultpnl->Name = L"resultpnl";
			this->resultpnl->Size = System::Drawing::Size(861, 290);
			this->resultpnl->TabIndex = 9;
			// 
			// prosbox2
			// 
			this->prosbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->prosbox2->Location = System::Drawing::Point(211, 249);
			this->prosbox2->Multiline = true;
			this->prosbox2->Name = L"prosbox2";
			this->prosbox2->ReadOnly = true;
			this->prosbox2->Size = System::Drawing::Size(190, 37);
			this->prosbox2->TabIndex = 9;
			this->prosbox2->WordWrap = false;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(15, 250);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(174, 30);
			this->label13->TabIndex = 8;
			this->label13->Text = L"Prosecuted By :";
			// 
			// descbox2
			// 
			this->descbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descbox2->Location = System::Drawing::Point(482, 108);
			this->descbox2->Multiline = true;
			this->descbox2->Name = L"descbox2";
			this->descbox2->ReadOnly = true;
			this->descbox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descbox2->Size = System::Drawing::Size(367, 120);
			this->descbox2->TabIndex = 7;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(477, 59);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(144, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Description :";
			// 
			// defendbox2
			// 
			this->defendbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->defendbox2->Location = System::Drawing::Point(208, 179);
			this->defendbox2->Multiline = true;
			this->defendbox2->Name = L"defendbox2";
			this->defendbox2->ReadOnly = true;
			this->defendbox2->Size = System::Drawing::Size(190, 37);
			this->defendbox2->TabIndex = 5;
			this->defendbox2->WordWrap = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(12, 180);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(158, 30);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Defended By :";
			// 
			// datebox2
			// 
			this->datebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox2->Location = System::Drawing::Point(211, 109);
			this->datebox2->Multiline = true;
			this->datebox2->Name = L"datebox2";
			this->datebox2->ReadOnly = true;
			this->datebox2->Size = System::Drawing::Size(190, 37);
			this->datebox2->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(15, 110);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(136, 30);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Filing Date :";
			// 
			// officerbox2
			// 
			this->officerbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->officerbox2->Location = System::Drawing::Point(208, 39);
			this->officerbox2->Multiline = true;
			this->officerbox2->Name = L"officerbox2";
			this->officerbox2->ReadOnly = true;
			this->officerbox2->Size = System::Drawing::Size(190, 37);
			this->officerbox2->TabIndex = 1;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(12, 40);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(125, 30);
			this->label11->TabIndex = 0;
			this->label11->Text = L"Officer ID :";
			// 
			// viewheading
			// 
			this->viewheading->AutoSize = true;
			this->viewheading->BackColor = System::Drawing::Color::Transparent;
			this->viewheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewheading->ForeColor = System::Drawing::Color::White;
			this->viewheading->Location = System::Drawing::Point(309, 32);
			this->viewheading->Name = L"viewheading";
			this->viewheading->Size = System::Drawing::Size(254, 45);
			this->viewheading->TabIndex = 10;
			this->viewheading->Text = L"Search Database";
			// 
			// resetbtn
			// 
			this->resetbtn->BackColor = System::Drawing::Color::White;
			this->resetbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn->FlatAppearance->BorderSize = 2;
			this->resetbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->resetbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn->Location = System::Drawing::Point(725, 148);
			this->resetbtn->Name = L"resetbtn";
			this->resetbtn->Size = System::Drawing::Size(122, 45);
			this->resetbtn->TabIndex = 7;
			this->resetbtn->Text = L"Reset";
			this->resetbtn->UseVisualStyleBackColor = false;
			this->resetbtn->Click += gcnew System::EventHandler(this, &Cases::resetbtn_Click);
			// 
			// searchbtn
			// 
			this->searchbtn->BackColor = System::Drawing::Color::White;
			this->searchbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->searchbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->searchbtn->FlatAppearance->BorderSize = 2;
			this->searchbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->searchbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->searchbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->searchbtn->Location = System::Drawing::Point(35, 148);
			this->searchbtn->Name = L"searchbtn";
			this->searchbtn->Size = System::Drawing::Size(122, 45);
			this->searchbtn->TabIndex = 7;
			this->searchbtn->Text = L"Search";
			this->searchbtn->UseVisualStyleBackColor = false;
			this->searchbtn->Click += gcnew System::EventHandler(this, &Cases::searchbtn_Click);
			// 
			// caseBox2
			// 
			this->caseBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->caseBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->caseBox2->Location = System::Drawing::Point(171, 85);
			this->caseBox2->Multiline = true;
			this->caseBox2->Name = L"caseBox2";
			this->caseBox2->Size = System::Drawing::Size(131, 38);
			this->caseBox2->TabIndex = 1;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(28, 90);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(121, 29);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Case No.";
			// 
			// closebtn
			// 
			this->closebtn->BackColor = System::Drawing::Color::White;
			this->closebtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closebtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn->FlatAppearance->BorderSize = 2;
			this->closebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closebtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn->Location = System::Drawing::Point(737, 493);
			this->closebtn->Name = L"closebtn";
			this->closebtn->Size = System::Drawing::Size(110, 44);
			this->closebtn->TabIndex = 11;
			this->closebtn->Text = L"Close";
			this->closebtn->UseVisualStyleBackColor = false;
			this->closebtn->Click += gcnew System::EventHandler(this, &Cases::closebtn_Click);
			// 
			// removepanel
			// 
			this->removepanel->BackColor = System::Drawing::Color::Silver;
			this->removepanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"removepanel.BackgroundImage")));
			this->removepanel->Controls->Add(this->closebutton);
			this->removepanel->Controls->Add(this->label14);
			this->removepanel->Controls->Add(this->removebtn3);
			this->removepanel->Controls->Add(this->caseBox3);
			this->removepanel->Controls->Add(this->fir_lbl);
			this->removepanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->removepanel->Location = System::Drawing::Point(0, 0);
			this->removepanel->Name = L"removepanel";
			this->removepanel->Size = System::Drawing::Size(861, 543);
			this->removepanel->TabIndex = 20;
			// 
			// closebutton
			// 
			this->closebutton->BackColor = System::Drawing::Color::White;
			this->closebutton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closebutton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebutton->FlatAppearance->BorderSize = 2;
			this->closebutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closebutton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closebutton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebutton->Location = System::Drawing::Point(698, 347);
			this->closebutton->Name = L"closebutton";
			this->closebutton->Size = System::Drawing::Size(122, 45);
			this->closebutton->TabIndex = 11;
			this->closebutton->Text = L"Close";
			this->closebutton->UseVisualStyleBackColor = false;
			this->closebutton->Click += gcnew System::EventHandler(this, &Cases::closebutton_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(335, 32);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(213, 45);
			this->label14->TabIndex = 10;
			this->label14->Text = L"Remove Case";
			// 
			// removebtn3
			// 
			this->removebtn3->BackColor = System::Drawing::Color::White;
			this->removebtn3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->removebtn3->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->removebtn3->FlatAppearance->BorderSize = 2;
			this->removebtn3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->removebtn3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->removebtn3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->removebtn3->Location = System::Drawing::Point(368, 235);
			this->removebtn3->Name = L"removebtn3";
			this->removebtn3->Size = System::Drawing::Size(122, 45);
			this->removebtn3->TabIndex = 7;
			this->removebtn3->Text = L"Remove";
			this->removebtn3->UseVisualStyleBackColor = false;
			this->removebtn3->Click += gcnew System::EventHandler(this, &Cases::removebtn3_Click);
			// 
			// caseBox3
			// 
			this->caseBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->caseBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->caseBox3->Location = System::Drawing::Point(363, 152);
			this->caseBox3->Multiline = true;
			this->caseBox3->Name = L"caseBox3";
			this->caseBox3->Size = System::Drawing::Size(131, 38);
			this->caseBox3->TabIndex = 1;
			// 
			// fir_lbl
			// 
			this->fir_lbl->AutoSize = true;
			this->fir_lbl->BackColor = System::Drawing::Color::Transparent;
			this->fir_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fir_lbl->ForeColor = System::Drawing::Color::White;
			this->fir_lbl->Location = System::Drawing::Point(214, 156);
			this->fir_lbl->Name = L"fir_lbl";
			this->fir_lbl->Size = System::Drawing::Size(144, 33);
			this->fir_lbl->TabIndex = 0;
			this->fir_lbl->Text = L"Case No.";
			// 
			// Cases
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(861, 570);
			this->Controls->Add(this->removepanel);
			this->Controls->Add(this->viewpanel);
			this->Controls->Add(this->addpanel);
			this->Controls->Add(this->dbinfo);
			this->Controls->Add(this->abt_Btn);
			this->Controls->Add(this->Exitbtn);
			this->Controls->Add(this->removebtn);
			this->Controls->Add(this->viewbtn);
			this->Controls->Add(this->addbtn);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->heading);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Cases";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Cases";
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->addpanel->ResumeLayout(false);
			this->addpanel->PerformLayout();
			this->viewpanel->ResumeLayout(false);
			this->viewpanel->PerformLayout();
			this->resultpnl->ResumeLayout(false);
			this->resultpnl->PerformLayout();
			this->removepanel->ResumeLayout(false);
			this->removepanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void addbtn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		addpanel->Show();
	}
private: System::Void resetbtn1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	caseBox1->Clear();
	officerbox1->Clear();
	datebox1->ResetText();
	defendbox1->Clear();
	prosbox1->Clear();
	descBox1->Clear();

}

private: System::Void closebtn1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::DialogResult msgbox;
	if (textchange == true)
	{
		msgbox = MessageBox::Show("Are you sure you want to Exit without saving.", "Save Information", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (msgbox== System::Windows::Forms::DialogResult::Yes)
		{
			caseBox1->Clear();
			officerbox1->Clear();
			datebox1->ResetText();
			defendbox1->Clear();
			prosbox1->Clear();
			descBox1->Clear();
			addpanel->Hide();
		}
		else if (msgbox == System::Windows::Forms::DialogResult::No)
		{
			return;
		}
	}
	else
	{
		addpanel->Hide();
	}
}

private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	int CASEno = NULL , officer_id = NULL;

	try
	{
		CASEno = System::Convert::ToInt16(caseBox1->Text);
		officer_id = System::Convert::ToInt16(officerbox1->Text);

		if (isDbEnabled == true)
		{
			if (!case_nocheck(CASEno))
			{
				MessageBox::Show("A case with this Case number already exist.", "PrimaryKey Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			addCaseDB(CASEno, officer_id, datebox1->Text, defendbox1->Text, prosbox1->Text, descBox1->Text);
		}
		else
		{
			addCaseCSV(CASEno, officer_id, datebox1->Text, defendbox1->Text, prosbox1->Text, descBox1->Text);
		}
	}
	catch (...)
	{
		MessageBox::Show("Case number and Officer ID can only be digits.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	MessageBox::Show("Details have been successfully saved.", "DialogBox", MessageBoxButtons::OK, MessageBoxIcon::Information);
	textchange = false;
}

//private: System::Void caseBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) 
//{
//	textchange = true;
//}
private: System::Void viewbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	addpanel->Hide();
	viewpanel->Show();
}
private: System::Void searchbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (caseBox2->Text== "")
	{
		MessageBox::Show("This field requires data.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	try
	{
		int caseNo = System::Convert::ToInt16(caseBox2->Text);
		if (isDbEnabled == true)
		{
			viewCaseDB(caseNo);
		}
		else
		{
			viewCaseCSV(caseNo);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		caseBox2->Clear();
	}
}

private: System::Void resetbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	caseBox2->Clear();
	officerbox2->Clear();
	datebox2->ResetText();
	defendbox2->Clear();
	prosbox2->Clear();
	descbox2->Clear();
}
private: System::Void closebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	caseBox2->Clear();
	officerbox2->Clear();
	datebox2->ResetText();
	defendbox2->Clear();
	prosbox2->Clear();
	descbox2->Clear();
	viewpanel->Hide();
	resultpnl->Hide();
}
private: System::Void removebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	addpanel->Hide();
	viewpanel->Hide();
	resultpnl->Hide();
	removepanel->Show();
}

private: System::Void removebtn3_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (caseBox3->Text == "")
	{
		MessageBox::Show("This field requires data.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	try
	{
		int caseNo = System::Convert::ToInt16(caseBox3->Text);

		if (isDbEnabled)
		{
			removeCaseDB(caseNo);
		}
		else
		{
			removeCaseCSV(caseNo);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		caseBox3->Clear();
	}
}
private: System::Void closebutton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	caseBox3->Clear();
	removepanel->Hide();
}
private: System::Void abt_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Case Details are manipulated through this tab . Other Details are also Stored ", "Cases Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void caseBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textchange = true; 
}
private: System::Void dbinfo_Click(System::Object^ sender, System::EventArgs^ e) {
	if (isDbEnabled == false)
	{
		MessageBox::Show("MYSQL Server is not installed on your system .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("MYSQL Server 8.0 .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
private: System::Void Exitbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Cases::Close(); 
}
};
}
