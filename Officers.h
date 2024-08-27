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
	/// Summary for Officers
	/// </summary>
	public ref class Officers : public System::Windows::Forms::Form
	{
	private:
		MYSQL* currentconn;
		bool isDbConnected;
		bool textChange = false;
	public:
		Officers(void)
		{
			InitializeComponent();
			addpanel->Hide();
			viewpanel->Hide();
			removepanel->Hide();
			assignPanel->Hide();
			//
			//TODO: Add the constructor code here
			//
		}
		Officers(MYSQL* db, bool isdb)
		{
			InitializeComponent();
			addpanel->Hide();
			viewpanel->Hide();
			removepanel->Hide();
			assignPanel->Hide();
			currentconn = db;
			isDbConnected = isdb;

			if (isDbConnected)
			{
				datalabel->ForeColor = System::Drawing::Color::LawnGreen;
				csvlabel->ForeColor = System::Drawing::Color::Red;
			}
			else
			{
				datalabel->ForeColor = System::Drawing::Color::Red;
				csvlabel->ForeColor = System::Drawing::Color::LawnGreen;
			}
			//
			//TODO: Add the constructor code here
			//
		}
		bool idcheckdb(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss;
			ss << "select ID from cms.officer where Officer_id = " << id;
			std::string abc = ss.str();
			char* arrayqueue;
			arrayqueue = &abc[0];

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
		//void adddetaildatabase(int id, String^ Name, String^ Date, int age, String^ Rank, String^ Experience)
		//{
		//	//int id, age;

		//	//id = System::Convert::ToInt16(idBox1->Text);
		//	//age = System::Convert::ToInt16(ageBox1->Text);

		//	msclr::interop::marshal_context converter;
		//	std::string name, date, rank, experience;


		//	name = converter.marshal_as<std::string>(nameBox1->Text);
		//	date = converter.marshal_as<std::string>(dateBox1->Text);
		//	rank = converter.marshal_as<std::string>(rankBox1->Text);
		//	experience = converter.marshal_as<std::string>(expBox1->Text);

		//	std::stringstream ss;
		//	ss << "insert into cms.officer (ID, Name, Date, Age, Rank, Experience) values (" << id << " , '" << name << "' , '" << date << "', " << age << ", '" << rank << "' , '" << experience << "' )";
		//	std::string newquery;
		//	newquery = ss.str();
		//	char* arrayqueue;
		//	arrayqueue = &newquery[0];

		//	if (mysql_query(currentconn, arrayqueue))
		//	{
		//		MessageBox::Show("Error");	
		//	}
		//	else
		//	{
		//		MessageBox::Show("Success");
		//	}
		//}
		void AddDetailsDB(int officer_id, String^ Name, String^ Date, int age, String^ Rank, String^ Exp)
		{
			msclr::interop::marshal_context converter;
			string name, date, rank, experience;

			name = converter.marshal_as<string>(nameBox1->Text);
			date = converter.marshal_as<string>(dateBox1->Text);
			rank = converter.marshal_as<string>(rankBox1->Text);
			experience = converter.marshal_as<string>(expBox1->Text);

			stringstream ss;
			ss << " insert into cms.officer (Officer_id, Name, Date, Age, Rank, Experience ) values (" << officer_id << ",'" << name << "' , '" << date << "' , " << age << " , '" << rank << "' , '" << experience << "')";

			string query = ss.str();
			char* arrayqueue;
			arrayqueue = &query[0];


			if (mysql_query(currentconn, arrayqueue))
			{
				MessageBox::Show("Error");
			}
			else
			{
				MessageBox::Show("Success");

			}
		}

		void adddetailcsv()
		{
			std::string name, date, age, rank, experience;

			msclr::interop::marshal_context converter;

			int id = System::Convert::ToInt16(idBox1->Text);

			name = converter.marshal_as<std::string>(nameBox1->Text);
			date = converter.marshal_as<std::string>(dateBox1->Text);
			age = converter.marshal_as<std::string>(ageBox1->Text);
			rank = converter.marshal_as<std::string>(rankBox1->Text);
			experience = converter.marshal_as<std::string>(expBox1->Text);

			std::fstream file1;

			file1.open("Officers.csv", std::ios::out | std::ios::app);
			file1 << id << "," << name << "," << date << "," << age << "," << rank << "," << experience << std::endl;
			file1.close();
		}
		void viewdetailsdatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::string name, date, age, rank, experience;
			String^ Name, ^ Date, ^ Age, ^ Rank, ^ Experience; 


			std::stringstream ss;
			ss << "select * from cms.officer where Officer_id = " << id;
			std::string query = ss.str();
			char* arrayqueue;
			arrayqueue = &query[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("No officer Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					resultpnl->Show();
					name = row[1];
					date = row[2];
					age = row[3];
					rank = row[4];
					experience = row[5];

					Name = gcnew String(name.c_str());
					Date = gcnew String(date.c_str());
					Age = gcnew String(age.c_str());
					Rank = gcnew String(rank.c_str());
					Experience = gcnew String(experience.c_str());

					nameBox2->Text = Name; 
					datebox2->Text = Date; 
					ageBox2->Text = Age; 
					rankBox2->Text = Rank;
					expBox2->Text = Experience; 
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void viewdetailscsv(int id)
		{
			int id2;
			std::fstream file1;
			file1.open("Officers.csv", std::ios::in);

			while (file1.good())
			{
				std::string line, word;
				std::getline(file1, line);
				std::stringstream ss(line);
				std::getline(ss, word, ',');

				try
				{
					id2 = std::stoi(word);
				}
				catch (...)
				{
					MessageBox::Show("No officer Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				if (id == id2)
				{
					resultpnl->Show();
					std::string name, day, month, year, age, rank, experience;
					getline(ss, name, ',');
					getline(ss, day, ',');
					getline(ss, month, ',');
					getline(ss, year, ',');
					getline(ss, age, ',');
					getline(ss, rank, ',');
					getline(ss, experience, ',');
					std::string date = day + month + year;
					String^ Name, ^ Date, ^ Age, ^ Rank, ^ Experience;

					Name = gcnew String(name.c_str());
					Date = gcnew String(date.c_str());
					Age = gcnew String(age.c_str());
					Rank = gcnew String(rank.c_str());
					Experience = gcnew String(experience.c_str());

					nameBox2->Text = Name;
					datebox2->Text = Date;
					ageBox2->Text = Age;
					rankBox2->Text = Rank;
					expBox2->Text = Experience;
					break;
				}
				else
				{
					continue;
				}
			}
			file1.close();
		}
		void removedetaildatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss, delquery;
			char* arrayqueue;

			ss << "select * from cms.officer where Officer_id = " << id;
			std::string q = ss.str();
			arrayqueue = &q[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("Officer does not exist.", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					delquery << "delete from cms.officer where Officer_id = " << id;
					std::string d = delquery.str();
					char* del;
					del = &d[0];
					mysql_query(currentconn, del);
					mysql_commit(currentconn);
					MessageBox::Show("Record Deleted Successfully", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void removedetailcsv(int id)
		{
			std::fstream file1, file2;
			file1.open("Officers.csv", std::ios::in);
			file2.open("OfficersNew.csv", std::ios::out);
			int id2 = NULL; bool idFound = false;

			while (file1.good())
			{
				std::string line, word;
				std::getline(file1, line);
				std::stringstream ss(line);
				std::getline(ss, word, ',');
				try
				{
					id2 = std::stoi(word);
				}
				catch (...)
				{
					break;
				}
				if (id == id2)
				{
					idFound = true;
					continue;
				}
				else
				{
					std::string name, day, month, year, age, rank, experience;
					getline(ss, name, ',');
					getline(ss, day, ',');
					getline(ss, month, ',');
					getline(ss, year, ',');
					getline(ss, age, ',');
					getline(ss, rank, ',');
					getline(ss, experience, ',');

					file2 << id << "," << name << "," << day << "," << month << "," << year << "," << age << "," << rank << "," << experience << std::endl;
					continue;
				}
			}
			if (idFound)
			{
				MessageBox::Show("Record Successfully Deleted", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("Officer Does Not Exist", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			file1.close();
			file2.close();

			remove("Officers.csv");
			rename("OfficersNew.csv", "Officers.csv");
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Officers()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ heading;
	private: System::Windows::Forms::Button^ removebtn;
	private: System::Windows::Forms::Button^ viewbtn;
	private: System::Windows::Forms::Button^ addbtn;
	private: System::Windows::Forms::Button^ dbinfo;
	private: System::Windows::Forms::Button^ aboutBtn;

	private: System::Windows::Forms::Button^ assignBtn;
	private: System::Windows::Forms::Panel^ bottonPnl;
	private: System::Windows::Forms::Label^ csvlabel;

	private: System::Windows::Forms::Label^ datalabel;
	private: System::Windows::Forms::Button^ ExitBtn;
	private: System::Windows::Forms::Panel^ addpanel;
	private: System::Windows::Forms::TextBox^ ageBox1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ rankBox1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ nameBox1;
	private: System::Windows::Forms::Button^ resetbtn1;
	private: System::Windows::Forms::Button^ closebtn1;
	private: System::Windows::Forms::Button^ savebtn;
	private: System::Windows::Forms::TextBox^ expBox1;
	private: System::Windows::Forms::DateTimePicker^ dateBox1;

	private: System::Windows::Forms::TextBox^ idBox1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ viewpanel;
	private: System::Windows::Forms::Panel^ resultpnl;
	private: System::Windows::Forms::TextBox^ rankBox2;



	private: System::Windows::Forms::Label^ label13;



	private: System::Windows::Forms::TextBox^ expBox2;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ ageBox2;


	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ datebox2;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ nameBox2;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ viewheading;
	private: System::Windows::Forms::Button^ resetbtn2;

	private: System::Windows::Forms::Button^ searchbtn;
	private: System::Windows::Forms::TextBox^ idBox2;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Button^ closebtn2;
	private: System::Windows::Forms::Panel^ removepanel;
	private: System::Windows::Forms::Button^ closeBtn3;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Button^ removebtn3;
private: System::Windows::Forms::TextBox^ idBox3;

	private: System::Windows::Forms::Label^ fir_lbl;
	private: System::Windows::Forms::Panel^ assignPanel;
	private: System::Windows::Forms::Button^ closeBtn4;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ idBox4;


	private: System::Windows::Forms::Label^ label15;
private: System::Windows::Forms::ComboBox^ rolebox1;

	private: System::Windows::Forms::Button^ savebtn2;
private: System::Windows::Forms::TextBox^ rankbox3;

	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label16;




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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Officers::typeid));
			this->heading = (gcnew System::Windows::Forms::Label());
			this->removebtn = (gcnew System::Windows::Forms::Button());
			this->viewbtn = (gcnew System::Windows::Forms::Button());
			this->addbtn = (gcnew System::Windows::Forms::Button());
			this->dbinfo = (gcnew System::Windows::Forms::Button());
			this->aboutBtn = (gcnew System::Windows::Forms::Button());
			this->assignBtn = (gcnew System::Windows::Forms::Button());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->csvlabel = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->ExitBtn = (gcnew System::Windows::Forms::Button());
			this->addpanel = (gcnew System::Windows::Forms::Panel());
			this->ageBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->removepanel = (gcnew System::Windows::Forms::Panel());
			this->closeBtn3 = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->removebtn3 = (gcnew System::Windows::Forms::Button());
			this->idBox3 = (gcnew System::Windows::Forms::TextBox());
			this->fir_lbl = (gcnew System::Windows::Forms::Label());
			this->rankBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->nameBox1 = (gcnew System::Windows::Forms::TextBox());
			this->resetbtn1 = (gcnew System::Windows::Forms::Button());
			this->closebtn1 = (gcnew System::Windows::Forms::Button());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->expBox1 = (gcnew System::Windows::Forms::TextBox());
			this->dateBox1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->idBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->viewpanel = (gcnew System::Windows::Forms::Panel());
			this->resultpnl = (gcnew System::Windows::Forms::Panel());
			this->rankBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->expBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->ageBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->closebtn2 = (gcnew System::Windows::Forms::Button());
			this->datebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->nameBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->resetbtn2 = (gcnew System::Windows::Forms::Button());
			this->searchbtn = (gcnew System::Windows::Forms::Button());
			this->idBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->assignPanel = (gcnew System::Windows::Forms::Panel());
			this->rolebox1 = (gcnew System::Windows::Forms::ComboBox());
			this->savebtn2 = (gcnew System::Windows::Forms::Button());
			this->closeBtn4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->rankbox3 = (gcnew System::Windows::Forms::TextBox());
			this->idBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->bottonPnl->SuspendLayout();
			this->addpanel->SuspendLayout();
			this->removepanel->SuspendLayout();
			this->viewpanel->SuspendLayout();
			this->resultpnl->SuspendLayout();
			this->assignPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// heading
			// 
			this->heading->AutoSize = true;
			this->heading->BackColor = System::Drawing::Color::Transparent;
			this->heading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->heading->ForeColor = System::Drawing::Color::White;
			this->heading->Location = System::Drawing::Point(312, 31);
			this->heading->Name = L"heading";
			this->heading->Size = System::Drawing::Size(182, 59);
			this->heading->TabIndex = 10;
			this->heading->Text = L"Officers";
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
			this->removebtn->Location = System::Drawing::Point(85, 335);
			this->removebtn->Name = L"removebtn";
			this->removebtn->Size = System::Drawing::Size(166, 39);
			this->removebtn->TabIndex = 15;
			this->removebtn->Text = L"Remove Officer";
			this->removebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->removebtn->UseVisualStyleBackColor = false;
			this->removebtn->Click += gcnew System::EventHandler(this, &Officers::removebtn_Click);
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
			this->viewbtn->Location = System::Drawing::Point(85, 230);
			this->viewbtn->Name = L"viewbtn";
			this->viewbtn->Size = System::Drawing::Size(166, 39);
			this->viewbtn->TabIndex = 16;
			this->viewbtn->Text = L"View Officer Data";
			this->viewbtn->UseVisualStyleBackColor = false;
			this->viewbtn->Click += gcnew System::EventHandler(this, &Officers::viewbtn_Click);
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
			this->addbtn->Location = System::Drawing::Point(85, 135);
			this->addbtn->Name = L"addbtn";
			this->addbtn->Size = System::Drawing::Size(166, 39);
			this->addbtn->TabIndex = 17;
			this->addbtn->Text = L"Add Officer";
			this->addbtn->UseVisualStyleBackColor = false;
			this->addbtn->Click += gcnew System::EventHandler(this, &Officers::addbtn_Click);
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
			this->dbinfo->Location = System::Drawing::Point(539, 230);
			this->dbinfo->Name = L"dbinfo";
			this->dbinfo->Size = System::Drawing::Size(166, 39);
			this->dbinfo->TabIndex = 18;
			this->dbinfo->Text = L"Database Info";
			this->dbinfo->UseVisualStyleBackColor = false;
			this->dbinfo->Click += gcnew System::EventHandler(this, &Officers::dbinfo_Click);
			// 
			// aboutBtn
			// 
			this->aboutBtn->BackColor = System::Drawing::Color::DarkGray;
			this->aboutBtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->aboutBtn->FlatAppearance->BorderSize = 0;
			this->aboutBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->aboutBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->aboutBtn->Location = System::Drawing::Point(539, 335);
			this->aboutBtn->Name = L"aboutBtn";
			this->aboutBtn->Size = System::Drawing::Size(166, 39);
			this->aboutBtn->TabIndex = 19;
			this->aboutBtn->Text = L"About";
			this->aboutBtn->UseVisualStyleBackColor = false;
			this->aboutBtn->Click += gcnew System::EventHandler(this, &Officers::aboutBtn_Click);
			// 
			// assignBtn
			// 
			this->assignBtn->BackColor = System::Drawing::Color::DarkGray;
			this->assignBtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->assignBtn->FlatAppearance->BorderSize = 0;
			this->assignBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->assignBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->assignBtn->Location = System::Drawing::Point(539, 135);
			this->assignBtn->Name = L"assignBtn";
			this->assignBtn->Size = System::Drawing::Size(166, 39);
			this->assignBtn->TabIndex = 20;
			this->assignBtn->Text = L"Assign Role";
			this->assignBtn->UseVisualStyleBackColor = false;
			this->assignBtn->Click += gcnew System::EventHandler(this, &Officers::assignBtn_Click);
			// 
			// bottonPnl
			// 
			this->bottonPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->bottonPnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->bottonPnl->Controls->Add(this->csvlabel);
			this->bottonPnl->Controls->Add(this->datalabel);
			this->bottonPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottonPnl->Location = System::Drawing::Point(0, 504);
			this->bottonPnl->Name = L"bottonPnl";
			this->bottonPnl->Size = System::Drawing::Size(845, 27);
			this->bottonPnl->TabIndex = 21;
			// 
			// csvlabel
			// 
			this->csvlabel->AutoSize = true;
			this->csvlabel->BackColor = System::Drawing::Color::Transparent;
			this->csvlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->csvlabel->ForeColor = System::Drawing::Color::White;
			this->csvlabel->Location = System::Drawing::Point(1, 4);
			this->csvlabel->Name = L"csvlabel";
			this->csvlabel->Size = System::Drawing::Size(159, 19);
			this->csvlabel->TabIndex = 5;
			this->csvlabel->Text = L"WINDOWS FILE SYSTEM";
			// 
			// datalabel
			// 
			this->datalabel->AutoSize = true;
			this->datalabel->BackColor = System::Drawing::Color::Transparent;
			this->datalabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datalabel->ForeColor = System::Drawing::Color::White;
			this->datalabel->Location = System::Drawing::Point(789, 4);
			this->datalabel->Name = L"datalabel";
			this->datalabel->Size = System::Drawing::Size(55, 19);
			this->datalabel->TabIndex = 5;
			this->datalabel->Text = L"MYSQL";
			// 
			// ExitBtn
			// 
			this->ExitBtn->BackColor = System::Drawing::Color::DarkGray;
			this->ExitBtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ExitBtn->FlatAppearance->BorderSize = 0;
			this->ExitBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->ExitBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ExitBtn->Location = System::Drawing::Point(322, 389);
			this->ExitBtn->Name = L"ExitBtn";
			this->ExitBtn->Size = System::Drawing::Size(166, 39);
			this->ExitBtn->TabIndex = 19;
			this->ExitBtn->Text = L"Exit";
			this->ExitBtn->UseVisualStyleBackColor = false;
			this->ExitBtn->Click += gcnew System::EventHandler(this, &Officers::ExitBtn_Click);
			// 
			// addpanel
			// 
			this->addpanel->BackColor = System::Drawing::Color::Silver;
			this->addpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addpanel.BackgroundImage")));
			this->addpanel->Controls->Add(this->ageBox1);
			this->addpanel->Controls->Add(this->label7);
			this->addpanel->Controls->Add(this->rankBox1);
			this->addpanel->Controls->Add(this->label5);
			this->addpanel->Controls->Add(this->nameBox1);
			this->addpanel->Controls->Add(this->resetbtn1);
			this->addpanel->Controls->Add(this->closebtn1);
			this->addpanel->Controls->Add(this->savebtn);
			this->addpanel->Controls->Add(this->expBox1);
			this->addpanel->Controls->Add(this->dateBox1);
			this->addpanel->Controls->Add(this->idBox1);
			this->addpanel->Controls->Add(this->label6);
			this->addpanel->Controls->Add(this->label4);
			this->addpanel->Controls->Add(this->label3);
			this->addpanel->Controls->Add(this->label2);
			this->addpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->addpanel->Location = System::Drawing::Point(0, 0);
			this->addpanel->Name = L"addpanel";
			this->addpanel->Size = System::Drawing::Size(845, 504);
			this->addpanel->TabIndex = 22;
			// 
			// ageBox1
			// 
			this->ageBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ageBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ageBox1->Location = System::Drawing::Point(279, 173);
			this->ageBox1->Multiline = true;
			this->ageBox1->Name = L"ageBox1";
			this->ageBox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->ageBox1->Size = System::Drawing::Size(146, 31);
			this->ageBox1->TabIndex = 12;
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
			this->label7->Size = System::Drawing::Size(126, 24);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Joining Date";
			// 
			// removepanel
			// 
			this->removepanel->BackColor = System::Drawing::Color::Silver;
			this->removepanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"removepanel.BackgroundImage")));
			this->removepanel->Controls->Add(this->closeBtn3);
			this->removepanel->Controls->Add(this->label14);
			this->removepanel->Controls->Add(this->removebtn3);
			this->removepanel->Controls->Add(this->idBox3);
			this->removepanel->Controls->Add(this->fir_lbl);
			this->removepanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->removepanel->Location = System::Drawing::Point(0, 0);
			this->removepanel->Name = L"removepanel";
			this->removepanel->Size = System::Drawing::Size(845, 504);
			this->removepanel->TabIndex = 24;
			// 
			// closeBtn3
			// 
			this->closeBtn3->BackColor = System::Drawing::Color::White;
			this->closeBtn3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closeBtn3->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closeBtn3->FlatAppearance->BorderSize = 2;
			this->closeBtn3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeBtn3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closeBtn3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closeBtn3->Location = System::Drawing::Point(698, 347);
			this->closeBtn3->Name = L"closeBtn3";
			this->closeBtn3->Size = System::Drawing::Size(122, 45);
			this->closeBtn3->TabIndex = 11;
			this->closeBtn3->Text = L"Close";
			this->closeBtn3->UseVisualStyleBackColor = false;
			this->closeBtn3->Click += gcnew System::EventHandler(this, &Officers::closeBtn3_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(283, 31);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(243, 45);
			this->label14->TabIndex = 10;
			this->label14->Text = L"Remove Officer";
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
			this->removebtn3->Location = System::Drawing::Point(366, 231);
			this->removebtn3->Name = L"removebtn3";
			this->removebtn3->Size = System::Drawing::Size(122, 45);
			this->removebtn3->TabIndex = 7;
			this->removebtn3->Text = L"Remove";
			this->removebtn3->UseVisualStyleBackColor = false;
			this->removebtn3->Click += gcnew System::EventHandler(this, &Officers::removebtn3_Click);
			// 
			// idBox3
			// 
			this->idBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->idBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->idBox3->Location = System::Drawing::Point(363, 152);
			this->idBox3->Multiline = true;
			this->idBox3->Name = L"idBox3";
			this->idBox3->Size = System::Drawing::Size(131, 38);
			this->idBox3->TabIndex = 1;
			// 
			// fir_lbl
			// 
			this->fir_lbl->AutoSize = true;
			this->fir_lbl->BackColor = System::Drawing::Color::Transparent;
			this->fir_lbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fir_lbl->ForeColor = System::Drawing::Color::White;
			this->fir_lbl->Location = System::Drawing::Point(219, 160);
			this->fir_lbl->Name = L"fir_lbl";
			this->fir_lbl->Size = System::Drawing::Size(113, 30);
			this->fir_lbl->TabIndex = 0;
			this->fir_lbl->Text = L"Officer ID";
			// 
			// rankBox1
			// 
			this->rankBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rankBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rankBox1->Location = System::Drawing::Point(279, 272);
			this->rankBox1->Multiline = true;
			this->rankBox1->Name = L"rankBox1";
			this->rankBox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->rankBox1->Size = System::Drawing::Size(146, 31);
			this->rankBox1->TabIndex = 10;
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
			this->label5->Size = System::Drawing::Size(57, 24);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Rank";
			// 
			// nameBox1
			// 
			this->nameBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->nameBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameBox1->Location = System::Drawing::Point(279, 115);
			this->nameBox1->Multiline = true;
			this->nameBox1->Name = L"nameBox1";
			this->nameBox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->nameBox1->Size = System::Drawing::Size(146, 31);
			this->nameBox1->TabIndex = 8;
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
			this->resetbtn1->Click += gcnew System::EventHandler(this, &Officers::resetbtn1_Click);
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
			this->closebtn1->Click += gcnew System::EventHandler(this, &Officers::closebtn1_Click);
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
			this->savebtn->Click += gcnew System::EventHandler(this, &Officers::savebtn_Click);
			// 
			// expBox1
			// 
			this->expBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->expBox1->Location = System::Drawing::Point(174, 362);
			this->expBox1->Multiline = true;
			this->expBox1->Name = L"expBox1";
			this->expBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->expBox1->Size = System::Drawing::Size(497, 102);
			this->expBox1->TabIndex = 6;
			// 
			// dateBox1
			// 
			this->dateBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateBox1->Location = System::Drawing::Point(279, 225);
			this->dateBox1->Name = L"dateBox1";
			this->dateBox1->Size = System::Drawing::Size(211, 25);
			this->dateBox1->TabIndex = 5;
			// 
			// idBox1
			// 
			this->idBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->idBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->idBox1->Location = System::Drawing::Point(279, 60);
			this->idBox1->Multiline = true;
			this->idBox1->Name = L"idBox1";
			this->idBox1->Size = System::Drawing::Size(146, 31);
			this->idBox1->TabIndex = 1;
			this->idBox1->TextChanged += gcnew System::EventHandler(this, &Officers::idBox1_TextChanged);
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
			this->label6->Size = System::Drawing::Size(205, 24);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Previous Experience";
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
			this->label4->Size = System::Drawing::Size(48, 24);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Age";
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
			this->label3->Size = System::Drawing::Size(65, 24);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Name";
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
			this->label2->Text = L"Officer ID";
			// 
			// viewpanel
			// 
			this->viewpanel->BackColor = System::Drawing::Color::Silver;
			this->viewpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"viewpanel.BackgroundImage")));
			this->viewpanel->Controls->Add(this->resultpnl);
			this->viewpanel->Controls->Add(this->viewheading);
			this->viewpanel->Controls->Add(this->resetbtn2);
			this->viewpanel->Controls->Add(this->searchbtn);
			this->viewpanel->Controls->Add(this->idBox2);
			this->viewpanel->Controls->Add(this->label12);
			this->viewpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->viewpanel->Location = System::Drawing::Point(0, 0);
			this->viewpanel->Name = L"viewpanel";
			this->viewpanel->Size = System::Drawing::Size(845, 504);
			this->viewpanel->TabIndex = 23;
			// 
			// resultpnl
			// 
			this->resultpnl->BackColor = System::Drawing::Color::Transparent;
			this->resultpnl->Controls->Add(this->rankBox2);
			this->resultpnl->Controls->Add(this->label13);
			this->resultpnl->Controls->Add(this->expBox2);
			this->resultpnl->Controls->Add(this->label10);
			this->resultpnl->Controls->Add(this->ageBox2);
			this->resultpnl->Controls->Add(this->label9);
			this->resultpnl->Controls->Add(this->closebtn2);
			this->resultpnl->Controls->Add(this->datebox2);
			this->resultpnl->Controls->Add(this->label8);
			this->resultpnl->Controls->Add(this->nameBox2);
			this->resultpnl->Controls->Add(this->label11);
			this->resultpnl->Location = System::Drawing::Point(0, 200);
			this->resultpnl->Name = L"resultpnl";
			this->resultpnl->Size = System::Drawing::Size(861, 290);
			this->resultpnl->TabIndex = 9;
			// 
			// rankBox2
			// 
			this->rankBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rankBox2->Location = System::Drawing::Point(171, 247);
			this->rankBox2->Multiline = true;
			this->rankBox2->Name = L"rankBox2";
			this->rankBox2->ReadOnly = true;
			this->rankBox2->Size = System::Drawing::Size(190, 37);
			this->rankBox2->TabIndex = 9;
			this->rankBox2->WordWrap = false;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(15, 250);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(59, 28);
			this->label13->TabIndex = 8;
			this->label13->Text = L"Rank";
			// 
			// expBox2
			// 
			this->expBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->expBox2->Location = System::Drawing::Point(452, 75);
			this->expBox2->Multiline = true;
			this->expBox2->Name = L"expBox2";
			this->expBox2->ReadOnly = true;
			this->expBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->expBox2->Size = System::Drawing::Size(358, 120);
			this->expBox2->TabIndex = 7;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(447, 29);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(233, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Previous Experience :";
			// 
			// ageBox2
			// 
			this->ageBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ageBox2->Location = System::Drawing::Point(171, 180);
			this->ageBox2->Multiline = true;
			this->ageBox2->Name = L"ageBox2";
			this->ageBox2->ReadOnly = true;
			this->ageBox2->Size = System::Drawing::Size(190, 37);
			this->ageBox2->TabIndex = 5;
			this->ageBox2->WordWrap = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(12, 180);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(49, 28);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Age";
			// 
			// closebtn2
			// 
			this->closebtn2->BackColor = System::Drawing::Color::White;
			this->closebtn2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closebtn2->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn2->FlatAppearance->BorderSize = 2;
			this->closebtn2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closebtn2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closebtn2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn2->Location = System::Drawing::Point(723, 236);
			this->closebtn2->Name = L"closebtn2";
			this->closebtn2->Size = System::Drawing::Size(110, 44);
			this->closebtn2->TabIndex = 11;
			this->closebtn2->Text = L"Close";
			this->closebtn2->UseVisualStyleBackColor = false;
			this->closebtn2->Click += gcnew System::EventHandler(this, &Officers::closebtn2_Click);
			// 
			// datebox2
			// 
			this->datebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox2->Location = System::Drawing::Point(171, 105);
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
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(15, 110);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(125, 28);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Date Joined";
			// 
			// nameBox2
			// 
			this->nameBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameBox2->Location = System::Drawing::Point(171, 32);
			this->nameBox2->Multiline = true;
			this->nameBox2->Name = L"nameBox2";
			this->nameBox2->ReadOnly = true;
			this->nameBox2->Size = System::Drawing::Size(190, 37);
			this->nameBox2->TabIndex = 1;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(12, 40);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(68, 28);
			this->label11->TabIndex = 0;
			this->label11->Text = L"Name";
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
			// resetbtn2
			// 
			this->resetbtn2->BackColor = System::Drawing::Color::White;
			this->resetbtn2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn2->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn2->FlatAppearance->BorderSize = 2;
			this->resetbtn2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->resetbtn2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn2->Location = System::Drawing::Point(711, 149);
			this->resetbtn2->Name = L"resetbtn2";
			this->resetbtn2->Size = System::Drawing::Size(122, 45);
			this->resetbtn2->TabIndex = 7;
			this->resetbtn2->Text = L"Reset";
			this->resetbtn2->UseVisualStyleBackColor = false;
			this->resetbtn2->Click += gcnew System::EventHandler(this, &Officers::resetbtn2_Click);
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
			this->searchbtn->Location = System::Drawing::Point(35, 149);
			this->searchbtn->Name = L"searchbtn";
			this->searchbtn->Size = System::Drawing::Size(122, 45);
			this->searchbtn->TabIndex = 7;
			this->searchbtn->Text = L"Search";
			this->searchbtn->UseVisualStyleBackColor = false;
			this->searchbtn->Click += gcnew System::EventHandler(this, &Officers::searchbtn_Click);
			// 
			// idBox2
			// 
			this->idBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->idBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->idBox2->Location = System::Drawing::Point(171, 85);
			this->idBox2->Multiline = true;
			this->idBox2->Name = L"idBox2";
			this->idBox2->Size = System::Drawing::Size(131, 38);
			this->idBox2->TabIndex = 1;
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
			this->label12->Size = System::Drawing::Size(123, 29);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Officer ID";
			// 
			// assignPanel
			// 
			this->assignPanel->BackColor = System::Drawing::Color::Silver;
			this->assignPanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"assignPanel.BackgroundImage")));
			this->assignPanel->Controls->Add(this->rolebox1);
			this->assignPanel->Controls->Add(this->savebtn2);
			this->assignPanel->Controls->Add(this->closeBtn4);
			this->assignPanel->Controls->Add(this->label1);
			this->assignPanel->Controls->Add(this->rankbox3);
			this->assignPanel->Controls->Add(this->idBox4);
			this->assignPanel->Controls->Add(this->label17);
			this->assignPanel->Controls->Add(this->label16);
			this->assignPanel->Controls->Add(this->label15);
			this->assignPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->assignPanel->Location = System::Drawing::Point(0, 0);
			this->assignPanel->Name = L"assignPanel";
			this->assignPanel->Size = System::Drawing::Size(845, 504);
			this->assignPanel->TabIndex = 25;
			// 
			// rolebox1
			// 
			this->rolebox1->FormattingEnabled = true;
			this->rolebox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Lead Officer", L"Detective", L"Forensics Team",
					L"Gunman"
			});
			this->rolebox1->Location = System::Drawing::Point(410, 279);
			this->rolebox1->Name = L"rolebox1";
			this->rolebox1->Size = System::Drawing::Size(131, 25);
			this->rolebox1->TabIndex = 12;
			// 
			// savebtn2
			// 
			this->savebtn2->BackColor = System::Drawing::Color::White;
			this->savebtn2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->savebtn2->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->savebtn2->FlatAppearance->BorderSize = 2;
			this->savebtn2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->savebtn2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->savebtn2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->savebtn2->Location = System::Drawing::Point(568, 433);
			this->savebtn2->Name = L"savebtn2";
			this->savebtn2->Size = System::Drawing::Size(122, 45);
			this->savebtn2->TabIndex = 11;
			this->savebtn2->Text = L"Save";
			this->savebtn2->UseVisualStyleBackColor = false;
			this->savebtn2->Click += gcnew System::EventHandler(this, &Officers::savebtn2_Click);
			// 
			// closeBtn4
			// 
			this->closeBtn4->BackColor = System::Drawing::Color::White;
			this->closeBtn4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closeBtn4->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closeBtn4->FlatAppearance->BorderSize = 2;
			this->closeBtn4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeBtn4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closeBtn4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closeBtn4->Location = System::Drawing::Point(696, 433);
			this->closeBtn4->Name = L"closeBtn4";
			this->closeBtn4->Size = System::Drawing::Size(122, 45);
			this->closeBtn4->TabIndex = 11;
			this->closeBtn4->Text = L"Close";
			this->closeBtn4->UseVisualStyleBackColor = false;
			this->closeBtn4->Click += gcnew System::EventHandler(this, &Officers::closeBtn4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(314, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(194, 45);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Assign Role";
			// 
			// rankbox3
			// 
			this->rankbox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rankbox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rankbox3->Location = System::Drawing::Point(410, 202);
			this->rankbox3->Multiline = true;
			this->rankbox3->Name = L"rankbox3";
			this->rankbox3->Size = System::Drawing::Size(131, 38);
			this->rankbox3->TabIndex = 1;
			// 
			// idBox4
			// 
			this->idBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->idBox4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->idBox4->Location = System::Drawing::Point(410, 137);
			this->idBox4->Multiline = true;
			this->idBox4->Name = L"idBox4";
			this->idBox4->Size = System::Drawing::Size(131, 38);
			this->idBox4->TabIndex = 1;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->BackColor = System::Drawing::Color::Transparent;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::Color::White;
			this->label17->Location = System::Drawing::Point(248, 273);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(128, 28);
			this->label17->TabIndex = 0;
			this->label17->Text = L"Choose Role";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->BackColor = System::Drawing::Color::Transparent;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(248, 202);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(136, 28);
			this->label16->TabIndex = 0;
			this->label16->Text = L"Current Rank";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Transparent;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(248, 137);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(105, 28);
			this->label15->TabIndex = 0;
			this->label15->Text = L"Officer ID";
			// 
			// Officers
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 17);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(845, 531);
			this->Controls->Add(this->assignPanel);
			this->Controls->Add(this->viewpanel);
			this->Controls->Add(this->removepanel);
			this->Controls->Add(this->addpanel);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->dbinfo);
			this->Controls->Add(this->ExitBtn);
			this->Controls->Add(this->aboutBtn);
			this->Controls->Add(this->assignBtn);
			this->Controls->Add(this->removebtn);
			this->Controls->Add(this->viewbtn);
			this->Controls->Add(this->addbtn);
			this->Controls->Add(this->heading);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Officers";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Officers";
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->addpanel->ResumeLayout(false);
			this->addpanel->PerformLayout();
			this->removepanel->ResumeLayout(false);
			this->removepanel->PerformLayout();
			this->viewpanel->ResumeLayout(false);
			this->viewpanel->PerformLayout();
			this->resultpnl->ResumeLayout(false);
			this->resultpnl->PerformLayout();
			this->assignPanel->ResumeLayout(false);
			this->assignPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void ExitBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Officers::Close(); 
}
private: System::Void aboutBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Officer's database is manipulated through this tab . Other Details are also Stored ", "Officers Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void dbinfo_Click(System::Object^ sender, System::EventArgs^ e) {
	if (isDbConnected == false)
	{
		MessageBox::Show("MYSQL Server is not installed on your system .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("MYSQL Server 8.0 .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
private: System::Void addbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	addpanel->Show(); 
}
private: System::Void viewbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	viewpanel->Show();
}
private: System::Void removebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	removepanel->Show(); 
}
private: System::Void assignBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	assignPanel->Show(); 
}
private: System::Void resetbtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	idBox1->Clear();
	nameBox1->Clear();
	dateBox1->ResetText();
	ageBox1->Clear();
	rankBox1->Clear();
	expBox1->Clear();
}
private: System::Void closebtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult msgbox;

	if (textChange == true)
	{
		msgbox = MessageBox::Show("Are you sure you want to exit without saving ? ", "SaveChanges", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (msgbox == System::Windows::Forms::DialogResult::Yes)
		{
			idBox1->Clear();
			nameBox1->Clear();
			dateBox1->ResetText();
			ageBox1->Clear();
			rankBox1->Clear();
			expBox1->Clear();
			addpanel->Hide();
		}
		else if (msgbox == System::Windows::Forms::DialogResult::No)
		{
			return;
		}
	}
	else {
		addpanel->Hide();
	}
}
private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	
	int officer_id , age;
	try
	{
		officer_id = System::Convert::ToInt16(idBox1->Text);
		age = System::Convert::ToInt16(ageBox1->Text);

		if (isDbConnected == true)
		{
			/*if (!idcheckdb(officer_id))
			{
				MessageBox::Show("Officer with this ID already Exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}*/
			AddDetailsDB(officer_id, nameBox1->Text, dateBox1->Text, age, rankBox1->Text, expBox1->Text);
		}
		else
		{
			adddetailcsv();
		}
	}
	catch (...)
	{
		MessageBox::Show("ID and Age can only be digits", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	MessageBox::Show("Details have been successfully saved.", "DialogBox", MessageBoxButtons::OK, MessageBoxIcon::Information);
	addpanel->Hide();
	textChange = false;

}
private: System::Void resetbtn2_Click(System::Object^ sender, System::EventArgs^ e) {
	idBox2->Clear();
	nameBox2->Clear();
	datebox2->ResetText();
	ageBox2->Clear();
	rankBox2->Clear();
	expBox2->Clear();
}
private: System::Void closebtn2_Click(System::Object^ sender, System::EventArgs^ e) {
	idBox2->Clear();
	nameBox2->Clear();
	datebox2->ResetText();
	ageBox2->Clear();
	rankBox2->Clear();
	expBox2->Clear();
	viewpanel->Hide(); 
}
private: System::Void closeBtn3_Click(System::Object^ sender, System::EventArgs^ e) {
	idBox3->Clear();
	removepanel->Hide(); 
}
private: System::Void removebtn3_Click(System::Object^ sender, System::EventArgs^ e) {
	if (idBox3->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invalid Input", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(idBox3->Text);

		if (isDbConnected)
		{
			removedetaildatabase(id);
		}
		else
		{
			removedetailcsv(id);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		idBox3->Clear();
	}
}
private: System::Void searchbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (idBox2->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invalid Input", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(idBox2->Text);

		if (isDbConnected)
		{
			viewdetailsdatabase(id);
		}
		else
		{
			viewdetailscsv(id);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		idBox2->Clear();
	}
}
private: System::Void closeBtn4_Click(System::Object^ sender, System::EventArgs^ e) {
	assignPanel->Hide(); 

}
private: System::Void savebtn2_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Role has been assigned to the officer .", "Assign Role", MessageBoxButtons::OK, MessageBoxIcon::Information);
	idBox4->Clear();
	rankbox3->Clear(); 
	rolebox1->ResetText(); 

}
private: System::Void idBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textChange = true; 
}
};
}
