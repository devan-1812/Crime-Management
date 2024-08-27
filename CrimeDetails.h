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
	
	/// <summary>
	/// Summary for CrimeDetails
	/// </summary>
	public ref class CrimeDetails : public System::Windows::Forms::Form
	{
	public : 
	MYSQL* currentconn;
	bool isDbConnected;
	bool textChange=false; 
	private: System::Windows::Forms::Label^ csv_Label;
	public:

	private: System::Windows::Forms::Button^ abt_Btn;

	private: System::Windows::Forms::Button^ resetbtn;
	private: System::Windows::Forms::Button^ addClbtn;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ resetbtn1;
	private: System::Windows::Forms::Button^ dbinfo;
	public:
		CrimeDetails(void)
		{
			InitializeComponent();
			panel1->Hide(); 
			resultpnl->Hide();
			pnlviewdata->Hide();
			Remove_rcd_pnl->Hide();
			//
			//TODO: Add the constructor code here
			//
		}
		CrimeDetails(MYSQL* db, bool isconn)
		{
			InitializeComponent();
			panel1->Hide();
			resultpnl->Hide();
			pnlviewdata->Hide();
			Remove_rcd_pnl->Hide();
			currentconn = db; 
			isDbConnected = isconn;

			if (isDbConnected)
			{
				mysql_Label->ForeColor = System::Drawing::Color::LawnGreen; 
				csv_Label->ForeColor = System::Drawing::Color::Red;
			}
			else
			{
				mysql_Label->ForeColor = System::Drawing::Color::Red;
				csv_Label->ForeColor = System::Drawing::Color::LawnGreen;
			}
		}
		void resetpnl()
		{
			crimeIdBox->Clear(); 
			typeBox->ResetText();
			datebox->ResetText();
			descBox->Clear();
			susepectsBox->ResetText();
		}
		bool idCheckDb(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss;
			ss << "select ID from cms.crimedetails where ID = " << id;
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
		void addDetailsDatabase(int ID, String^ Type, String^ Description, String^ Date, int totalSuspects)
		{
			std::string type, desc, date;
			//this marshal converter converts textboxes datatype to normal string datatype 
			msclr::interop::marshal_context converter;
			type = converter.marshal_as<std::string>(typeBox->Text);
			desc = converter.marshal_as<std::string>(descBox->Text);
			date = converter.marshal_as<std::string>(datebox->Text);

			ID = System::Convert::ToInt16(crimeIdBox->Text);
			totalSuspects = System::Convert::ToInt16(susepectsBox->Value); 

			std::stringstream ss;
			ss << "insert into cms.crimedetails (ID, Type, Description, Date, totalSuspects) values (" << ID << ", '" << type << "', '" << desc << "' , '" << date << "', " << totalSuspects << " )";
			
			std::string query = ss.str();
			char* arrayquery;
			arrayquery = &query[0]; 

			if (mysql_query(currentconn, arrayquery))
			{
				MessageBox::Show("Error");
			}
			else
			{
				MessageBox::Show("Success");
			}
		}
		void addDetailsCSV(int ID, String^ Type, String^ Description, String^ Date, int totalSuspects)
		{
			std::string type, desc, date; 
			msclr::interop::marshal_context converter;
			type = converter.marshal_as<std::string>(typeBox->Text);
			desc = converter.marshal_as<std::string>(descBox->Text);
			date = converter.marshal_as<std::string>(datebox->Text);
			
			std::fstream file1; 

			file1.open("CrimeDetails.csv", std::ios::out | std::ios::app); 
			file1 << ID << "," << type << "," << desc << "," << date << "," << totalSuspects << std::endl ;
			file1.close(); 
		}
		void viewDetailsDatabase(int searchid)
		{
			MYSQL_ROW row; 
			MYSQL_RES* res; 
			std::string type, desc, date, suspects;
			std::stringstream ss; 
			String^ Type, ^ Date, ^ Desc, ^ Suspects;

			ss << "select * from cms.crimedetails where id = " << searchid ; 
			std::string query = ss.str(); 
			char* arrayqueue; 
			arrayqueue = &query[0]; 

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("No Record Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					resultpnl->Show();
					type = row[1]; 
					desc = row[2]; 
					date = row[3]; 
					suspects = row[4]; 

					Type = gcnew String(type.c_str()); 
					Date = gcnew String(date.c_str()); 
					Desc = gcnew String(desc.c_str()); 
					Suspects = gcnew String(suspects.c_str()); 

					typ_inp_txtbox->Text = Type;
					sus_inp_txtbox->Text = Suspects; 
					dat_inp_txtbox->Text = Date;
					des_inp_txt_box->Text = Desc; 
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void ViewDetailsCSV(int id)
		{
			int id2; 
			std::fstream file1;
			file1.open("CrimeDetails.csv", std::ios::in);

			while (file1.good())
			{
				std::string line, word;
				std::getline(file1, line);   // take input from file1 , store it in line 
				std::stringstream ss(line);
				std::getline(ss, word, ',');   

				try
				{
					id2 = std::stoi(word);
				}
				catch (...)
				{
					MessageBox::Show("No Record Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break; 
				}
				if (id == id2)
				{
					resultpnl->Show();
					std::string type, desc, day, month, year, suspects;
					std::getline(ss, type, ',');
					std::getline(ss, desc, ',');
					std::getline(ss, day, ',');
					std::getline(ss, month, ',');
					std::getline(ss, year, ',');
					std::getline(ss, suspects, ',');
					std::string date = day + month + year; 
					String^ Type, ^ Date, ^ Desc, ^ Suspects;
					Type = gcnew String(type.c_str());
					Date = gcnew String(date.c_str());
					Desc = gcnew String(desc.c_str());
					Suspects = gcnew String(suspects.c_str());

					typ_inp_txtbox->Text = Type;
					sus_inp_txtbox->Text = Suspects;
					dat_inp_txtbox->Text = Date;
					des_inp_txt_box->Text = Desc;
					break;
				}
				else
				{
					continue; 
				}
			}
			file1.close();
		}

		void removefromDatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss, delquery; 
			char* arrayqueue; 

			ss << "select * from cms.crimedetails where id = " <<  id ; 
			std::string q = ss.str();
			arrayqueue = &q[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);

				if (row == NULL)
				{
					MessageBox::Show("No Record Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					delquery << "delete from cms.crimedetails where id = " << id;
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
		void removefromCsv(int id)
		{
			std::fstream file1,file2;
			file1.open("CrimeDetails.csv", std::ios::in);
			file2.open("CrimeNew.csv", std::ios::out);
			int id2=NULL; bool idFound = false; 

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
					std::string type, desc, day, month, year, suspects;
					std::getline(ss, type, ',');
					std::getline(ss, desc, ',');
					std::getline(ss, day, ',');
					std::getline(ss, month, ',');
					std::getline(ss, year, ',');
					std::getline(ss, suspects, ',');

					file2 << id2 << "," << type << "," << desc << "," << day << "," << month << "," << year << "," << suspects << std::endl;
					continue; 
				}
			}
			if (idFound)
			{
				MessageBox::Show("Record Successfully Deleted", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("No Record Exists with this ID", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			file1.close();
			file2.close();

			remove("CrimeDetails.csv");
			rename("CrimeNew.csv", "CrimeDetails.csv");
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CrimeDetails()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ addbtn;
	private: System::Windows::Forms::Button^ viewbtn;
	private: System::Windows::Forms::Button^ removebtn;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ mainheading;
	private: System::Windows::Forms::TextBox^ crimeIdBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ typeBox;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ descBox;
	private: System::Windows::Forms::DateTimePicker^ datebox;
	private: System::Windows::Forms::NumericUpDown^ susepectsBox;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ savebtn;
	private: System::Windows::Forms::Button^ Exitbtn;
	private: System::Windows::Forms::Panel^ pnlviewdata;
	private: System::Windows::Forms::Button^ searchbtn;
	private: System::Windows::Forms::TextBox^ IDtxtbox;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ viewheading;

	private: System::Windows::Forms::Panel^ resultpnl;
	private: System::Windows::Forms::TextBox^ des_inp_txt_box;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ dat_inp_txtbox;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ sus_inp_txtbox;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ typ_inp_txtbox;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Panel^ Remove_rcd_pnl;
	private: System::Windows::Forms::Button^ close_rcd_btn;

	private: System::Windows::Forms::Label^ remomv_Heading;
	private: System::Windows::Forms::Button^ remove_rcd_btn;
	private: System::Windows::Forms::TextBox^ IDtxtbox_2;

	private: System::Windows::Forms::Label^ c_id_lbl;
private: System::Windows::Forms::Label^ mysql_Label;





private: System::Windows::Forms::Panel^ bottonPnl;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CrimeDetails::typeid));
			this->addbtn = (gcnew System::Windows::Forms::Button());
			this->viewbtn = (gcnew System::Windows::Forms::Button());
			this->removebtn = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->resetbtn1 = (gcnew System::Windows::Forms::Button());
			this->addClbtn = (gcnew System::Windows::Forms::Button());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->descBox = (gcnew System::Windows::Forms::TextBox());
			this->datebox = (gcnew System::Windows::Forms::DateTimePicker());
			this->susepectsBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->typeBox = (gcnew System::Windows::Forms::ComboBox());
			this->crimeIdBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Remove_rcd_pnl = (gcnew System::Windows::Forms::Panel());
			this->close_rcd_btn = (gcnew System::Windows::Forms::Button());
			this->remomv_Heading = (gcnew System::Windows::Forms::Label());
			this->remove_rcd_btn = (gcnew System::Windows::Forms::Button());
			this->IDtxtbox_2 = (gcnew System::Windows::Forms::TextBox());
			this->c_id_lbl = (gcnew System::Windows::Forms::Label());
			this->pnlviewdata = (gcnew System::Windows::Forms::Panel());
			this->resultpnl = (gcnew System::Windows::Forms::Panel());
			this->des_inp_txt_box = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->dat_inp_txtbox = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->sus_inp_txtbox = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->typ_inp_txtbox = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->resetbtn = (gcnew System::Windows::Forms::Button());
			this->searchbtn = (gcnew System::Windows::Forms::Button());
			this->IDtxtbox = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->mainheading = (gcnew System::Windows::Forms::Label());
			this->Exitbtn = (gcnew System::Windows::Forms::Button());
			this->mysql_Label = (gcnew System::Windows::Forms::Label());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->csv_Label = (gcnew System::Windows::Forms::Label());
			this->abt_Btn = (gcnew System::Windows::Forms::Button());
			this->dbinfo = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->susepectsBox))->BeginInit();
			this->Remove_rcd_pnl->SuspendLayout();
			this->pnlviewdata->SuspendLayout();
			this->resultpnl->SuspendLayout();
			this->bottonPnl->SuspendLayout();
			this->SuspendLayout();
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
			this->addbtn->Location = System::Drawing::Point(69, 128);
			this->addbtn->Name = L"addbtn";
			this->addbtn->Size = System::Drawing::Size(166, 39);
			this->addbtn->TabIndex = 0;
			this->addbtn->Text = L"Add Data";
			this->addbtn->UseVisualStyleBackColor = false;
			this->addbtn->Click += gcnew System::EventHandler(this, &CrimeDetails::addbtn_Click);
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
			this->viewbtn->Location = System::Drawing::Point(69, 228);
			this->viewbtn->Name = L"viewbtn";
			this->viewbtn->Size = System::Drawing::Size(166, 39);
			this->viewbtn->TabIndex = 0;
			this->viewbtn->Text = L"View Records";
			this->viewbtn->UseVisualStyleBackColor = false;
			this->viewbtn->Click += gcnew System::EventHandler(this, &CrimeDetails::viewbtn_Click);
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
			this->removebtn->Location = System::Drawing::Point(69, 328);
			this->removebtn->Name = L"removebtn";
			this->removebtn->Size = System::Drawing::Size(166, 39);
			this->removebtn->TabIndex = 0;
			this->removebtn->Text = L"Remove\r\n\r\n";
			this->removebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->removebtn->UseVisualStyleBackColor = false;
			this->removebtn->Click += gcnew System::EventHandler(this, &CrimeDetails::removebtn_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Silver;
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->Controls->Add(this->resetbtn1);
			this->panel1->Controls->Add(this->addClbtn);
			this->panel1->Controls->Add(this->savebtn);
			this->panel1->Controls->Add(this->descBox);
			this->panel1->Controls->Add(this->datebox);
			this->panel1->Controls->Add(this->susepectsBox);
			this->panel1->Controls->Add(this->typeBox);
			this->panel1->Controls->Add(this->crimeIdBox);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(861, 570);
			this->panel1->TabIndex = 1;
			// 
			// resetbtn1
			// 
			this->resetbtn1->BackColor = System::Drawing::Color::White;
			this->resetbtn1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn1->FlatAppearance->BorderSize = 2;
			this->resetbtn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetbtn1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn1->Location = System::Drawing::Point(697, 231);
			this->resetbtn1->Name = L"resetbtn1";
			this->resetbtn1->Size = System::Drawing::Size(118, 58);
			this->resetbtn1->TabIndex = 9;
			this->resetbtn1->Text = L"Reset";
			this->resetbtn1->UseVisualStyleBackColor = false;
			this->resetbtn1->Click += gcnew System::EventHandler(this, &CrimeDetails::resetbtn1_Click);
			// 
			// addClbtn
			// 
			this->addClbtn->BackColor = System::Drawing::Color::White;
			this->addClbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->addClbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->addClbtn->FlatAppearance->BorderSize = 2;
			this->addClbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addClbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addClbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->addClbtn->Location = System::Drawing::Point(697, 146);
			this->addClbtn->Name = L"addClbtn";
			this->addClbtn->Size = System::Drawing::Size(118, 58);
			this->addClbtn->TabIndex = 8;
			this->addClbtn->Text = L"Close";
			this->addClbtn->UseVisualStyleBackColor = false;
			this->addClbtn->Click += gcnew System::EventHandler(this, &CrimeDetails::addClbtn_Click_1);
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
			this->savebtn->Location = System::Drawing::Point(697, 61);
			this->savebtn->Name = L"savebtn";
			this->savebtn->Size = System::Drawing::Size(118, 58);
			this->savebtn->TabIndex = 7;
			this->savebtn->Text = L"Save";
			this->savebtn->UseVisualStyleBackColor = false;
			this->savebtn->Click += gcnew System::EventHandler(this, &CrimeDetails::savebtn_Click);
			// 
			// descBox
			// 
			this->descBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descBox->Location = System::Drawing::Point(129, 319);
			this->descBox->Multiline = true;
			this->descBox->Name = L"descBox";
			this->descBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descBox->Size = System::Drawing::Size(598, 178);
			this->descBox->TabIndex = 6;
			// 
			// datebox
			// 
			this->datebox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox->Location = System::Drawing::Point(129, 215);
			this->datebox->Name = L"datebox";
			this->datebox->Size = System::Drawing::Size(228, 25);
			this->datebox->TabIndex = 5;
			// 
			// susepectsBox
			// 
			this->susepectsBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->susepectsBox->Location = System::Drawing::Point(129, 152);
			this->susepectsBox->Name = L"susepectsBox";
			this->susepectsBox->Size = System::Drawing::Size(124, 25);
			this->susepectsBox->TabIndex = 4;
			// 
			// typeBox
			// 
			this->typeBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->typeBox->FormattingEnabled = true;
			this->typeBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Property Crime", L"White Collar Crime", L"Organized Crime" });
			this->typeBox->Location = System::Drawing::Point(129, 97);
			this->typeBox->Name = L"typeBox";
			this->typeBox->Size = System::Drawing::Size(124, 25);
			this->typeBox->TabIndex = 3;
			// 
			// crimeIdBox
			// 
			this->crimeIdBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->crimeIdBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crimeIdBox->Location = System::Drawing::Point(128, 36);
			this->crimeIdBox->Name = L"crimeIdBox";
			this->crimeIdBox->Size = System::Drawing::Size(124, 25);
			this->crimeIdBox->TabIndex = 1;
			this->crimeIdBox->TextChanged += gcnew System::EventHandler(this, &CrimeDetails::crimeIdBox_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(18, 268);
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
			this->label5->Location = System::Drawing::Point(18, 215);
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
			this->label4->Location = System::Drawing::Point(18, 153);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(95, 24);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Suspects";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(18, 95);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 24);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Type";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(18, 37);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Crime ID";
			// 
			// Remove_rcd_pnl
			// 
			this->Remove_rcd_pnl->BackColor = System::Drawing::Color::Silver;
			this->Remove_rcd_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Remove_rcd_pnl.BackgroundImage")));
			this->Remove_rcd_pnl->Controls->Add(this->close_rcd_btn);
			this->Remove_rcd_pnl->Controls->Add(this->remomv_Heading);
			this->Remove_rcd_pnl->Controls->Add(this->remove_rcd_btn);
			this->Remove_rcd_pnl->Controls->Add(this->IDtxtbox_2);
			this->Remove_rcd_pnl->Controls->Add(this->c_id_lbl);
			this->Remove_rcd_pnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Remove_rcd_pnl->Location = System::Drawing::Point(0, 0);
			this->Remove_rcd_pnl->Name = L"Remove_rcd_pnl";
			this->Remove_rcd_pnl->Size = System::Drawing::Size(861, 543);
			this->Remove_rcd_pnl->TabIndex = 6;
			// 
			// close_rcd_btn
			// 
			this->close_rcd_btn->BackColor = System::Drawing::Color::White;
			this->close_rcd_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->close_rcd_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->close_rcd_btn->FlatAppearance->BorderSize = 2;
			this->close_rcd_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->close_rcd_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->close_rcd_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->close_rcd_btn->Location = System::Drawing::Point(693, 394);
			this->close_rcd_btn->Name = L"close_rcd_btn";
			this->close_rcd_btn->Size = System::Drawing::Size(122, 45);
			this->close_rcd_btn->TabIndex = 11;
			this->close_rcd_btn->Text = L"Close";
			this->close_rcd_btn->UseVisualStyleBackColor = false;
			this->close_rcd_btn->Click += gcnew System::EventHandler(this, &CrimeDetails::close_rcd_btn_Click);
			// 
			// remomv_Heading
			// 
			this->remomv_Heading->AutoSize = true;
			this->remomv_Heading->BackColor = System::Drawing::Color::Transparent;
			this->remomv_Heading->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->remomv_Heading->ForeColor = System::Drawing::Color::White;
			this->remomv_Heading->Location = System::Drawing::Point(309, 32);
			this->remomv_Heading->Name = L"remomv_Heading";
			this->remomv_Heading->Size = System::Drawing::Size(246, 45);
			this->remomv_Heading->TabIndex = 10;
			this->remomv_Heading->Text = L"Remove Record";
			// 
			// remove_rcd_btn
			// 
			this->remove_rcd_btn->BackColor = System::Drawing::Color::White;
			this->remove_rcd_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->remove_rcd_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->remove_rcd_btn->FlatAppearance->BorderSize = 2;
			this->remove_rcd_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->remove_rcd_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->remove_rcd_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->remove_rcd_btn->Location = System::Drawing::Point(368, 235);
			this->remove_rcd_btn->Name = L"remove_rcd_btn";
			this->remove_rcd_btn->Size = System::Drawing::Size(122, 45);
			this->remove_rcd_btn->TabIndex = 7;
			this->remove_rcd_btn->Text = L"Remove";
			this->remove_rcd_btn->UseVisualStyleBackColor = false;
			this->remove_rcd_btn->Click += gcnew System::EventHandler(this, &CrimeDetails::remove_rcd_btn_Click);
			// 
			// IDtxtbox_2
			// 
			this->IDtxtbox_2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->IDtxtbox_2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IDtxtbox_2->Location = System::Drawing::Point(368, 152);
			this->IDtxtbox_2->Multiline = true;
			this->IDtxtbox_2->Name = L"IDtxtbox_2";
			this->IDtxtbox_2->Size = System::Drawing::Size(131, 38);
			this->IDtxtbox_2->TabIndex = 1;
			// 
			// c_id_lbl
			// 
			this->c_id_lbl->AutoSize = true;
			this->c_id_lbl->BackColor = System::Drawing::Color::Transparent;
			this->c_id_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->c_id_lbl->ForeColor = System::Drawing::Color::White;
			this->c_id_lbl->Location = System::Drawing::Point(195, 156);
			this->c_id_lbl->Name = L"c_id_lbl";
			this->c_id_lbl->Size = System::Drawing::Size(137, 29);
			this->c_id_lbl->TabIndex = 0;
			this->c_id_lbl->Text = L"Crime ID =";
			// 
			// pnlviewdata
			// 
			this->pnlviewdata->BackColor = System::Drawing::Color::Silver;
			this->pnlviewdata->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlviewdata.BackgroundImage")));
			this->pnlviewdata->Controls->Add(this->resultpnl);
			this->pnlviewdata->Controls->Add(this->viewheading);
			this->pnlviewdata->Controls->Add(this->button1);
			this->pnlviewdata->Controls->Add(this->resetbtn);
			this->pnlviewdata->Controls->Add(this->searchbtn);
			this->pnlviewdata->Controls->Add(this->IDtxtbox);
			this->pnlviewdata->Controls->Add(this->label11);
			this->pnlviewdata->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlviewdata->Location = System::Drawing::Point(0, 0);
			this->pnlviewdata->Name = L"pnlviewdata";
			this->pnlviewdata->Size = System::Drawing::Size(861, 543);
			this->pnlviewdata->TabIndex = 5;
			// 
			// resultpnl
			// 
			this->resultpnl->BackColor = System::Drawing::Color::Transparent;
			this->resultpnl->Controls->Add(this->des_inp_txt_box);
			this->resultpnl->Controls->Add(this->label10);
			this->resultpnl->Controls->Add(this->dat_inp_txtbox);
			this->resultpnl->Controls->Add(this->label9);
			this->resultpnl->Controls->Add(this->sus_inp_txtbox);
			this->resultpnl->Controls->Add(this->label8);
			this->resultpnl->Controls->Add(this->typ_inp_txtbox);
			this->resultpnl->Controls->Add(this->label7);
			this->resultpnl->Location = System::Drawing::Point(22, 201);
			this->resultpnl->Name = L"resultpnl";
			this->resultpnl->Size = System::Drawing::Size(825, 290);
			this->resultpnl->TabIndex = 9;
			// 
			// des_inp_txt_box
			// 
			this->des_inp_txt_box->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->des_inp_txt_box->Location = System::Drawing::Point(418, 100);
			this->des_inp_txt_box->Multiline = true;
			this->des_inp_txt_box->Name = L"des_inp_txt_box";
			this->des_inp_txt_box->ReadOnly = true;
			this->des_inp_txt_box->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->des_inp_txt_box->Size = System::Drawing::Size(331, 120);
			this->des_inp_txt_box->TabIndex = 7;
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
			// dat_inp_txtbox
			// 
			this->dat_inp_txtbox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dat_inp_txtbox->Location = System::Drawing::Point(158, 205);
			this->dat_inp_txtbox->Multiline = true;
			this->dat_inp_txtbox->Name = L"dat_inp_txtbox";
			this->dat_inp_txtbox->ReadOnly = true;
			this->dat_inp_txtbox->Size = System::Drawing::Size(190, 37);
			this->dat_inp_txtbox->TabIndex = 5;
			this->dat_inp_txtbox->WordWrap = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(51, 200);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(62, 30);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Date";
			// 
			// sus_inp_txtbox
			// 
			this->sus_inp_txtbox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sus_inp_txtbox->Location = System::Drawing::Point(158, 124);
			this->sus_inp_txtbox->Multiline = true;
			this->sus_inp_txtbox->Name = L"sus_inp_txtbox";
			this->sus_inp_txtbox->ReadOnly = true;
			this->sus_inp_txtbox->Size = System::Drawing::Size(190, 37);
			this->sus_inp_txtbox->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(51, 120);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(104, 30);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Suspects";
			// 
			// typ_inp_txtbox
			// 
			this->typ_inp_txtbox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->typ_inp_txtbox->Location = System::Drawing::Point(158, 52);
			this->typ_inp_txtbox->Multiline = true;
			this->typ_inp_txtbox->Name = L"typ_inp_txtbox";
			this->typ_inp_txtbox->ReadOnly = true;
			this->typ_inp_txtbox->Size = System::Drawing::Size(190, 37);
			this->typ_inp_txtbox->TabIndex = 1;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(51, 52);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(63, 30);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Type";
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
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::White;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button1->Location = System::Drawing::Point(722, 492);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(122, 45);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Close";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &CrimeDetails::button1_Click);
			// 
			// resetbtn
			// 
			this->resetbtn->BackColor = System::Drawing::Color::White;
			this->resetbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn->FlatAppearance->BorderSize = 2;
			this->resetbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn->Location = System::Drawing::Point(180, 153);
			this->resetbtn->Name = L"resetbtn";
			this->resetbtn->Size = System::Drawing::Size(122, 45);
			this->resetbtn->TabIndex = 7;
			this->resetbtn->Text = L"Reset";
			this->resetbtn->UseVisualStyleBackColor = false;
			this->resetbtn->Click += gcnew System::EventHandler(this, &CrimeDetails::resetbtn_Click);
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
			this->searchbtn->Location = System::Drawing::Point(35, 153);
			this->searchbtn->Name = L"searchbtn";
			this->searchbtn->Size = System::Drawing::Size(122, 45);
			this->searchbtn->TabIndex = 7;
			this->searchbtn->Text = L"Search";
			this->searchbtn->UseVisualStyleBackColor = false;
			this->searchbtn->Click += gcnew System::EventHandler(this, &CrimeDetails::searchbtn_Click_1);
			// 
			// IDtxtbox
			// 
			this->IDtxtbox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->IDtxtbox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IDtxtbox->Location = System::Drawing::Point(171, 85);
			this->IDtxtbox->Multiline = true;
			this->IDtxtbox->Name = L"IDtxtbox";
			this->IDtxtbox->Size = System::Drawing::Size(131, 38);
			this->IDtxtbox->TabIndex = 1;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(28, 90);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(137, 29);
			this->label11->TabIndex = 0;
			this->label11->Text = L"Crime ID =";
			// 
			// mainheading
			// 
			this->mainheading->AutoSize = true;
			this->mainheading->BackColor = System::Drawing::Color::Transparent;
			this->mainheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mainheading->ForeColor = System::Drawing::Color::White;
			this->mainheading->Location = System::Drawing::Point(282, 32);
			this->mainheading->Name = L"mainheading";
			this->mainheading->Size = System::Drawing::Size(293, 59);
			this->mainheading->TabIndex = 2;
			this->mainheading->Text = L"Crime Details";
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
			this->Exitbtn->Location = System::Drawing::Point(588, 328);
			this->Exitbtn->Name = L"Exitbtn";
			this->Exitbtn->Size = System::Drawing::Size(166, 39);
			this->Exitbtn->TabIndex = 4;
			this->Exitbtn->Text = L"Exit";
			this->Exitbtn->UseVisualStyleBackColor = false;
			this->Exitbtn->Click += gcnew System::EventHandler(this, &CrimeDetails::Exitbtn_Click);
			// 
			// mysql_Label
			// 
			this->mysql_Label->AutoSize = true;
			this->mysql_Label->BackColor = System::Drawing::Color::Transparent;
			this->mysql_Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mysql_Label->ForeColor = System::Drawing::Color::White;
			this->mysql_Label->Location = System::Drawing::Point(792, 4);
			this->mysql_Label->Name = L"mysql_Label";
			this->mysql_Label->Size = System::Drawing::Size(55, 19);
			this->mysql_Label->TabIndex = 5;
			this->mysql_Label->Text = L"MYSQL";
			// 
			// bottonPnl
			// 
			this->bottonPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->bottonPnl->Controls->Add(this->csv_Label);
			this->bottonPnl->Controls->Add(this->mysql_Label);
			this->bottonPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottonPnl->Location = System::Drawing::Point(0, 543);
			this->bottonPnl->Name = L"bottonPnl";
			this->bottonPnl->Size = System::Drawing::Size(861, 27);
			this->bottonPnl->TabIndex = 6;
			// 
			// csv_Label
			// 
			this->csv_Label->AutoSize = true;
			this->csv_Label->BackColor = System::Drawing::Color::Transparent;
			this->csv_Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->csv_Label->ForeColor = System::Drawing::Color::White;
			this->csv_Label->Location = System::Drawing::Point(1, 4);
			this->csv_Label->Name = L"csv_Label";
			this->csv_Label->Size = System::Drawing::Size(159, 19);
			this->csv_Label->TabIndex = 5;
			this->csv_Label->Text = L"WINDOWS FILE SYSTEM";
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
			this->abt_Btn->Location = System::Drawing::Point(588, 128);
			this->abt_Btn->Name = L"abt_Btn";
			this->abt_Btn->Size = System::Drawing::Size(166, 39);
			this->abt_Btn->TabIndex = 4;
			this->abt_Btn->Text = L"About";
			this->abt_Btn->UseVisualStyleBackColor = false;
			this->abt_Btn->Click += gcnew System::EventHandler(this, &CrimeDetails::abt_Btn_Click);
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
			this->dbinfo->Location = System::Drawing::Point(588, 223);
			this->dbinfo->Name = L"dbinfo";
			this->dbinfo->Size = System::Drawing::Size(166, 39);
			this->dbinfo->TabIndex = 4;
			this->dbinfo->Text = L"Database Info";
			this->dbinfo->UseVisualStyleBackColor = false;
			this->dbinfo->Click += gcnew System::EventHandler(this, &CrimeDetails::dbinfo_Click);
			// 
			// CrimeDetails
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(861, 570);
			this->Controls->Add(this->pnlviewdata);
			this->Controls->Add(this->Remove_rcd_pnl);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->mainheading);
			this->Controls->Add(this->removebtn);
			this->Controls->Add(this->viewbtn);
			this->Controls->Add(this->addbtn);
			this->Controls->Add(this->dbinfo);
			this->Controls->Add(this->abt_Btn);
			this->Controls->Add(this->Exitbtn);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"CrimeDetails";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CrimeDetails";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->susepectsBox))->EndInit();
			this->Remove_rcd_pnl->ResumeLayout(false);
			this->Remove_rcd_pnl->PerformLayout();
			this->pnlviewdata->ResumeLayout(false);
			this->pnlviewdata->PerformLayout();
			this->resultpnl->ResumeLayout(false);
			this->resultpnl->PerformLayout();
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void addbtn_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Show();

	}

	private: System::Void viewbtn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		panel1->Hide();
		pnlviewdata->Show();
	}

	/*private: System::Void searchbtn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		searchpnl->Show();
	}*/
	private: System::Void searchbtn_Click_1(System::Object^ sender, System::EventArgs^ e) 
	{
		if (IDtxtbox->Text == "")
		{
			MessageBox::Show("This field requires data.", "Invalid Input", MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		try
		{
			int id = System::Convert::ToInt16(IDtxtbox->Text); 
			if (isDbConnected == true)
			{
				viewDetailsDatabase(id);
			}
			else
			{
				ViewDetailsCSV(id); 
			}
		}
		catch (...)
		{
			MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
			IDtxtbox->Clear();
		}
	}


private: System::Void Exitbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	CrimeDetails::Close();
}

private: System::Void closebtn_Click(System::Object^ sender, System::EventArgs^ e) {

	IDtxtbox->Clear(); 
	typ_inp_txtbox->Clear();
	sus_inp_txtbox->Clear();
	dat_inp_txtbox->Clear();
	des_inp_txt_box->Clear(); 

	resultpnl->Hide();
	pnlviewdata->Hide();
}


private: System::Void removebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	panel1->Hide();
	pnlviewdata->Hide();
	resultpnl->Hide();
	Remove_rcd_pnl->Show();
}

private: System::Void remove_rcd_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (IDtxtbox_2->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invalid ID", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(IDtxtbox_2->Text); 
		if (isDbConnected == true)
		{
			removefromDatabase(id);
		}
		else
		{
			removefromCsv(id);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		IDtxtbox->Clear();
	}
	
}

private: System::Void close_rcd_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Remove_rcd_pnl->Hide();
}

private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	int id, sus; 
	try
	{
		id = System::Convert::ToInt16(crimeIdBox->Text);
		sus = System::Convert::ToInt16(susepectsBox->Value);
		if (isDbConnected == true)
		{
			if (!idCheckDb(id))
			{
				MessageBox::Show("A record with this Crime ID already exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			addDetailsDatabase(id, typeBox->Text, descBox->Text, datebox->Text, sus);
		}
		else
		{
			addDetailsCSV(id, typeBox->Text, descBox->Text, datebox->Text, sus);
		}
	}
	catch(...)
	{
		MessageBox::Show("ID and Suspects can only be digits", "Incorrect Input", MessageBoxButtons::OK,		 MessageBoxIcon::Error);
		return;
	}
	MessageBox::Show("Details have been successfully saved.", "DialogBox", MessageBoxButtons::OK, MessageBoxIcon::Information);
	panel1->Hide(); 
	textChange = false; 

}
private: System::Void abt_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("This Tab Stores the info of various crime across the city. Each detail is distinguished by its unique Crime ID . Other Details are also Stored ", "CrimeDetails Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void dbinfo_Click(System::Object^ sender, System::EventArgs^ e) {

	if (isDbConnected == false)
	{
		MessageBox::Show("MYSQL Server is not installed on your system .", "Database Info", MessageBoxButtons::OK , MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("MYSQL Server 8.0 .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
private: System::Void addClbtn_Click(System::Object^ sender, System::EventArgs^ e) {	
}
private: System::Void crimeIdBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textChange = true; 
}

private: System::Void resetbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	IDtxtbox->Clear();
	typ_inp_txtbox->Clear();
	sus_inp_txtbox->Clear();
	dat_inp_txtbox->Clear();
	des_inp_txt_box->Clear();
}

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	IDtxtbox->Clear();
	typ_inp_txtbox->Clear();
	sus_inp_txtbox->Clear();
	dat_inp_txtbox->Clear();
	des_inp_txt_box->Clear();
	pnlviewdata->Hide(); 
}
private: System::Void addClbtn_Click_1(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult msgbox;

	if (textChange == true)
	{
		msgbox = MessageBox::Show("Are you sure you want to exit without saving ? ", "SaveChanges", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (msgbox == System::Windows::Forms::DialogResult::Yes)
		{
			resetpnl(); 
			panel1->Hide();

		}
		else if (msgbox == System::Windows::Forms::DialogResult::No)
		{
			return;
		}
	}
	else {
		panel1->Hide();
	}
}
private: System::Void resetbtn1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	crimeIdBox->Clear();
	typeBox->ResetText();
	susepectsBox->ResetText();
	descBox->Clear();
}

};
}
