#pragma once
#include<sstream>
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
	//using namespace msclr::interop;*/

	/// <summary>
	/// Summary for Forensics
	/// </summary>
	public ref class Forensics : public System::Windows::Forms::Form
	{
	public:
	
	MYSQL* currentconn;
	bool isDbEnabled;
	bool textChange = false;

	private: System::Windows::Forms::Panel^ createrep_pnl;
	
	private: System::Windows::Forms::ComboBox^ FprintsBox1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ Bloodgrpbox1;
	private: System::Windows::Forms::Button^ createClbtn;


	private: System::Windows::Forms::Button^ savebtn;
	private: System::Windows::Forms::TextBox^ descBox1;
	private: System::Windows::Forms::DateTimePicker^ datebox1;


	private: System::Windows::Forms::ComboBox^ dnabox1;

	private: System::Windows::Forms::TextBox^ RepBox1;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ viewreportpnl;
	private: System::Windows::Forms::Panel^ resultpnl;
	private: System::Windows::Forms::TextBox^ descBox2;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ FprintsBox2;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ dnabox2;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ Bloodgrpbox2;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ viewheading;
	private: System::Windows::Forms::Button^ resetbtn;
	private: System::Windows::Forms::Button^ searchbtn;
	private: System::Windows::Forms::TextBox^ RepBox2;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Button^ closebtn;
	private: System::Windows::Forms::TextBox^ datebox2;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Panel^ Rmvreportpnl;
	private: System::Windows::Forms::Button^ close_rpt_btn;


	private: System::Windows::Forms::Label^ Heading;
	private: System::Windows::Forms::Button^ rmvreportbtn;


	private: System::Windows::Forms::TextBox^ RepBox3;

	private: System::Windows::Forms::Label^ repnumlbl;

	private: System::Windows::Forms::Label^ label2;
	public:
		Forensics(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			createrep_pnl->Hide();
			viewreportpnl->Hide();
			resultpnl->Hide();
			Rmvreportpnl->Hide();
		}
		Forensics(MYSQL* db, bool isconn)
		{
			InitializeComponent();
			createrep_pnl->Hide();
			viewreportpnl->Hide();
			resultpnl->Hide();
			Rmvreportpnl->Hide();
			isDbEnabled = isconn;
			currentconn = db;

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
		void resetpnl()
		{
			RepBox1->Clear();
			Bloodgrpbox1->Clear();
			descBox1->Clear();
			dnabox1->ResetText();
			FprintsBox1->ResetText();
			datebox1->ResetText();
		}
		//void createreportdb(int Report_No, String^ bloodgroup, String^ DNA , String^ Finger_prints, String^Date, String^Description )
		//{
		//	string Bloodgroup, Dna, Fprints, DATE, Desc;
		//	msclr::interop::marshal_context converter;


		//	Bloodgroup = converter.marshal_as<std::string>(Bloodgrpbox1->Text);
		//	Dna = converter.marshal_as<std::string>(dnabox1->Text);
		//	Fprints = converter.marshal_as<std::string>(FprintsBox1->Text);
		//	DATE = converter.marshal_as<std::string>(datebox1->Text);
		//	Desc = converter.marshal_as<std::string>(descBox1->Text);

		//	//Report_No = System::Convert::ToInt16(RepBox1->Text);

		//	stringstream ss;
		//	ss << "insert into cms.forensics (Report_No, bloodgroup, DNA, Finger_prints, Date, Description ) values (" << Report_No << ", " << Bloodgroup << ", " << Dna << ", " << Fprints << ", " << DATE << ", " << Desc << ")";

		//	string query = ss.str();
		//	char* arrayquery;
		//	arrayquery = &query[0];

		//	if (!mysql_query(currentconn , arrayquery))
		//	{
		//		MessageBox::Show("Successfully connected");
		//	}
		//	else
		//	{
		//		MessageBox::Show("Error");
		//	}
		//}
		void createReportDB(int Report_no, String^ Bloodgrp, String^ DNA, String^ fprints, String^ Date, String^Desc)
		{
			msclr::interop::marshal_context converter;
			string bg, dna, FPRINTS, DATE, DESC;

			bg = converter.marshal_as<string > (Bloodgrpbox1->Text);
			dna = converter.marshal_as<string>(dnabox1->Text);
			FPRINTS = converter.marshal_as<string>(FprintsBox1->Text);
			DATE = converter.marshal_as<string>(datebox1->Text);
			DESC = converter.marshal_as<string>(descBox1->Text);

			stringstream ss;
			ss << "insert into cms.forensics(Report_No, bloodgroup, DNA, Finger_prints, Date, Description) values(" << Report_no << ",'" << bg << "','" << dna << "', '" << FPRINTS << "','" << DATE << "','" << DESC << "')";
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
		void createreportCSV(int Report_No, String^ bloodgrp, String^ DNA, String^ Finger_prints, String^ date, String^ Description)
		{
			
			string bloodgroup, Dna, Fprints, Date, Desc;
			msclr::interop::marshal_context converter;
			bloodgroup = converter.marshal_as<std::string>(Bloodgrpbox1->Text);
			Dna = converter.marshal_as<std::string>(dnabox1->Text);
			Fprints = converter.marshal_as<std::string>(FprintsBox1->Text);
			Date = converter.marshal_as<std::string>(datebox1->Text);
			Desc = converter.marshal_as<std::string>(descBox1->Text);

			fstream file1;
			file1.open("Forensics.csv", ios::out | ios::app);
			file1 << Report_No << "," << bloodgroup << "," << Dna << "," << Fprints << "," << Date << "," << Desc << endl;
			file1.close();
		}

		void viewreportdb(int R_no)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			string bg, dna, FPRINTS, DATE, DESC;
			String^ BloodGrp, ^DNA, ^fprints, ^Date, ^Description;

			stringstream ss;
			ss << "select * from cms.forensics where Report_No = " << R_no;
			string query = ss.str();
			char* arrayquery;
			arrayquery = &query[0];

			if (!mysql_query(currentconn, arrayquery))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("No report exist with this report number.", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);

				}
				else
				{
					resultpnl -> Show();
					bg = row[1];
					dna = row[2];
					FPRINTS = row[3];
					DATE = row[4];
					DESC = row[5];

					BloodGrp = gcnew String(bg.c_str());
					DNA = gcnew String(dna.c_str());
					fprints = gcnew String(FPRINTS.c_str());
					Date = gcnew String(DATE.c_str());
					Description = gcnew String(DESC.c_str());

					Bloodgrpbox2->Text = BloodGrp;
					dnabox2->Text = DNA;
					FprintsBox2->Text = fprints;
					datebox2->Text = Date;
					descBox2->Text = Description;
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}

		void viewreportCSV(int R_no)
		{
			int R_no2;
			fstream file1;
			file1.open("Forensics.csv", ios::in);

			while (file1.good())
			{
				string line, word;
				getline(file1, line);
				stringstream ss(line);
				getline(ss, word, ',');

				try
				{
					R_no2 = stoi(word);
				}
				catch (...)
				{
					MessageBox::Show("Any Record with this Report Number does not exist.", "Search Database", MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					break;
				}
				if (R_no == R_no2)
				{
					resultpnl->Show();

					string bloodgrp, Dna, Fprints, day, month, year, desc;
					getline(ss, bloodgrp, ',');
					getline(ss, Dna, ',');
					getline(ss, Fprints, ',');
					getline(ss, day, ',');
					getline(ss, month, ',');
					getline(ss, year, ',');
					getline(ss, desc, ',');
					string date = day + month + year;

					String^ Bloodgrp , ^DNA, ^fingerprints, ^Date, ^Description;
					Bloodgrp = gcnew String(bloodgrp.c_str());
					DNA = gcnew String(Dna.c_str());
					fingerprints = gcnew String(Fprints.c_str());
					Date = gcnew String(date.c_str());
					Description = gcnew String(desc.c_str());

					Bloodgrpbox2->Text = Bloodgrp;
					dnabox2->Text = DNA;
					FprintsBox2->Text = fingerprints;
					datebox2->Text = Date;
					descBox2->Text = Description;
					break;
				}
				else
				{
					continue;
				}
				file1.close();
			}
		}
		void removereportdb(int R_no)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			stringstream ss, dltquery;
			char* arrayquery;
			ss << "select* from cms.forensics where Report_No = " << R_no;
			string query = ss.str();
			arrayquery = &query[0];

			if (!mysql_query(currentconn,arrayquery))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);

				if (row == NULL)
				{
					MessageBox::Show("Any report with ths report number doesnot exist.", "Search Report", MessageBoxButtons::OK, MessageBoxIcon::Error);

				}
				else
				{
					dltquery << "delete from cms.forensics where Report_No = " << R_no;
					string Delete = dltquery.str();
					char* dlt;
					dlt = &Delete[0];
					mysql_query(currentconn, dlt);
					mysql_commit(currentconn);
					MessageBox::Show("Report Deleted Successfully.", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);

				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void removereportCSV(int R_no) 
		{
			fstream file1, file2;
			file1.open("Forensics.csv", ios::in);
			file2.open("Forensicsnew.csv", ios::out);
			int R_no2 = NULL; bool reportexist = false;

			while (file1.good())
			{
				string line, word;
				getline(file1, line);
				stringstream ss(line);
				getline(ss, word, ',');

				try
				{
					R_no2 = stoi(word);
				}
				catch (...)
				{
					break;
				}
				if (R_no == R_no2)
				{
					reportexist = true;
					continue;
				}
				else
				{
					string bloodgrp, Dna, Fprints, day, month, year, desc;
					getline(ss, bloodgrp, ',');
					getline(ss, Dna, ',');
					getline(ss, Fprints, ',');
					getline(ss, day, ',');
					getline(ss, month, ',');
					getline(ss, year, ',');
					getline(ss, desc, ',');
					file2 << R_no2 << "," << bloodgrp << "," << Dna << "," << Fprints << "," << day << "," << month << "," << year << "," << desc << endl;
					continue;
				}
				
			}
			if (reportexist)
			{
				MessageBox::Show("Report Successfully Deleted", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("No Report Exists with this Report Number", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			file1.close();
			file2.close();

			remove("Forensics.csv");
			rename("Forensicsnew.csv", "Forensics.csv");
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Forensics()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ mainheading;
	private: System::Windows::Forms::Button^ removebtn;
	private: System::Windows::Forms::Button^ viewbtn;
	private: System::Windows::Forms::Button^ addbtn;
	private: System::Windows::Forms::Panel^ bottonPnl;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ datalabel;
	private: System::Windows::Forms::Button^ dbinfo;
	private: System::Windows::Forms::Button^ abt_Btn;
	private: System::Windows::Forms::Button^ Exitbtn;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Forensics::typeid));
			this->mainheading = (gcnew System::Windows::Forms::Label());
			this->removebtn = (gcnew System::Windows::Forms::Button());
			this->viewbtn = (gcnew System::Windows::Forms::Button());
			this->addbtn = (gcnew System::Windows::Forms::Button());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->dbinfo = (gcnew System::Windows::Forms::Button());
			this->abt_Btn = (gcnew System::Windows::Forms::Button());
			this->Exitbtn = (gcnew System::Windows::Forms::Button());
			this->createrep_pnl = (gcnew System::Windows::Forms::Panel());
			this->FprintsBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->Bloodgrpbox1 = (gcnew System::Windows::Forms::TextBox());
			this->createClbtn = (gcnew System::Windows::Forms::Button());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->descBox1 = (gcnew System::Windows::Forms::TextBox());
			this->datebox1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dnabox1 = (gcnew System::Windows::Forms::ComboBox());
			this->RepBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->viewreportpnl = (gcnew System::Windows::Forms::Panel());
			this->resultpnl = (gcnew System::Windows::Forms::Panel());
			this->datebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->descBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->FprintsBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->dnabox2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->Bloodgrpbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->resetbtn = (gcnew System::Windows::Forms::Button());
			this->searchbtn = (gcnew System::Windows::Forms::Button());
			this->RepBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->closebtn = (gcnew System::Windows::Forms::Button());
			this->Rmvreportpnl = (gcnew System::Windows::Forms::Panel());
			this->close_rpt_btn = (gcnew System::Windows::Forms::Button());
			this->Heading = (gcnew System::Windows::Forms::Label());
			this->rmvreportbtn = (gcnew System::Windows::Forms::Button());
			this->RepBox3 = (gcnew System::Windows::Forms::TextBox());
			this->repnumlbl = (gcnew System::Windows::Forms::Label());
			this->bottonPnl->SuspendLayout();
			this->createrep_pnl->SuspendLayout();
			this->viewreportpnl->SuspendLayout();
			this->resultpnl->SuspendLayout();
			this->Rmvreportpnl->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainheading
			// 
			this->mainheading->AutoSize = true;
			this->mainheading->BackColor = System::Drawing::Color::Transparent;
			this->mainheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mainheading->ForeColor = System::Drawing::Color::White;
			this->mainheading->Location = System::Drawing::Point(317, 39);
			this->mainheading->Name = L"mainheading";
			this->mainheading->Size = System::Drawing::Size(210, 59);
			this->mainheading->TabIndex = 3;
			this->mainheading->Text = L"Forensics";
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
			this->removebtn->Location = System::Drawing::Point(77, 346);
			this->removebtn->Name = L"removebtn";
			this->removebtn->Size = System::Drawing::Size(166, 39);
			this->removebtn->TabIndex = 4;
			this->removebtn->Text = L"Remove Report";
			this->removebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->removebtn->UseVisualStyleBackColor = false;
			this->removebtn->Click += gcnew System::EventHandler(this, &Forensics::removebtn_Click);
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
			this->viewbtn->Location = System::Drawing::Point(77, 246);
			this->viewbtn->Name = L"viewbtn";
			this->viewbtn->Size = System::Drawing::Size(166, 39);
			this->viewbtn->TabIndex = 5;
			this->viewbtn->Text = L"View Report";
			this->viewbtn->UseVisualStyleBackColor = false;
			this->viewbtn->Click += gcnew System::EventHandler(this, &Forensics::viewbtn_Click);
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
			this->addbtn->Location = System::Drawing::Point(77, 146);
			this->addbtn->Name = L"addbtn";
			this->addbtn->Size = System::Drawing::Size(166, 39);
			this->addbtn->TabIndex = 6;
			this->addbtn->Text = L"Create Report";
			this->addbtn->UseVisualStyleBackColor = false;
			this->addbtn->Click += gcnew System::EventHandler(this, &Forensics::addbtn_Click);
			// 
			// bottonPnl
			// 
			this->bottonPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->bottonPnl->Controls->Add(this->label1);
			this->bottonPnl->Controls->Add(this->datalabel);
			this->bottonPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottonPnl->Location = System::Drawing::Point(0, 543);
			this->bottonPnl->Name = L"bottonPnl";
			this->bottonPnl->Size = System::Drawing::Size(861, 27);
			this->bottonPnl->TabIndex = 7;
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
			// dbinfo
			// 
			this->dbinfo->BackColor = System::Drawing::Color::DarkGray;
			this->dbinfo->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->dbinfo->FlatAppearance->BorderSize = 0;
			this->dbinfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->dbinfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dbinfo->Location = System::Drawing::Point(592, 246);
			this->dbinfo->Name = L"dbinfo";
			this->dbinfo->Size = System::Drawing::Size(166, 39);
			this->dbinfo->TabIndex = 8;
			this->dbinfo->Text = L"Database Info";
			this->dbinfo->UseVisualStyleBackColor = false;
			this->dbinfo->Click += gcnew System::EventHandler(this, &Forensics::dbinfo_Click);
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
			this->abt_Btn->Location = System::Drawing::Point(592, 146);
			this->abt_Btn->Name = L"abt_Btn";
			this->abt_Btn->Size = System::Drawing::Size(166, 39);
			this->abt_Btn->TabIndex = 9;
			this->abt_Btn->Text = L"About";
			this->abt_Btn->UseVisualStyleBackColor = false;
			this->abt_Btn->Click += gcnew System::EventHandler(this, &Forensics::abt_Btn_Click);
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
			this->Exitbtn->Location = System::Drawing::Point(592, 346);
			this->Exitbtn->Name = L"Exitbtn";
			this->Exitbtn->Size = System::Drawing::Size(166, 39);
			this->Exitbtn->TabIndex = 10;
			this->Exitbtn->Text = L"Exit";
			this->Exitbtn->UseVisualStyleBackColor = false;
			this->Exitbtn->Click += gcnew System::EventHandler(this, &Forensics::Exitbtn_Click);
			// 
			// createrep_pnl
			// 
			this->createrep_pnl->BackColor = System::Drawing::Color::Silver;
			this->createrep_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"createrep_pnl.BackgroundImage")));
			this->createrep_pnl->Controls->Add(this->FprintsBox1);
			this->createrep_pnl->Controls->Add(this->label7);
			this->createrep_pnl->Controls->Add(this->Bloodgrpbox1);
			this->createrep_pnl->Controls->Add(this->createClbtn);
			this->createrep_pnl->Controls->Add(this->savebtn);
			this->createrep_pnl->Controls->Add(this->descBox1);
			this->createrep_pnl->Controls->Add(this->datebox1);
			this->createrep_pnl->Controls->Add(this->dnabox1);
			this->createrep_pnl->Controls->Add(this->RepBox1);
			this->createrep_pnl->Controls->Add(this->label6);
			this->createrep_pnl->Controls->Add(this->label5);
			this->createrep_pnl->Controls->Add(this->label4);
			this->createrep_pnl->Controls->Add(this->label3);
			this->createrep_pnl->Controls->Add(this->label2);
			this->createrep_pnl->Location = System::Drawing::Point(0, 0);
			this->createrep_pnl->Name = L"createrep_pnl";
			this->createrep_pnl->Size = System::Drawing::Size(861, 543);
			this->createrep_pnl->TabIndex = 11;
			// 
			// FprintsBox1
			// 
			this->FprintsBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FprintsBox1->FormattingEnabled = true;
			this->FprintsBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Found ", L"Not Found" });
			this->FprintsBox1->Location = System::Drawing::Point(187, 201);
			this->FprintsBox1->Name = L"FprintsBox1";
			this->FprintsBox1->Size = System::Drawing::Size(124, 25);
			this->FprintsBox1->TabIndex = 10;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(26, 205);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(129, 24);
			this->label7->TabIndex = 9;
			this->label7->Text = L"Finger Prints";
			// 
			// Bloodgrpbox1
			// 
			this->Bloodgrpbox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Bloodgrpbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Bloodgrpbox1->Location = System::Drawing::Point(187, 92);
			this->Bloodgrpbox1->Multiline = true;
			this->Bloodgrpbox1->Name = L"Bloodgrpbox1";
			this->Bloodgrpbox1->Size = System::Drawing::Size(124, 25);
			this->Bloodgrpbox1->TabIndex = 8;
			// 
			// createClbtn
			// 
			this->createClbtn->BackColor = System::Drawing::Color::White;
			this->createClbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->createClbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->createClbtn->FlatAppearance->BorderSize = 2;
			this->createClbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->createClbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->createClbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->createClbtn->Location = System::Drawing::Point(707, 128);
			this->createClbtn->Name = L"createClbtn";
			this->createClbtn->Size = System::Drawing::Size(118, 58);
			this->createClbtn->TabIndex = 7;
			this->createClbtn->Text = L"Close";
			this->createClbtn->UseVisualStyleBackColor = false;
			this->createClbtn->Click += gcnew System::EventHandler(this, &Forensics::createClbtn_Click);
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
			this->savebtn->Click += gcnew System::EventHandler(this, &Forensics::savebtn_Click);
			// 
			// descBox1
			// 
			this->descBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descBox1->Location = System::Drawing::Point(126, 365);
			this->descBox1->Multiline = true;
			this->descBox1->Name = L"descBox1";
			this->descBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descBox1->Size = System::Drawing::Size(598, 106);
			this->descBox1->TabIndex = 6;
			// 
			// datebox1
			// 
			this->datebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox1->Location = System::Drawing::Point(187, 254);
			this->datebox1->Name = L"datebox1";
			this->datebox1->Size = System::Drawing::Size(240, 25);
			this->datebox1->TabIndex = 5;
			// 
			// dnabox1
			// 
			this->dnabox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dnabox1->FormattingEnabled = true;
			this->dnabox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Found", L"Not Found" });
			this->dnabox1->Location = System::Drawing::Point(187, 146);
			this->dnabox1->Name = L"dnabox1";
			this->dnabox1->Size = System::Drawing::Size(124, 25);
			this->dnabox1->TabIndex = 3;
			// 
			// RepBox1
			// 
			this->RepBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->RepBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RepBox1->Location = System::Drawing::Point(187, 40);
			this->RepBox1->Name = L"RepBox1";
			this->RepBox1->Size = System::Drawing::Size(124, 25);
			this->RepBox1->TabIndex = 1;
			this->RepBox1->TextChanged += gcnew System::EventHandler(this, &Forensics::RepBox1_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(26, 317);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(252, 24);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Enter Description Below : ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(26, 261);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(52, 24);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Date";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(26, 149);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(139, 24);
			this->label4->TabIndex = 0;
			this->label4->Text = L"DNA Samples";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(26, 93);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 24);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Blood Group";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(26, 37);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Report No.";
			// 
			// viewreportpnl
			// 
			this->viewreportpnl->BackColor = System::Drawing::Color::Silver;
			this->viewreportpnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"viewreportpnl.BackgroundImage")));
			this->viewreportpnl->Controls->Add(this->resultpnl);
			this->viewreportpnl->Controls->Add(this->viewheading);
			this->viewreportpnl->Controls->Add(this->resetbtn);
			this->viewreportpnl->Controls->Add(this->searchbtn);
			this->viewreportpnl->Controls->Add(this->RepBox2);
			this->viewreportpnl->Controls->Add(this->label12);
			this->viewreportpnl->Controls->Add(this->closebtn);
			this->viewreportpnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->viewreportpnl->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->viewreportpnl->Location = System::Drawing::Point(0, 0);
			this->viewreportpnl->Name = L"viewreportpnl";
			this->viewreportpnl->Size = System::Drawing::Size(861, 543);
			this->viewreportpnl->TabIndex = 12;
			// 
			// resultpnl
			// 
			this->resultpnl->BackColor = System::Drawing::Color::Transparent;
			this->resultpnl->Controls->Add(this->datebox2);
			this->resultpnl->Controls->Add(this->label13);
			this->resultpnl->Controls->Add(this->descBox2);
			this->resultpnl->Controls->Add(this->label10);
			this->resultpnl->Controls->Add(this->FprintsBox2);
			this->resultpnl->Controls->Add(this->label9);
			this->resultpnl->Controls->Add(this->dnabox2);
			this->resultpnl->Controls->Add(this->label8);
			this->resultpnl->Controls->Add(this->Bloodgrpbox2);
			this->resultpnl->Controls->Add(this->label11);
			this->resultpnl->Location = System::Drawing::Point(0, 205);
			this->resultpnl->Name = L"resultpnl";
			this->resultpnl->Size = System::Drawing::Size(861, 285);
			this->resultpnl->TabIndex = 9;
			// 
			// datebox2
			// 
			this->datebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox2->Location = System::Drawing::Point(191, 217);
			this->datebox2->Multiline = true;
			this->datebox2->Name = L"datebox2";
			this->datebox2->ReadOnly = true;
			this->datebox2->Size = System::Drawing::Size(171, 37);
			this->datebox2->TabIndex = 9;
			this->datebox2->WordWrap = false;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(31, 223);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(62, 30);
			this->label13->TabIndex = 8;
			this->label13->Text = L"Date";
			// 
			// descBox2
			// 
			this->descBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descBox2->Location = System::Drawing::Point(418, 100);
			this->descBox2->Multiline = true;
			this->descBox2->Name = L"descBox2";
			this->descBox2->ReadOnly = true;
			this->descBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descBox2->Size = System::Drawing::Size(371, 120);
			this->descBox2->TabIndex = 7;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(413, 52);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(144, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Description :";
			// 
			// FprintsBox2
			// 
			this->FprintsBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FprintsBox2->Location = System::Drawing::Point(191, 156);
			this->FprintsBox2->Multiline = true;
			this->FprintsBox2->Name = L"FprintsBox2";
			this->FprintsBox2->ReadOnly = true;
			this->FprintsBox2->Size = System::Drawing::Size(171, 37);
			this->FprintsBox2->TabIndex = 5;
			this->FprintsBox2->WordWrap = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(31, 160);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(151, 30);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Finger Prints ";
			// 
			// dnabox2
			// 
			this->dnabox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dnabox2->Location = System::Drawing::Point(191, 95);
			this->dnabox2->Multiline = true;
			this->dnabox2->Name = L"dnabox2";
			this->dnabox2->ReadOnly = true;
			this->dnabox2->Size = System::Drawing::Size(171, 37);
			this->dnabox2->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(31, 97);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(153, 30);
			this->label8->TabIndex = 2;
			this->label8->Text = L"DNA Samples";
			// 
			// Bloodgrpbox2
			// 
			this->Bloodgrpbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Bloodgrpbox2->Location = System::Drawing::Point(191, 34);
			this->Bloodgrpbox2->Multiline = true;
			this->Bloodgrpbox2->Name = L"Bloodgrpbox2";
			this->Bloodgrpbox2->ReadOnly = true;
			this->Bloodgrpbox2->Size = System::Drawing::Size(171, 37);
			this->Bloodgrpbox2->TabIndex = 1;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(31, 34);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(144, 30);
			this->label11->TabIndex = 0;
			this->label11->Text = L"Blood Group";
			// 
			// viewheading
			// 
			this->viewheading->AutoSize = true;
			this->viewheading->BackColor = System::Drawing::Color::Transparent;
			this->viewheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewheading->ForeColor = System::Drawing::Color::White;
			this->viewheading->Location = System::Drawing::Point(309, 28);
			this->viewheading->Name = L"viewheading";
			this->viewheading->Size = System::Drawing::Size(254, 45);
			this->viewheading->TabIndex = 10;
			this->viewheading->Text = L"Search Database";
			// 
			// resetbtn
			// 
			this->resetbtn->BackColor = System::Drawing::Color::LightGray;
			this->resetbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn->FlatAppearance->BorderSize = 2;
			this->resetbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn->Location = System::Drawing::Point(725, 149);
			this->resetbtn->Name = L"resetbtn";
			this->resetbtn->Size = System::Drawing::Size(122, 45);
			this->resetbtn->TabIndex = 7;
			this->resetbtn->Text = L"Reset";
			this->resetbtn->UseVisualStyleBackColor = false;
			this->resetbtn->Click += gcnew System::EventHandler(this, &Forensics::resetbtn_Click);
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
			this->searchbtn->Location = System::Drawing::Point(35, 149);
			this->searchbtn->Name = L"searchbtn";
			this->searchbtn->Size = System::Drawing::Size(122, 45);
			this->searchbtn->TabIndex = 7;
			this->searchbtn->Text = L"Search";
			this->searchbtn->UseVisualStyleBackColor = false;
			this->searchbtn->Click += gcnew System::EventHandler(this, &Forensics::searchbtn_Click);
			// 
			// RepBox2
			// 
			this->RepBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->RepBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RepBox2->Location = System::Drawing::Point(171, 85);
			this->RepBox2->Multiline = true;
			this->RepBox2->Name = L"RepBox2";
			this->RepBox2->Size = System::Drawing::Size(131, 38);
			this->RepBox2->TabIndex = 1;
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
			this->label12->Size = System::Drawing::Size(140, 29);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Report No.";
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
			this->closebtn->Location = System::Drawing::Point(725, 496);
			this->closebtn->Name = L"closebtn";
			this->closebtn->Size = System::Drawing::Size(124, 41);
			this->closebtn->TabIndex = 11;
			this->closebtn->Text = L"Close";
			this->closebtn->UseVisualStyleBackColor = false;
			this->closebtn->Click += gcnew System::EventHandler(this, &Forensics::closebtn_Click);
			// 
			// Rmvreportpnl
			// 
			this->Rmvreportpnl->BackColor = System::Drawing::Color::Silver;
			this->Rmvreportpnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Rmvreportpnl.BackgroundImage")));
			this->Rmvreportpnl->Controls->Add(this->close_rpt_btn);
			this->Rmvreportpnl->Controls->Add(this->Heading);
			this->Rmvreportpnl->Controls->Add(this->rmvreportbtn);
			this->Rmvreportpnl->Controls->Add(this->RepBox3);
			this->Rmvreportpnl->Controls->Add(this->repnumlbl);
			this->Rmvreportpnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Rmvreportpnl->Location = System::Drawing::Point(0, 0);
			this->Rmvreportpnl->Name = L"Rmvreportpnl";
			this->Rmvreportpnl->Size = System::Drawing::Size(861, 543);
			this->Rmvreportpnl->TabIndex = 13;
			// 
			// close_rpt_btn
			// 
			this->close_rpt_btn->BackColor = System::Drawing::Color::White;
			this->close_rpt_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->close_rpt_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->close_rpt_btn->FlatAppearance->BorderSize = 2;
			this->close_rpt_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->close_rpt_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->close_rpt_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->close_rpt_btn->Location = System::Drawing::Point(725, 451);
			this->close_rpt_btn->Name = L"close_rpt_btn";
			this->close_rpt_btn->Size = System::Drawing::Size(122, 45);
			this->close_rpt_btn->TabIndex = 11;
			this->close_rpt_btn->Text = L"Close";
			this->close_rpt_btn->UseVisualStyleBackColor = false;
			this->close_rpt_btn->Click += gcnew System::EventHandler(this, &Forensics::close_rpt_btn_Click);
			// 
			// Heading
			// 
			this->Heading->AutoSize = true;
			this->Heading->BackColor = System::Drawing::Color::Transparent;
			this->Heading->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Heading->ForeColor = System::Drawing::Color::White;
			this->Heading->Location = System::Drawing::Point(309, 32);
			this->Heading->Name = L"Heading";
			this->Heading->Size = System::Drawing::Size(244, 45);
			this->Heading->TabIndex = 10;
			this->Heading->Text = L"Remove Report";
			// 
			// rmvreportbtn
			// 
			this->rmvreportbtn->BackColor = System::Drawing::Color::White;
			this->rmvreportbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->rmvreportbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->rmvreportbtn->FlatAppearance->BorderSize = 2;
			this->rmvreportbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->rmvreportbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rmvreportbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->rmvreportbtn->Location = System::Drawing::Point(368, 235);
			this->rmvreportbtn->Name = L"rmvreportbtn";
			this->rmvreportbtn->Size = System::Drawing::Size(122, 45);
			this->rmvreportbtn->TabIndex = 7;
			this->rmvreportbtn->Text = L"Remove";
			this->rmvreportbtn->UseVisualStyleBackColor = false;
			this->rmvreportbtn->Click += gcnew System::EventHandler(this, &Forensics::rmvreportbtn_Click);
			// 
			// RepBox3
			// 
			this->RepBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RepBox3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->RepBox3->Location = System::Drawing::Point(368, 152);
			this->RepBox3->Multiline = true;
			this->RepBox3->Name = L"RepBox3";
			this->RepBox3->Size = System::Drawing::Size(131, 38);
			this->RepBox3->TabIndex = 1;
			// 
			// repnumlbl
			// 
			this->repnumlbl->AutoSize = true;
			this->repnumlbl->BackColor = System::Drawing::Color::Transparent;
			this->repnumlbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->repnumlbl->ForeColor = System::Drawing::Color::White;
			this->repnumlbl->Location = System::Drawing::Point(198, 156);
			this->repnumlbl->Name = L"repnumlbl";
			this->repnumlbl->Size = System::Drawing::Size(165, 33);
			this->repnumlbl->TabIndex = 0;
			this->repnumlbl->Text = L"Report No.";
			// 
			// Forensics
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(861, 570);
			this->Controls->Add(this->Rmvreportpnl);
			this->Controls->Add(this->viewreportpnl);
			this->Controls->Add(this->createrep_pnl);
			this->Controls->Add(this->dbinfo);
			this->Controls->Add(this->abt_Btn);
			this->Controls->Add(this->Exitbtn);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->removebtn);
			this->Controls->Add(this->viewbtn);
			this->Controls->Add(this->addbtn);
			this->Controls->Add(this->mainheading);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Forensics";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Forensics";
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->createrep_pnl->ResumeLayout(false);
			this->createrep_pnl->PerformLayout();
			this->viewreportpnl->ResumeLayout(false);
			this->viewreportpnl->PerformLayout();
			this->resultpnl->ResumeLayout(false);
			this->resultpnl->PerformLayout();
			this->Rmvreportpnl->ResumeLayout(false);
			this->Rmvreportpnl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void abt_Btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		MessageBox::Show("This Tab Stores the information of all the forensic analysis gathered during cases. Each detail is distinguished by it's unique report ID .", "Forensic Analysis", MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}


private: System::Void dbinfo_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (isDbEnabled == false)
	{
		MessageBox::Show("MYSQL Server is not installed on your system.", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("MYSQL Server 8.0", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
private: System::Void Exitbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Forensics::Hide();
}

private: System::Void addbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	createrep_pnl->Show();
}


private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	int Report_No;
	try
	{
		Report_No = System::Convert::ToInt16(RepBox1->Text);

		if (isDbEnabled == true)
		{
			createReportDB(Report_No, Bloodgrpbox1->Text, dnabox1->Text, FprintsBox1->Text, datebox1->Text, descBox1->Text);
		}
		else
		{
			createreportCSV(Report_No, Bloodgrpbox1->Text, dnabox1->Text, FprintsBox1->Text, datebox1->Text, descBox1->Text);
		}
	}
	catch (...)
	{
		MessageBox::Show("Report Number can only be digit.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	MessageBox::Show("Report has been created successfully.", "Dialog Box", MessageBoxButtons::OK, MessageBoxIcon::Information);
	createrep_pnl->Hide();
	textChange = false;
	resetpnl();
}

private: System::Void createClbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::DialogResult MsgBox;

	MsgBox = MessageBox::Show("Are you sure you want to exit without saving?", "Save Changes", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
	if (MsgBox == System::Windows::Forms::DialogResult::Yes)
	{
		createrep_pnl->Hide();
		resetpnl();
	}
}


private: System::Void viewbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	createrep_pnl->Hide();
	viewreportpnl->Show();
}

private: System::Void resetbtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	RepBox2->Clear();
	Bloodgrpbox2->Clear();
	dnabox2->Clear();
	datebox2->Clear();
	FprintsBox2->Clear();
	descBox2->Clear();
}

private: System::Void searchbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (RepBox2->Text == "")
	{
		MessageBox::Show("This field Requires Data.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	try
	{
		int R_no = System::Convert::ToInt16(RepBox2->Text);
		if (isDbEnabled)
		{
			viewreportdb(R_no);
		}
		else
		{
			viewreportCSV(R_no);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		RepBox2->Clear();
	}
}
	private: System::Void closebtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		RepBox2->Clear();
		Bloodgrpbox2->Clear();
		dnabox2->Clear();
		datebox2->Clear();
		FprintsBox2->Clear();
		descBox2->Clear();

		viewreportpnl->Hide();
		resultpnl->Hide();
	}


private: System::Void removebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	createrep_pnl->Hide();
	viewreportpnl->Hide();
	resultpnl->Hide();
	Rmvreportpnl->Show();
}

private: System::Void close_rpt_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Rmvreportpnl->Hide();
}


private: System::Void rmvreportbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (RepBox3->Text == "")
	{
		MessageBox::Show("This field Requires Data.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	try
	{
		int RepNo = System::Convert::ToInt16(RepBox3->Text);
		if (isDbEnabled== true)
		{
			removereportdb(RepNo);
		}
		else
		{
			removereportCSV(RepNo);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		RepBox3->Clear();
	}
}


private: System::Void RepBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) 
{
	textChange = true;
}
};
}
