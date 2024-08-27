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
	/// Summary for FIR
	/// </summary>
	public ref class FIR : public System::Windows::Forms::Form
	{
	private:
		MYSQL* currentconn;
		bool isDbConnected;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Button^ resetbtn1;
		   bool textChange = false;
	public:
		FIR(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			setpanel->Hide();
			viewpanel->Hide();
			resultpnl->Hide();
			removepanel->Hide();
		}
		FIR(MYSQL* db, bool isconn)
		{
			InitializeComponent();
			setpanel->Hide();
			viewpanel->Hide();
			resultpnl->Hide();
			removepanel->Hide();
			currentconn = db; 
			isDbConnected = isconn; 

			if (isDbConnected)
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
		bool IDcheckDb(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss;
			ss << "select firNo from cms.fir where firNo = " << id;
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
		void addDetailsDatabase(int fir_no, int case_no , String^ Date, String^Time, String^ Desc)
		{
			msclr::interop::marshal_context converter;
			std::string date, time, desc; 

			date = converter.marshal_as<std::string>(datebox1->Text);
			time = converter.marshal_as<std::string>(timebox1->Text);
			desc = converter.marshal_as<std::string>(descBox1->Text);

			std::stringstream ss; 
			ss << "insert into cms.fir (firNo, caseNo, Date, Time, Description) values ( " << fir_no << "," << case_no << ", '" << date << "' , '" << time << "' , '" << desc << "' )";
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
		void addDetailCsv(int fir_no, int case_no, String^ Date, String^ Time, String^ Desc)
		{
			std::fstream file1; 
			msclr::interop::marshal_context converter;
			std::string date, time, desc;
			date = converter.marshal_as<std::string>(datebox1->Text);
			time = converter.marshal_as<std::string>(timebox1->Text);
			desc = converter.marshal_as<std::string>(descBox1->Text);

			file1.open("FIR.csv", std::ios::out | std::ios::app);
			file1 << fir_no << "," << case_no << "," << date << "," << time << "," << desc << std::endl;
			file1.close(); 
 		}
		void viewDetailDatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::string caseno, date, time, desc;
			String^ Date, ^ Time, ^ Desc, ^CaseNo; 

			std::stringstream ss; 
			ss << "select * from cms.fir where firNo = " << id; 
			std::string query; 
			query = ss.str();
			char* arrayqueue; 
			arrayqueue = &query[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					MessageBox::Show("No Record Exists with this FIRNo", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					resultpnl->Show(); 
					caseno = row[1];
					date = row[2]; 
					time = row[3]; 
					desc = row[4]; 

					CaseNo = gcnew String(caseno.c_str());
					Date = gcnew String(date.c_str());
					Time = gcnew String(time.c_str());
					Desc= gcnew String(desc.c_str());

					casebox2->Text = CaseNo; 
					datebox2->Text = Date;
					timebox2->Text = Time;
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
			file1.open("FIR.csv", std::ios::in);
		
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
					MessageBox::Show("No FIR with this ID exists ", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				if (id == id2)
				{
					resultpnl->Show(); 
					std::string caseno, date, day, time, desc;
					std::getline(ss, caseno, ',');
					std::getline(ss, day, ',');
					std::getline(ss, date, ',');
					std::getline(ss, time, ',');
					std::getline(ss, desc, ',');

					std::string finaldate = date + day; 

					String^ Date, ^ Time, ^ Desc, ^ CaseNo;
					CaseNo = gcnew String(caseno.c_str());
					Date = gcnew String(finaldate.c_str());
					Time = gcnew String(time.c_str());
					Desc = gcnew String(desc.c_str());

					casebox2->Text = CaseNo;
					datebox2->Text = Date;
					timebox2->Text = Time;
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

			ss << "select * from cms.fir where firNo = " << id; 
			std::string q = ss.str(); 
			arrayqueue = &q[0];

			if (!mysql_query(currentconn, arrayqueue))
			{
				res = mysql_store_result(currentconn);
				row = mysql_fetch_row(res);

				if (row == NULL)
				{
					MessageBox::Show("No FIR Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
				{
					delquery << "delete from cms.fir where firNo = " << id; 
					std::string d = delquery.str();
					char* delarrayqueue;
					delarrayqueue = &d[0];
					mysql_query(currentconn, delarrayqueue); 
					mysql_commit(currentconn);
					MessageBox::Show("FIR Deleted Successfully", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void removeDetailCSV(int id)
		{
			std::fstream file1, file2;
			file1.open("FIR.csv", std::ios::in);
			file2.open("FIRNew.csv", std::ios::out);
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
					std::string caseno, date, day, time, desc;
					std::getline(ss, caseno, ',');
					std::getline(ss, day, ',');
					std::getline(ss, date, ',');
					std::getline(ss, time, ',');
					std::getline(ss, desc, ','); 

					file2 << id2 << "," << caseno << "," << day << "," << date << "," << time << "," << desc << std::endl; 
					break;
				}
			}
			if (idFound==true)
			{
				MessageBox::Show("FIR Successfully Deleted", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("No FIR Exists with this ID", "Remove Details", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			file1.close(); 
			file2.close();

			remove("FIR.csv");
			rename("FIRNew.csv", "FIR.csv"); 
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FIR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ bottonPnl;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ datalabel;
	private: System::Windows::Forms::Label^ mainheading;
	private: System::Windows::Forms::Button^ removebtn;
	private: System::Windows::Forms::Button^ viewbtn;
	private: System::Windows::Forms::Button^ setbtn;
	private: System::Windows::Forms::Button^ dbinfo;
	private: System::Windows::Forms::Button^ abt_Btn;
	private: System::Windows::Forms::Button^ Exitbtn;
	private: System::Windows::Forms::Panel^ setpanel;
	private: System::Windows::Forms::TextBox^ timebox1;
	private: System::Windows::Forms::TextBox^ casebox1;
	private: System::Windows::Forms::Button^ setClbtn;
	private: System::Windows::Forms::Button^ savebtn;
	private: System::Windows::Forms::TextBox^ descBox1;
	private: System::Windows::Forms::DateTimePicker^ datebox1;

	private: System::Windows::Forms::TextBox^ FIR_Box1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ viewpanel;

	private: System::Windows::Forms::Panel^ resultpnl;
	private: System::Windows::Forms::TextBox^ descbox2;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ timebox2;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ datebox2;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ casebox2;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ viewheading;
	private: System::Windows::Forms::Button^ resetbtn;
	private: System::Windows::Forms::Button^ searchbtn;
	private: System::Windows::Forms::TextBox^ FIR_Box2;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Button^ closebtn;
	private: System::Windows::Forms::Panel^ removepanel;
	private: System::Windows::Forms::Button^ close_rcd_btn;
	private: System::Windows::Forms::Label^ Heading;
	private: System::Windows::Forms::Button^ remove_rcd_btn;
	private: System::Windows::Forms::TextBox^ FIR_Box3;
	private: System::Windows::Forms::Label^ fir_lbl;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FIR::typeid));
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->mainheading = (gcnew System::Windows::Forms::Label());
			this->removebtn = (gcnew System::Windows::Forms::Button());
			this->viewbtn = (gcnew System::Windows::Forms::Button());
			this->setbtn = (gcnew System::Windows::Forms::Button());
			this->dbinfo = (gcnew System::Windows::Forms::Button());
			this->abt_Btn = (gcnew System::Windows::Forms::Button());
			this->Exitbtn = (gcnew System::Windows::Forms::Button());
			this->setpanel = (gcnew System::Windows::Forms::Panel());
			this->timebox1 = (gcnew System::Windows::Forms::TextBox());
			this->casebox1 = (gcnew System::Windows::Forms::TextBox());
			this->resetbtn1 = (gcnew System::Windows::Forms::Button());
			this->setClbtn = (gcnew System::Windows::Forms::Button());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->descBox1 = (gcnew System::Windows::Forms::TextBox());
			this->datebox1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->FIR_Box1 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->viewpanel = (gcnew System::Windows::Forms::Panel());
			this->resultpnl = (gcnew System::Windows::Forms::Panel());
			this->descbox2 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->timebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->datebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->casebox2 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->resetbtn = (gcnew System::Windows::Forms::Button());
			this->searchbtn = (gcnew System::Windows::Forms::Button());
			this->FIR_Box2 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->closebtn = (gcnew System::Windows::Forms::Button());
			this->removepanel = (gcnew System::Windows::Forms::Panel());
			this->close_rcd_btn = (gcnew System::Windows::Forms::Button());
			this->Heading = (gcnew System::Windows::Forms::Label());
			this->remove_rcd_btn = (gcnew System::Windows::Forms::Button());
			this->FIR_Box3 = (gcnew System::Windows::Forms::TextBox());
			this->fir_lbl = (gcnew System::Windows::Forms::Label());
			this->bottonPnl->SuspendLayout();
			this->setpanel->SuspendLayout();
			this->viewpanel->SuspendLayout();
			this->resultpnl->SuspendLayout();
			this->removepanel->SuspendLayout();
			this->SuspendLayout();
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
			// mainheading
			// 
			this->mainheading->AutoSize = true;
			this->mainheading->BackColor = System::Drawing::Color::Transparent;
			this->mainheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mainheading->ForeColor = System::Drawing::Color::White;
			this->mainheading->Location = System::Drawing::Point(386, 31);
			this->mainheading->Name = L"mainheading";
			this->mainheading->Size = System::Drawing::Size(89, 59);
			this->mainheading->TabIndex = 8;
			this->mainheading->Text = L"FIR";
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
			this->removebtn->Location = System::Drawing::Point(75, 366);
			this->removebtn->Name = L"removebtn";
			this->removebtn->Size = System::Drawing::Size(166, 39);
			this->removebtn->TabIndex = 9;
			this->removebtn->Text = L"Remove FIR";
			this->removebtn->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->removebtn->UseVisualStyleBackColor = false;
			this->removebtn->Click += gcnew System::EventHandler(this, &FIR::removebtn_Click);
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
			this->viewbtn->Location = System::Drawing::Point(75, 261);
			this->viewbtn->Name = L"viewbtn";
			this->viewbtn->Size = System::Drawing::Size(166, 39);
			this->viewbtn->TabIndex = 10;
			this->viewbtn->Text = L"View FIR";
			this->viewbtn->UseVisualStyleBackColor = false;
			this->viewbtn->Click += gcnew System::EventHandler(this, &FIR::viewbtn_Click);
			// 
			// setbtn
			// 
			this->setbtn->BackColor = System::Drawing::Color::DarkGray;
			this->setbtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->setbtn->FlatAppearance->BorderSize = 0;
			this->setbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->setbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->setbtn->ForeColor = System::Drawing::Color::Black;
			this->setbtn->Location = System::Drawing::Point(75, 166);
			this->setbtn->Name = L"setbtn";
			this->setbtn->Size = System::Drawing::Size(166, 39);
			this->setbtn->TabIndex = 11;
			this->setbtn->Text = L"Set FIR";
			this->setbtn->UseVisualStyleBackColor = false;
			this->setbtn->Click += gcnew System::EventHandler(this, &FIR::setbtn_Click);
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
			this->dbinfo->Location = System::Drawing::Point(577, 261);
			this->dbinfo->Name = L"dbinfo";
			this->dbinfo->Size = System::Drawing::Size(166, 39);
			this->dbinfo->TabIndex = 12;
			this->dbinfo->Text = L"Database Info";
			this->dbinfo->UseVisualStyleBackColor = false;
			this->dbinfo->Click += gcnew System::EventHandler(this, &FIR::dbinfo_Click);
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
			this->abt_Btn->Location = System::Drawing::Point(577, 166);
			this->abt_Btn->Name = L"abt_Btn";
			this->abt_Btn->Size = System::Drawing::Size(166, 39);
			this->abt_Btn->TabIndex = 13;
			this->abt_Btn->Text = L"About";
			this->abt_Btn->UseVisualStyleBackColor = false;
			this->abt_Btn->Click += gcnew System::EventHandler(this, &FIR::abt_Btn_Click);
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
			this->Exitbtn->Location = System::Drawing::Point(577, 366);
			this->Exitbtn->Name = L"Exitbtn";
			this->Exitbtn->Size = System::Drawing::Size(166, 39);
			this->Exitbtn->TabIndex = 14;
			this->Exitbtn->Text = L"Exit";
			this->Exitbtn->UseVisualStyleBackColor = false;
			this->Exitbtn->Click += gcnew System::EventHandler(this, &FIR::Exitbtn_Click);
			// 
			// setpanel
			// 
			this->setpanel->BackColor = System::Drawing::Color::Silver;
			this->setpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"setpanel.BackgroundImage")));
			this->setpanel->Controls->Add(this->timebox1);
			this->setpanel->Controls->Add(this->casebox1);
			this->setpanel->Controls->Add(this->resetbtn1);
			this->setpanel->Controls->Add(this->setClbtn);
			this->setpanel->Controls->Add(this->savebtn);
			this->setpanel->Controls->Add(this->descBox1);
			this->setpanel->Controls->Add(this->datebox1);
			this->setpanel->Controls->Add(this->FIR_Box1);
			this->setpanel->Controls->Add(this->label6);
			this->setpanel->Controls->Add(this->label12);
			this->setpanel->Controls->Add(this->label5);
			this->setpanel->Controls->Add(this->label4);
			this->setpanel->Controls->Add(this->label3);
			this->setpanel->Controls->Add(this->label2);
			this->setpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->setpanel->Location = System::Drawing::Point(0, 0);
			this->setpanel->Name = L"setpanel";
			this->setpanel->Size = System::Drawing::Size(861, 543);
			this->setpanel->TabIndex = 15;
			// 
			// timebox1
			// 
			this->timebox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->timebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->timebox1->Location = System::Drawing::Point(257, 229);
			this->timebox1->Name = L"timebox1";
			this->timebox1->Size = System::Drawing::Size(124, 25);
			this->timebox1->TabIndex = 9;
			// 
			// casebox1
			// 
			this->casebox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->casebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->casebox1->Location = System::Drawing::Point(257, 117);
			this->casebox1->Name = L"casebox1";
			this->casebox1->Size = System::Drawing::Size(124, 25);
			this->casebox1->TabIndex = 8;
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
			this->resetbtn1->Click += gcnew System::EventHandler(this, &FIR::resetbtn1_Click);
			// 
			// setClbtn
			// 
			this->setClbtn->BackColor = System::Drawing::Color::White;
			this->setClbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->setClbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->setClbtn->FlatAppearance->BorderSize = 2;
			this->setClbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->setClbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->setClbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->setClbtn->Location = System::Drawing::Point(707, 117);
			this->setClbtn->Name = L"setClbtn";
			this->setClbtn->Size = System::Drawing::Size(118, 58);
			this->setClbtn->TabIndex = 7;
			this->setClbtn->Text = L"Close";
			this->setClbtn->UseVisualStyleBackColor = false;
			this->setClbtn->Click += gcnew System::EventHandler(this, &FIR::setClbtn_Click);
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
			this->savebtn->Click += gcnew System::EventHandler(this, &FIR::savebtn_Click);
			// 
			// descBox1
			// 
			this->descBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descBox1->Location = System::Drawing::Point(119, 341);
			this->descBox1->Multiline = true;
			this->descBox1->Name = L"descBox1";
			this->descBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->descBox1->Size = System::Drawing::Size(598, 178);
			this->descBox1->TabIndex = 6;
			// 
			// datebox1
			// 
			this->datebox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox1->Location = System::Drawing::Point(257, 174);
			this->datebox1->Name = L"datebox1";
			this->datebox1->Size = System::Drawing::Size(214, 25);
			this->datebox1->TabIndex = 5;
			// 
			// FIR_Box1
			// 
			this->FIR_Box1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->FIR_Box1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FIR_Box1->Location = System::Drawing::Point(257, 60);
			this->FIR_Box1->Name = L"FIR_Box1";
			this->FIR_Box1->Size = System::Drawing::Size(124, 25);
			this->FIR_Box1->TabIndex = 1;
			this->FIR_Box1->TextChanged += gcnew System::EventHandler(this, &FIR::FIR_Box1_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(33, 303);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(252, 24);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Enter Description Below : ";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(34, 253);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(126, 13);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Format : 00:15 Hours";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(33, 229);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(185, 24);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Registration Time :";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(33, 174);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(180, 24);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Registration Date :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(33, 117);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(96, 24);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Case No.";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(33, 60);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"FIR No.";
			// 
			// viewpanel
			// 
			this->viewpanel->BackColor = System::Drawing::Color::Silver;
			this->viewpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"viewpanel.BackgroundImage")));
			this->viewpanel->Controls->Add(this->resultpnl);
			this->viewpanel->Controls->Add(this->viewheading);
			this->viewpanel->Controls->Add(this->resetbtn);
			this->viewpanel->Controls->Add(this->searchbtn);
			this->viewpanel->Controls->Add(this->FIR_Box2);
			this->viewpanel->Controls->Add(this->label11);
			this->viewpanel->Controls->Add(this->closebtn);
			this->viewpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->viewpanel->Location = System::Drawing::Point(0, 0);
			this->viewpanel->Name = L"viewpanel";
			this->viewpanel->Size = System::Drawing::Size(861, 543);
			this->viewpanel->TabIndex = 16;
			// 
			// resultpnl
			// 
			this->resultpnl->BackColor = System::Drawing::Color::Transparent;
			this->resultpnl->Controls->Add(this->descbox2);
			this->resultpnl->Controls->Add(this->label10);
			this->resultpnl->Controls->Add(this->timebox2);
			this->resultpnl->Controls->Add(this->label9);
			this->resultpnl->Controls->Add(this->datebox2);
			this->resultpnl->Controls->Add(this->label8);
			this->resultpnl->Controls->Add(this->casebox2);
			this->resultpnl->Controls->Add(this->label7);
			this->resultpnl->Location = System::Drawing::Point(0, 200);
			this->resultpnl->Name = L"resultpnl";
			this->resultpnl->Size = System::Drawing::Size(861, 290);
			this->resultpnl->TabIndex = 9;
			// 
			// descbox2
			// 
			this->descbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->descbox2->Location = System::Drawing::Point(445, 107);
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
			this->label10->Location = System::Drawing::Point(440, 59);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(144, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Description :";
			// 
			// timebox2
			// 
			this->timebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->timebox2->Location = System::Drawing::Point(211, 199);
			this->timebox2->Multiline = true;
			this->timebox2->Name = L"timebox2";
			this->timebox2->ReadOnly = true;
			this->timebox2->Size = System::Drawing::Size(190, 37);
			this->timebox2->TabIndex = 5;
			this->timebox2->WordWrap = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(15, 200);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(196, 30);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Registration Time";
			// 
			// datebox2
			// 
			this->datebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->datebox2->Location = System::Drawing::Point(211, 125);
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
			this->label8->Location = System::Drawing::Point(15, 126);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(194, 30);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Registration Date";
			// 
			// casebox2
			// 
			this->casebox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->casebox2->Location = System::Drawing::Point(211, 51);
			this->casebox2->Multiline = true;
			this->casebox2->Name = L"casebox2";
			this->casebox2->ReadOnly = true;
			this->casebox2->Size = System::Drawing::Size(190, 37);
			this->casebox2->TabIndex = 1;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(15, 52);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(103, 30);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Case No.";
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
			this->resetbtn->Location = System::Drawing::Point(725, 149);
			this->resetbtn->Name = L"resetbtn";
			this->resetbtn->Size = System::Drawing::Size(122, 45);
			this->resetbtn->TabIndex = 7;
			this->resetbtn->Text = L"Reset";
			this->resetbtn->UseVisualStyleBackColor = false;
			this->resetbtn->Click += gcnew System::EventHandler(this, &FIR::resetbtn_Click);
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
			this->searchbtn->Click += gcnew System::EventHandler(this, &FIR::searchbtn_Click);
			// 
			// FIR_Box2
			// 
			this->FIR_Box2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->FIR_Box2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FIR_Box2->Location = System::Drawing::Point(171, 85);
			this->FIR_Box2->Multiline = true;
			this->FIR_Box2->Name = L"FIR_Box2";
			this->FIR_Box2->Size = System::Drawing::Size(131, 38);
			this->FIR_Box2->TabIndex = 1;
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
			this->label11->Size = System::Drawing::Size(102, 29);
			this->label11->TabIndex = 0;
			this->label11->Text = L"FIR No.";
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
			this->closebtn->Click += gcnew System::EventHandler(this, &FIR::closebtn_Click);
			// 
			// removepanel
			// 
			this->removepanel->BackColor = System::Drawing::Color::Silver;
			this->removepanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"removepanel.BackgroundImage")));
			this->removepanel->Controls->Add(this->close_rcd_btn);
			this->removepanel->Controls->Add(this->Heading);
			this->removepanel->Controls->Add(this->remove_rcd_btn);
			this->removepanel->Controls->Add(this->FIR_Box3);
			this->removepanel->Controls->Add(this->fir_lbl);
			this->removepanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->removepanel->Location = System::Drawing::Point(0, 0);
			this->removepanel->Name = L"removepanel";
			this->removepanel->Size = System::Drawing::Size(861, 543);
			this->removepanel->TabIndex = 17;
			this->removepanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FIR::removepanel_Paint);
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
			this->close_rcd_btn->Location = System::Drawing::Point(698, 347);
			this->close_rcd_btn->Name = L"close_rcd_btn";
			this->close_rcd_btn->Size = System::Drawing::Size(122, 45);
			this->close_rcd_btn->TabIndex = 11;
			this->close_rcd_btn->Text = L"Close";
			this->close_rcd_btn->UseVisualStyleBackColor = false;
			this->close_rcd_btn->Click += gcnew System::EventHandler(this, &FIR::close_rcd_btn_Click);
			// 
			// Heading
			// 
			this->Heading->AutoSize = true;
			this->Heading->BackColor = System::Drawing::Color::Transparent;
			this->Heading->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Heading->ForeColor = System::Drawing::Color::White;
			this->Heading->Location = System::Drawing::Point(335, 32);
			this->Heading->Name = L"Heading";
			this->Heading->Size = System::Drawing::Size(190, 45);
			this->Heading->TabIndex = 10;
			this->Heading->Text = L"Remove FIR";
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
			this->remove_rcd_btn->Click += gcnew System::EventHandler(this, &FIR::remove_rcd_btn_Click);
			// 
			// FIR_Box3
			// 
			this->FIR_Box3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->FIR_Box3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FIR_Box3->Location = System::Drawing::Point(363, 152);
			this->FIR_Box3->Multiline = true;
			this->FIR_Box3->Name = L"FIR_Box3";
			this->FIR_Box3->Size = System::Drawing::Size(131, 38);
			this->FIR_Box3->TabIndex = 1;
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
			this->fir_lbl->Size = System::Drawing::Size(122, 33);
			this->fir_lbl->TabIndex = 0;
			this->fir_lbl->Text = L"FIR No.";
			// 
			// FIR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(861, 570);
			this->Controls->Add(this->viewpanel);
			this->Controls->Add(this->removepanel);
			this->Controls->Add(this->setpanel);
			this->Controls->Add(this->dbinfo);
			this->Controls->Add(this->abt_Btn);
			this->Controls->Add(this->Exitbtn);
			this->Controls->Add(this->removebtn);
			this->Controls->Add(this->viewbtn);
			this->Controls->Add(this->setbtn);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->mainheading);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FIR";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"FIR";
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->setpanel->ResumeLayout(false);
			this->setpanel->PerformLayout();
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
	private: System::Void setbtn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		setpanel->Show();
	}

private: System::Void abt_Btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	MessageBox::Show("This tab includes the informmation about all the FIRs registered against cases. Case Number is used to search required FIR.", "FIR Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void dbinfo_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (isDbConnected == false)
	{
		MessageBox::Show("MYSQL Server is not installed on your system .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("MYSQL Server 8.0 .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}

private: System::Void Exitbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	FIR::Hide();
}

private: System::Void viewbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	setpanel->Hide();
	viewpanel->Show();
}

private: System::Void searchbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (FIR_Box2->Text== "")
	{
		MessageBox::Show("This field requires data.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(FIR_Box2->Text); 
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
		FIR_Box2->Clear();
	}
}
private: System::Void resetbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	FIR_Box2->Clear(); 
	casebox2->Clear();
	datebox2->ResetText();
	timebox2->Clear(); 
	descbox2->Clear(); 
}
private: System::Void closebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	FIR_Box2->Clear();
	casebox2->Clear();
	datebox2->ResetText();
	timebox2->Clear();
	descbox2->Clear();
	viewpanel->Hide();
	resultpnl->Hide();
}
private: System::Void removebtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	setpanel->Hide();
	viewpanel->Hide();
	resultpnl->Hide();
	removepanel->Show();
}
private: System::Void setClbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult msgbox;
	if (textChange == true)
	{
		msgbox = MessageBox::Show("Are you sure you want to exit without saving ? ", "SaveChanges", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (msgbox == System::Windows::Forms::DialogResult::Yes)
		{
			FIR_Box1->Clear();
			casebox1->Clear();
			datebox1->ResetText();
			timebox1->Clear();
			descBox1->Clear();
			setpanel->Hide();
		}
		else if (msgbox == System::Windows::Forms::DialogResult::No)
		{
			return;
		}
	}
	else
	{
		setpanel->Hide();
	}
}
private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	int firid = NULL, caseid= NULL; 

	try
	{
		firid = System::Convert::ToInt16(FIR_Box1->Text);
		caseid = System::Convert::ToInt16(casebox1->Text);

		if (isDbConnected)
		{
			if (!IDcheckDb(firid))
			{
				MessageBox::Show("A record with this FIR'ID already exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			addDetailsDatabase(firid , caseid, datebox1->Text, timebox1->Text, descBox1->Text);  
		}
		else
		{
			addDetailCsv(firid, caseid, datebox1->Text, timebox1->Text, descBox1->Text);
		}
 	}
	catch (...)
	{
		MessageBox::Show("FIR ID and Case ID can only be digits", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	MessageBox::Show("Details have been successfully saved.", "DialogBox", MessageBoxButtons::OK, MessageBoxIcon::Information);
	textChange = false;
}
private: System::Void FIR_Box1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textChange = true; 
}
private: System::Void randbtn_Click(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void resetbtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	FIR_Box1->Clear();
	casebox1->Clear();
	datebox1->ResetText();
	timebox1->Clear();
	descBox1->Clear();
}
private: System::Void remove_rcd_btn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (FIR_Box3->Text == "")
	{
		MessageBox::Show("This field requires data.", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(FIR_Box3->Text); 

		if (isDbConnected)
		{
			removeDetailDatabase(id); 
		}
		else
		{
			removeDetailCSV(id); 
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		FIR_Box3->Clear();
	}
}
private: System::Void removepanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void close_rcd_btn_Click(System::Object^ sender, System::EventArgs^ e) {
	FIR_Box3->Clear(); 
	removepanel->Hide(); 
}

};
}
