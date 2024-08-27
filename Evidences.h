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
	/// Summary for Evidences
	/// </summary>
	public ref class Evidences : public System::Windows::Forms::Form
	{
	public:
		MYSQL* currentconn;
		bool isDbConnected;
		bool textChange = false;
		Evidences(void)
		{
			InitializeComponent();
		}
		Evidences(MYSQL* conn, bool dbconn)
		{
			InitializeComponent();
			addpanel->Hide();
			viewpanel->Hide();
			removepanel->Hide();

			currentconn = conn;
			isDbConnected = dbconn; 

			if (isDbConnected)
			{
				datalabel->ForeColor = System::Drawing::Color::LawnGreen;
				label6->ForeColor = System::Drawing::Color::Red;
			}
			else
			{
				datalabel->ForeColor = System::Drawing::Color::Red;
				label6->ForeColor = System::Drawing::Color::LawnGreen;
			}

		}
		bool idCheckDb(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss;
			ss << "select LabelNo from cms.evidence where LabelNo = " << id;
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
		void addDetailDatabase()
		{
			int labelno, itemsno;
			std::string type, caseno, desc; 

			labelno = System::Convert::ToInt16(labelbox1->Text); 
			itemsno = System::Convert::ToInt16(numberbox1->Value); 

			msclr::interop::marshal_context converter;

			type = converter.marshal_as<std::string>(typebox1->Text);
			caseno = converter.marshal_as<std::string>(casebox1->Text);
			desc = converter.marshal_as<std::string>(descbox1->Text);

			std::stringstream ss; 

			ss << "insert into cms.evidence (LabelNo, ItemsNo, Type, CaseNo, Description) values ( " << labelno << "," << itemsno << ", '" << type << "','" << caseno << "','" << desc <<"')"; 
			std::string query = ss.str();
			char* arrayqueue;
			arrayqueue = &query[0]; 

			if (!mysql_query(currentconn, arrayqueue))
			{
				MessageBox::Show("Success");

			}
			else
			{
				MessageBox::Show("Error");

			}
		}
		void addDetailCSV()
		{
			int labelno, itemsno;
			std::string type, caseno, desc;

			labelno = System::Convert::ToInt16(labelbox1->Text);
			itemsno = System::Convert::ToInt16(numberbox1->Value);

			msclr::interop::marshal_context converter;

			type = converter.marshal_as<std::string>(typebox1->Text);
			caseno = converter.marshal_as<std::string>(casebox1->Text);
			desc = converter.marshal_as<std::string>(descbox1->Text);

			std::fstream file1; 

			file1.open("Evidence.csv", std::ios::out | std::ios::app); 
			file1 << labelno << "," << itemsno << "," << type << "," << caseno << "," << desc << std::endl; 
			file1.close(); 
		}
		void viewDetailDatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;

			std::string itemno, type, caseno, desc; 
			String^ ItemNo, ^ Type, ^ CaseNo, ^ Desc; 

			std::stringstream ss; 
			ss << "select * from cms.evidence where LabelNo = " << id;
			std::string query = ss.str();
			char* arrayqueue;
			arrayqueue = &query[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("No Evidence Exists with this LabelNo", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					resultpnl->Show(); 
					itemno = row[1];
					type = row[2];
					caseno = row[3]; 
					desc = row[4];

					ItemNo = gcnew String(itemno.c_str()); 
					Type = gcnew String(type.c_str());
					CaseNo = gcnew String(caseno.c_str());
					Desc = gcnew String(desc.c_str());

					numberbox2->Text = ItemNo; 
					typebox2->Text = Type; 
					casebox2->Text = CaseNo; 
					descbox2->Text = Desc; 
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void viewDetailCSV(int id)
		{
			int id2;
			std::fstream file1;
			file1.open("Evidence.csv", std::ios::in);

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
					MessageBox::Show("Evidence with this LabelNo does not exist. ", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				if (id == id2)
				{
					resultpnl->Show(); 
					std::string itemno, type, caseno, desc;
					getline(ss, itemno, ','); 
					getline(ss, type, ',');
					getline(ss, caseno, ','); 
					getline(ss, desc, ','); 

					String^ ItemNo, ^ Type, ^ CaseNo, ^ Desc;

					ItemNo = gcnew String(itemno.c_str());
					Type = gcnew String(type.c_str());
					CaseNo = gcnew String(caseno.c_str());
					Desc = gcnew String(desc.c_str());

					numberbox2->Text = ItemNo;
					typebox2->Text = Type;
					casebox2->Text = CaseNo;
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
		void removeDetailDatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss, delquery;
			char* arrayqueue;

			ss << "select * from cms.evidence where LabelNo = " << id;
			std::string q = ss.str();
			arrayqueue = &q[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("LabelNo does not exist.", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					delquery << "delete from cms.evidence where LabelNo = " << id;
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
		void removeDetailCsv(int id)
		{
			int id2= NULL ; bool idFound;
			std::fstream file1, file2; 
			file1.open("Evidence.csv", std::ios::in);
			file2.open("EvidenceNew.csv", std::ios::out);

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
					std::string itemno, type, caseno, desc;
					getline(ss, itemno, ',');
					getline(ss, type, ',');
					getline(ss, caseno, ',');
					getline(ss, desc, ',');

					file2 << id << "," << itemno << "," << type << "," << caseno << "," << desc << std::endl;
					continue; 
				}
			}
			if(idFound)
			{
				MessageBox::Show("Record Successfully Deleted", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
			MessageBox::Show("LabelNo does not exist.", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			file1.close();
			file2.close();

			remove("Evidence.csv");
			rename("EvidenceNew.csv", "Evidence.csv");
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Evidences()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ heading;
	private: System::Windows::Forms::Button^ removebtn;
	private: System::Windows::Forms::Button^ viewbtn;
	private: System::Windows::Forms::Button^ createbtn;
	private: System::Windows::Forms::Button^ dbinfo;
	private: System::Windows::Forms::Button^ abt_Btn;
	private: System::Windows::Forms::Button^ Exitbtn;
	private: System::Windows::Forms::Panel^ addpanel;
	private: System::Windows::Forms::NumericUpDown^ numberbox1;
	private: System::Windows::Forms::TextBox^ descbox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ typebox1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ casebox1;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ resetbtn1;
	private: System::Windows::Forms::Button^ closebtn1;
	private: System::Windows::Forms::Button^ savebtn;
	private: System::Windows::Forms::TextBox^ labelbox1;
	private: System::Windows::Forms::Label^ label;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ viewpanel;
	private: System::Windows::Forms::Panel^ resultpnl;
	private: System::Windows::Forms::TextBox^ descbox2;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ casebox2;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ typebox2;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ numberbox2;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ viewheading;
	private: System::Windows::Forms::Button^ resetbtn;
	private: System::Windows::Forms::Button^ searchbtn;
	private: System::Windows::Forms::TextBox^ labelbox2;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Button^ closebtn;
	private: System::Windows::Forms::Panel^ bottonPnl;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ datalabel;
	private: System::Windows::Forms::Panel^ removepanel;
	private: System::Windows::Forms::Button^ closebtn3;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Button^ remov_evdbtn;
	private: System::Windows::Forms::TextBox^ labelbox3;
	private: System::Windows::Forms::Label^ label15;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Evidences::typeid));
			this->heading = (gcnew System::Windows::Forms::Label());
			this->removebtn = (gcnew System::Windows::Forms::Button());
			this->viewbtn = (gcnew System::Windows::Forms::Button());
			this->createbtn = (gcnew System::Windows::Forms::Button());
			this->dbinfo = (gcnew System::Windows::Forms::Button());
			this->abt_Btn = (gcnew System::Windows::Forms::Button());
			this->Exitbtn = (gcnew System::Windows::Forms::Button());
			this->addpanel = (gcnew System::Windows::Forms::Panel());
			this->numberbox1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->descbox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->typebox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->casebox1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->resetbtn1 = (gcnew System::Windows::Forms::Button());
			this->closebtn1 = (gcnew System::Windows::Forms::Button());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->labelbox1 = (gcnew System::Windows::Forms::TextBox());
			this->label = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->viewpanel = (gcnew System::Windows::Forms::Panel());
			this->resultpnl = (gcnew System::Windows::Forms::Panel());
			this->descbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->casebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->typebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->numberbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->resetbtn = (gcnew System::Windows::Forms::Button());
			this->searchbtn = (gcnew System::Windows::Forms::Button());
			this->labelbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->closebtn = (gcnew System::Windows::Forms::Button());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->removepanel = (gcnew System::Windows::Forms::Panel());
			this->closebtn3 = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->remov_evdbtn = (gcnew System::Windows::Forms::Button());
			this->labelbox3 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->addpanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberbox1))->BeginInit();
			this->viewpanel->SuspendLayout();
			this->resultpnl->SuspendLayout();
			this->bottonPnl->SuspendLayout();
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
			this->heading->Location = System::Drawing::Point(329, 29);
			this->heading->Name = L"heading";
			this->heading->Size = System::Drawing::Size(203, 59);
			this->heading->TabIndex = 19;
			this->heading->Text = L"Evidence";
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
			this->removebtn->Location = System::Drawing::Point(70, 363);
			this->removebtn->Name = L"removebtn";
			this->removebtn->Size = System::Drawing::Size(166, 39);
			this->removebtn->TabIndex = 20;
			this->removebtn->Text = L"Remove Evidence";
			this->removebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->removebtn->UseVisualStyleBackColor = false;
			this->removebtn->Click += gcnew System::EventHandler(this, &Evidences::removebtn_Click);
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
			this->viewbtn->Location = System::Drawing::Point(70, 269);
			this->viewbtn->Name = L"viewbtn";
			this->viewbtn->Size = System::Drawing::Size(166, 39);
			this->viewbtn->TabIndex = 21;
			this->viewbtn->Text = L"View Evidence";
			this->viewbtn->UseVisualStyleBackColor = false;
			this->viewbtn->Click += gcnew System::EventHandler(this, &Evidences::viewbtn_Click);
			// 
			// createbtn
			// 
			this->createbtn->BackColor = System::Drawing::Color::DarkGray;
			this->createbtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->createbtn->FlatAppearance->BorderSize = 0;
			this->createbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->createbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->createbtn->ForeColor = System::Drawing::Color::Black;
			this->createbtn->Location = System::Drawing::Point(70, 175);
			this->createbtn->Name = L"createbtn";
			this->createbtn->Size = System::Drawing::Size(166, 39);
			this->createbtn->TabIndex = 22;
			this->createbtn->Text = L"Create Evidence";
			this->createbtn->UseVisualStyleBackColor = false;
			this->createbtn->Click += gcnew System::EventHandler(this, &Evidences::createbtn_Click);
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
			this->dbinfo->Location = System::Drawing::Point(580, 269);
			this->dbinfo->Name = L"dbinfo";
			this->dbinfo->Size = System::Drawing::Size(166, 39);
			this->dbinfo->TabIndex = 23;
			this->dbinfo->Text = L"Database Info";
			this->dbinfo->UseVisualStyleBackColor = false;
			this->dbinfo->Click += gcnew System::EventHandler(this, &Evidences::dbinfo_Click);
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
			this->abt_Btn->Location = System::Drawing::Point(580, 175);
			this->abt_Btn->Name = L"abt_Btn";
			this->abt_Btn->Size = System::Drawing::Size(166, 39);
			this->abt_Btn->TabIndex = 24;
			this->abt_Btn->Text = L"About";
			this->abt_Btn->UseVisualStyleBackColor = false;
			this->abt_Btn->Click += gcnew System::EventHandler(this, &Evidences::abt_Btn_Click);
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
			this->Exitbtn->Location = System::Drawing::Point(580, 363);
			this->Exitbtn->Name = L"Exitbtn";
			this->Exitbtn->Size = System::Drawing::Size(166, 39);
			this->Exitbtn->TabIndex = 25;
			this->Exitbtn->Text = L"Exit";
			this->Exitbtn->UseVisualStyleBackColor = false;
			this->Exitbtn->Click += gcnew System::EventHandler(this, &Evidences::Exitbtn_Click);
			// 
			// addpanel
			// 
			this->addpanel->BackColor = System::Drawing::Color::Silver;
			this->addpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addpanel.BackgroundImage")));
			this->addpanel->Controls->Add(this->numberbox1);
			this->addpanel->Controls->Add(this->descbox1);
			this->addpanel->Controls->Add(this->label1);
			this->addpanel->Controls->Add(this->typebox1);
			this->addpanel->Controls->Add(this->label7);
			this->addpanel->Controls->Add(this->casebox1);
			this->addpanel->Controls->Add(this->label5);
			this->addpanel->Controls->Add(this->resetbtn1);
			this->addpanel->Controls->Add(this->closebtn1);
			this->addpanel->Controls->Add(this->savebtn);
			this->addpanel->Controls->Add(this->labelbox1);
			this->addpanel->Controls->Add(this->label);
			this->addpanel->Controls->Add(this->label2);
			this->addpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->addpanel->Location = System::Drawing::Point(0, 0);
			this->addpanel->Name = L"addpanel";
			this->addpanel->Size = System::Drawing::Size(860, 544);
			this->addpanel->TabIndex = 26;
			// 
			// numberbox1
			// 
			this->numberbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numberbox1->Location = System::Drawing::Point(280, 146);
			this->numberbox1->Name = L"numberbox1";
			this->numberbox1->Size = System::Drawing::Size(120, 25);
			this->numberbox1->TabIndex = 15;
			// 
			// descbox1
			// 
			this->descbox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->descbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descbox1->Location = System::Drawing::Point(277, 363);
			this->descbox1->Multiline = true;
			this->descbox1->Name = L"descbox1";
			this->descbox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->descbox1->Size = System::Drawing::Size(335, 92);
			this->descbox1->TabIndex = 14;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(48, 360);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(138, 25);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Description:";
			// 
			// typebox1
			// 
			this->typebox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->typebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->typebox1->Location = System::Drawing::Point(277, 209);
			this->typebox1->Multiline = true;
			this->typebox1->Name = L"typebox1";
			this->typebox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->typebox1->Size = System::Drawing::Size(146, 31);
			this->typebox1->TabIndex = 12;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(46, 212);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(190, 24);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Type Of Evidence :";
			// 
			// casebox1
			// 
			this->casebox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->casebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->casebox1->Location = System::Drawing::Point(280, 283);
			this->casebox1->Multiline = true;
			this->casebox1->Name = L"casebox1";
			this->casebox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->casebox1->Size = System::Drawing::Size(146, 31);
			this->casebox1->TabIndex = 10;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(49, 283);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(102, 24);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Case No :";
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
			this->resetbtn1->Location = System::Drawing::Point(707, 222);
			this->resetbtn1->Name = L"resetbtn1";
			this->resetbtn1->Size = System::Drawing::Size(118, 58);
			this->resetbtn1->TabIndex = 7;
			this->resetbtn1->Text = L"Reset";
			this->resetbtn1->UseVisualStyleBackColor = false;
			this->resetbtn1->Click += gcnew System::EventHandler(this, &Evidences::resetbtn1_Click);
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
			this->closebtn1->Location = System::Drawing::Point(707, 132);
			this->closebtn1->Name = L"closebtn1";
			this->closebtn1->Size = System::Drawing::Size(118, 58);
			this->closebtn1->TabIndex = 7;
			this->closebtn1->Text = L"Close";
			this->closebtn1->UseVisualStyleBackColor = false;
			this->closebtn1->Click += gcnew System::EventHandler(this, &Evidences::closebtn1_Click);
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
			this->savebtn->Location = System::Drawing::Point(707, 51);
			this->savebtn->Name = L"savebtn";
			this->savebtn->Size = System::Drawing::Size(118, 58);
			this->savebtn->TabIndex = 7;
			this->savebtn->Text = L"Save";
			this->savebtn->UseVisualStyleBackColor = false;
			this->savebtn->Click += gcnew System::EventHandler(this, &Evidences::savebtn_Click);
			// 
			// labelbox1
			// 
			this->labelbox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelbox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelbox1->Location = System::Drawing::Point(280, 72);
			this->labelbox1->Multiline = true;
			this->labelbox1->Name = L"labelbox1";
			this->labelbox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->labelbox1->Size = System::Drawing::Size(146, 31);
			this->labelbox1->TabIndex = 1;
			this->labelbox1->TextChanged += gcnew System::EventHandler(this, &Evidences::labelbox1_TextChanged);
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->BackColor = System::Drawing::Color::Transparent;
			this->label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label->ForeColor = System::Drawing::Color::White;
			this->label->Location = System::Drawing::Point(49, 141);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(137, 24);
			this->label->TabIndex = 0;
			this->label->Text = L"No. Of Items :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(49, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(215, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Evidence\'s Label No. ";
			// 
			// viewpanel
			// 
			this->viewpanel->BackColor = System::Drawing::Color::Silver;
			this->viewpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"viewpanel.BackgroundImage")));
			this->viewpanel->Controls->Add(this->resultpnl);
			this->viewpanel->Controls->Add(this->viewheading);
			this->viewpanel->Controls->Add(this->resetbtn);
			this->viewpanel->Controls->Add(this->searchbtn);
			this->viewpanel->Controls->Add(this->labelbox2);
			this->viewpanel->Controls->Add(this->label12);
			this->viewpanel->Controls->Add(this->closebtn);
			this->viewpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->viewpanel->Location = System::Drawing::Point(0, 0);
			this->viewpanel->Name = L"viewpanel";
			this->viewpanel->Size = System::Drawing::Size(860, 544);
			this->viewpanel->TabIndex = 27;
			// 
			// resultpnl
			// 
			this->resultpnl->BackColor = System::Drawing::Color::Transparent;
			this->resultpnl->Controls->Add(this->descbox2);
			this->resultpnl->Controls->Add(this->label10);
			this->resultpnl->Controls->Add(this->casebox2);
			this->resultpnl->Controls->Add(this->label9);
			this->resultpnl->Controls->Add(this->typebox2);
			this->resultpnl->Controls->Add(this->label8);
			this->resultpnl->Controls->Add(this->numberbox2);
			this->resultpnl->Controls->Add(this->label11);
			this->resultpnl->Location = System::Drawing::Point(0, 200);
			this->resultpnl->Name = L"resultpnl";
			this->resultpnl->Size = System::Drawing::Size(861, 290);
			this->resultpnl->TabIndex = 9;
			// 
			// descbox2
			// 
			this->descbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descbox2->Location = System::Drawing::Point(459, 134);
			this->descbox2->Multiline = true;
			this->descbox2->Name = L"descbox2";
			this->descbox2->ReadOnly = true;
			this->descbox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descbox2->Size = System::Drawing::Size(367, 99);
			this->descbox2->TabIndex = 7;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(459, 85);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(144, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Description :";
			// 
			// casebox2
			// 
			this->casebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->casebox2->Location = System::Drawing::Point(222, 228);
			this->casebox2->Multiline = true;
			this->casebox2->Name = L"casebox2";
			this->casebox2->ReadOnly = true;
			this->casebox2->Size = System::Drawing::Size(190, 37);
			this->casebox2->TabIndex = 5;
			this->casebox2->WordWrap = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(12, 225);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(103, 30);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Case No:";
			// 
			// typebox2
			// 
			this->typebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->typebox2->Location = System::Drawing::Point(222, 158);
			this->typebox2->Multiline = true;
			this->typebox2->Name = L"typebox2";
			this->typebox2->ReadOnly = true;
			this->typebox2->Size = System::Drawing::Size(190, 37);
			this->typebox2->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(12, 156);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(204, 30);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Type Of Evidence :";
			// 
			// numberbox2
			// 
			this->numberbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numberbox2->Location = System::Drawing::Point(222, 88);
			this->numberbox2->Multiline = true;
			this->numberbox2->Name = L"numberbox2";
			this->numberbox2->ReadOnly = true;
			this->numberbox2->Size = System::Drawing::Size(190, 37);
			this->numberbox2->TabIndex = 1;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(12, 85);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(144, 30);
			this->label11->TabIndex = 0;
			this->label11->Text = L"No. Of Items";
			// 
			// viewheading
			// 
			this->viewheading->AutoSize = true;
			this->viewheading->BackColor = System::Drawing::Color::Transparent;
			this->viewheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewheading->ForeColor = System::Drawing::Color::White;
			this->viewheading->Location = System::Drawing::Point(309, 23);
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
			this->resetbtn->Location = System::Drawing::Point(717, 104);
			this->resetbtn->Name = L"resetbtn";
			this->resetbtn->Size = System::Drawing::Size(122, 45);
			this->resetbtn->TabIndex = 7;
			this->resetbtn->Text = L"Reset";
			this->resetbtn->UseVisualStyleBackColor = false;
			this->resetbtn->Click += gcnew System::EventHandler(this, &Evidences::resetbtn_Click);
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
			this->searchbtn->Click += gcnew System::EventHandler(this, &Evidences::searchbtn_Click);
			// 
			// labelbox2
			// 
			this->labelbox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelbox2->Location = System::Drawing::Point(171, 90);
			this->labelbox2->Multiline = true;
			this->labelbox2->Name = L"labelbox2";
			this->labelbox2->Size = System::Drawing::Size(131, 38);
			this->labelbox2->TabIndex = 1;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(28, 95);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(126, 29);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Label No.";
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
			this->closebtn->Location = System::Drawing::Point(717, 493);
			this->closebtn->Name = L"closebtn";
			this->closebtn->Size = System::Drawing::Size(122, 44);
			this->closebtn->TabIndex = 11;
			this->closebtn->Text = L"Close";
			this->closebtn->UseVisualStyleBackColor = false;
			this->closebtn->Click += gcnew System::EventHandler(this, &Evidences::closebtn_Click);
			// 
			// bottonPnl
			// 
			this->bottonPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->bottonPnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->bottonPnl->Controls->Add(this->label6);
			this->bottonPnl->Controls->Add(this->datalabel);
			this->bottonPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottonPnl->Location = System::Drawing::Point(0, 544);
			this->bottonPnl->Name = L"bottonPnl";
			this->bottonPnl->Size = System::Drawing::Size(860, 27);
			this->bottonPnl->TabIndex = 28;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(1, 4);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(159, 19);
			this->label6->TabIndex = 5;
			this->label6->Text = L"WINDOWS FILE SYSTEM";
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
			// removepanel
			// 
			this->removepanel->BackColor = System::Drawing::Color::Silver;
			this->removepanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"removepanel.BackgroundImage")));
			this->removepanel->Controls->Add(this->closebtn3);
			this->removepanel->Controls->Add(this->label14);
			this->removepanel->Controls->Add(this->remov_evdbtn);
			this->removepanel->Controls->Add(this->labelbox3);
			this->removepanel->Controls->Add(this->label15);
			this->removepanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->removepanel->Location = System::Drawing::Point(0, 0);
			this->removepanel->Name = L"removepanel";
			this->removepanel->Size = System::Drawing::Size(860, 544);
			this->removepanel->TabIndex = 29;
			// 
			// closebtn3
			// 
			this->closebtn3->BackColor = System::Drawing::Color::White;
			this->closebtn3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closebtn3->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn3->FlatAppearance->BorderSize = 2;
			this->closebtn3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closebtn3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closebtn3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closebtn3->Location = System::Drawing::Point(719, 397);
			this->closebtn3->Name = L"closebtn3";
			this->closebtn3->Size = System::Drawing::Size(122, 45);
			this->closebtn3->TabIndex = 11;
			this->closebtn3->Text = L"Close";
			this->closebtn3->UseVisualStyleBackColor = false;
			this->closebtn3->Click += gcnew System::EventHandler(this, &Evidences::closebtn3_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(309, 32);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(273, 45);
			this->label14->TabIndex = 10;
			this->label14->Text = L"Remove Evidence";
			// 
			// remov_evdbtn
			// 
			this->remov_evdbtn->BackColor = System::Drawing::Color::White;
			this->remov_evdbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->remov_evdbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->remov_evdbtn->FlatAppearance->BorderSize = 2;
			this->remov_evdbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->remov_evdbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->remov_evdbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->remov_evdbtn->Location = System::Drawing::Point(456, 233);
			this->remov_evdbtn->Name = L"remov_evdbtn";
			this->remov_evdbtn->Size = System::Drawing::Size(122, 45);
			this->remov_evdbtn->TabIndex = 7;
			this->remov_evdbtn->Text = L"Remove";
			this->remov_evdbtn->UseVisualStyleBackColor = false;
			this->remov_evdbtn->Click += gcnew System::EventHandler(this, &Evidences::remov_evdbtn_Click);
			// 
			// labelbox3
			// 
			this->labelbox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelbox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelbox3->Location = System::Drawing::Point(443, 149);
			this->labelbox3->Multiline = true;
			this->labelbox3->Name = L"labelbox3";
			this->labelbox3->Size = System::Drawing::Size(131, 38);
			this->labelbox3->TabIndex = 1;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Transparent;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(118, 151);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(308, 33);
			this->label15->TabIndex = 0;
			this->label15->Text = L"Evidence\'s Label No.";
			// 
			// Evidences
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(860, 571);
			this->Controls->Add(this->removepanel);
			this->Controls->Add(this->viewpanel);
			this->Controls->Add(this->addpanel);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->dbinfo);
			this->Controls->Add(this->abt_Btn);
			this->Controls->Add(this->Exitbtn);
			this->Controls->Add(this->removebtn);
			this->Controls->Add(this->viewbtn);
			this->Controls->Add(this->createbtn);
			this->Controls->Add(this->heading);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Evidences";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Evidences";
			this->addpanel->ResumeLayout(false);
			this->addpanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberbox1))->EndInit();
			this->viewpanel->ResumeLayout(false);
			this->viewpanel->PerformLayout();
			this->resultpnl->ResumeLayout(false);
			this->resultpnl->PerformLayout();
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->removepanel->ResumeLayout(false);
			this->removepanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void createbtn_Click(System::Object^ sender, System::EventArgs^ e) {
		addpanel->Show(); 
	}
private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	try
	{
		int labelno = System::Convert::ToInt16(labelbox1->Text);
		if (isDbConnected)
		{
			if (!idCheckDb(labelno))
			{
				MessageBox::Show("Evidence with this Label No already exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			addDetailDatabase(); 
		}
		else
		{
			addDetailCSV(); 
		}
	}
	catch (...)
	{
		MessageBox::Show("ID and Suspects can only be digits", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	MessageBox::Show("Details have been successfully saved.", "DialogBox", MessageBoxButtons::OK, MessageBoxIcon::Information);
	addpanel->Hide();
	textChange = false;
}
private: System::Void labelbox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textChange = true;
}
private: System::Void closebtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult msgbox;

	if (textChange == true)
	{
		msgbox = MessageBox::Show("Are you sure you want to exit without saving ? ", "SaveChanges", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (msgbox == System::Windows::Forms::DialogResult::Yes)
		{
			labelbox1->Clear();
			numberbox1->ResetText();
			typebox1->Clear();
			casebox1->Clear();
			descbox1->Clear();
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
private: System::Void resetbtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	labelbox1->Clear(); 
	numberbox1->ResetText();
	typebox1->Clear();
	casebox1->Clear();
	descbox1->Clear(); 
}
private: System::Void Exitbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Evidences::Close(); 
}
private: System::Void viewbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	viewpanel->Show(); 
}
private: System::Void resetbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	labelbox2->Clear();
	numberbox2->ResetText();
	typebox2->Clear();
	casebox2->Clear();
	descbox2->Clear();
}
private: System::Void closebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	labelbox2->Clear();
	numberbox2->ResetText();
	typebox2->Clear();
	casebox2->Clear();
	descbox2->Clear();
	viewpanel->Hide();
}
private: System::Void searchbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (labelbox2->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invaid ID", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(labelbox2->Text);
		if (isDbConnected)
		{
			viewDetailDatabase(id); 
		}
		else
		{
			viewDetailCSV(id); 
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		labelbox2->Clear();
	}
}

private: System::Void removebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	removepanel->Show(); 
}
private: System::Void closebtn3_Click(System::Object^ sender, System::EventArgs^ e) {
	labelbox3->Clear();
	removepanel->Hide(); 
}
private: System::Void remov_evdbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (labelbox3->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invaid ID", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(labelbox3->Text);
		if (isDbConnected)
		{
			removeDetailDatabase(id);
		}
		else
		{
			removeDetailCsv(id);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		labelbox2->Clear();
	}
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
private: System::Void abt_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("This section stores all kinds of digital evidence related to cases entered .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
};
}
