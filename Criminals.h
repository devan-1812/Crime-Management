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
	/// Summary for Criminals
	/// </summary>
	public ref class Criminals : public System::Windows::Forms::Form
	{
	private:
		MYSQL* currentconn;
		bool isDbConnected;
		bool textChange = false;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ crimeIdBox1;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ durationBox1;
	private: System::Windows::Forms::TextBox^ heightBox1;
	private: System::Windows::Forms::TextBox^ crimeCommitedBox1;
	private: System::Windows::Forms::Button^ closeBtn1;
	private: System::Windows::Forms::Button^ resetbtn1;
	private: System::Windows::Forms::Panel^ bottonPnl;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TextBox^ crimecommitecBox2;

	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ durationBox2;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ heightBox2;

	private: System::Windows::Forms::TextBox^ ageBox2;
	private: System::Windows::Forms::TextBox^ crimeIdBox2;


	private: System::Windows::Forms::TextBox^ nameBox2;

	private: System::Windows::Forms::Label^ label13;

	private: System::Windows::Forms::Label^ crmnl_id_lbl;
	private: System::Windows::Forms::TextBox^ IdBox3;
	private: System::Windows::Forms::Button^ rmv_crmnl_rcd_btn;
	private: System::Windows::Forms::Label^ rmv_crmnl_Heading;
	private: System::Windows::Forms::Button^ close_crmnl_rcd_btn;
	private: System::Windows::Forms::Panel^ Rmv_crmnl_rcd_pnl;
	private: System::Windows::Forms::Label^ datalabel;
	public:
		Criminals(void)
		{
			InitializeComponent();
			add_crmnl_det_pnl->Hide();
			pnlview_crmnl->Hide();
			resultPnl->Hide();
			Rmv_crmnl_rcd_pnl->Hide();
			//
			//TODO: Add the constructor code here
			//
		}
		Criminals(MYSQL* db, bool isconn)
		{
			InitializeComponent();
			add_crmnl_det_pnl->Hide();
			pnlview_crmnl->Hide();
			resultPnl->Hide();
			Rmv_crmnl_rcd_pnl->Hide();
			currentconn = db; 
			isDbConnected = isconn; 

			if (isDbConnected)
			{
				datalabel->ForeColor = System::Drawing::Color::LawnGreen;
				label18->ForeColor = System::Drawing::Color::Red;
			}
			else
			{
				datalabel->ForeColor = System::Drawing::Color::Red;
				label18->ForeColor = System::Drawing::Color::LawnGreen;
			}
		}
		bool idcheckDB(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss;
			ss << "select ID from cms.criminals where ID = " << id;
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
			msclr::interop::marshal_context converter;
			std::string name, crimecommited, age, duration; 

			name = converter.marshal_as<std::string>(nameBox1->Text);
			crimecommited = converter.marshal_as<std::string>(crimeCommitedBox1->Text);
			age = converter.marshal_as<std::string>(ageBox1->Text); 
			duration = converter.marshal_as<std::string>(durationBox1->Text); 

			int id = System::Convert::ToInt16(idBox1->Text);
			int crimeid = System::Convert::ToInt16(crimeIdBox1->Text); 
			double height = System::Convert::ToDouble(heightBox1->Text); 

			std::stringstream ss; 
			ss << "insert into cms.criminals (ID, Name, CrimeID, CrimeCommited, Age, Height, Duration) values ( " << id << ", '" << name << "' ," << crimeid << ", '" << crimecommited << "' , '" << age << "' , " << height << ", '" << duration <<"' )";
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
		void addDetaiCSV()
		{
			msclr::interop::marshal_context converter;
			std::string name, crimecommited, age, duration;

			name = converter.marshal_as<std::string>(nameBox1->Text);
			crimecommited = converter.marshal_as<std::string>(crimeCommitedBox1->Text);
			age = converter.marshal_as<std::string>(ageBox1->Text);
			duration = converter.marshal_as<std::string>(durationBox1->Text);

			int id = System::Convert::ToInt16(idBox1->Text);
			int crimeid = System::Convert::ToInt16(crimeIdBox1->Text);
			double height = System::Convert::ToDouble(heightBox1->Text);

			std::fstream file1; 
			file1.open("Criminals.csv", std::ios::out | std::ios::app); 
			file1 << id << "," << name << "," << crimeid << "," << crimecommited << "," << age << "," << height << "," << duration << std::endl; 
			file1.close();
		}
		void viewdetaildatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::string name, crimeid, crimecommited, age, height, duration; 
			String^ Name, ^ CrimeID, ^ CrimeCommited, ^ Age, ^ Height, ^ Duration;

			std::stringstream ss; 

			ss << "select * from cms.criminals where ID = " << id ;
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
					resultPnl->Show();
					name = row[1]; 
					crimeid = row[2];
					crimecommited = row[3];
					age = row[4]; 
					height = row[5]; 
					duration = row[6]; 

					Name = gcnew String(name.c_str());
					CrimeID = gcnew String(crimeid.c_str());
					CrimeCommited = gcnew String(crimecommited.c_str());
					Age = gcnew String(age.c_str());
					Height= gcnew String(height.c_str());
					Duration = gcnew String(duration.c_str());

					nameBox2->Text = Name; 
					crimeIdBox2->Text = CrimeID; 
					crimecommitecBox2->Text = CrimeCommited; 
					ageBox2->Text = Age;
					heightBox2->Text = Height;
					durationBox2->Text = Duration; 
				}
			}
			else
			{
				MessageBox::Show("Error"); 
			}


		}
		void viewdetailcsv(int id)
		{
			int id2;
			std::fstream file1;
			file1.open("Criminals.csv", std::ios::in);

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
					MessageBox::Show("No Record Exists with this ID", "Search Database", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				if (id == id2)
				{
					resultPnl->Show();
					std::string name, crimeid, crimecommited, age, height, duration;
					getline(ss, name, ',');
					getline(ss, crimeid, ',');
					getline(ss, crimecommited, ',');
					getline(ss, age, ',');
					getline(ss, height, ',');
					getline(ss, duration, ',');
					String^ Name, ^ CrimeID, ^ CrimeCommited, ^ Age, ^ Height, ^ Duration;

					Name = gcnew String(name.c_str());
					CrimeID = gcnew String(crimeid.c_str());
					CrimeCommited = gcnew String(crimecommited.c_str());
					Age = gcnew String(age.c_str());
					Height = gcnew String(height.c_str());
					Duration = gcnew String(duration.c_str());

					nameBox2->Text = Name;
					crimeIdBox2->Text = CrimeID;
					crimecommitecBox2->Text = CrimeCommited;
					ageBox2->Text = Age;
					heightBox2->Text = Height;
					durationBox2->Text = Duration;
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

			ss << "select * from cms.criminals where ID = " << id; 
			std::string query= ss.str();
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
					delquery << "delete from cms.criminals where ID = " << id;
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
			file1.open("Criminals.csv", std::ios::in); 
			file2.open("CriminalsNew.csv", std::ios::out); 
			int id2 = NULL;  bool idFound = false;

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
					std::string name, crimeid, crimecommited, age, height, duration;
					getline(ss, name, ',');
					getline(ss, crimeid, ',');
					getline(ss, crimecommited, ',');
					getline(ss, age, ',');
					getline(ss, height, ',');
					getline(ss, duration, ',');

					file2 << id2 << "," << name << "," << crimeid << "," << crimecommited << "," << age << "," << height << "," << duration << std::endl;
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
			remove("Criminals.csv"); 
			rename("CriminalsNew.csv", "Criminals.csv"); 
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Criminals()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ mainheading_criminals;
	private: System::Windows::Forms::Button^ rmv_crmnl_btn;
	private: System::Windows::Forms::Button^ view_criminal_btn;
	private: System::Windows::Forms::Button^ add_criminal_btn;
	private: System::Windows::Forms::Panel^ add_crmnl_det_pnl;
	private: System::Windows::Forms::Button^ Savebtn;

	private: System::Windows::Forms::TextBox^ idBox1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ nameBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ ageBox1;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Panel^ pnlview_crmnl;
	private: System::Windows::Forms::Button^ cls_crmnl_rec_btn;
private: System::Windows::Forms::Panel^ resultPnl;

	private: System::Windows::Forms::Label^ viewheading;
	private: System::Windows::Forms::Button^ search_CID_btn;
private: System::Windows::Forms::TextBox^ IdBox2;


	private: System::Windows::Forms::Label^ label14;







	private: System::Windows::Forms::Button^ abtbtn;
	private: System::Windows::Forms::Button^ dbInfoBtn;
	private: System::Windows::Forms::Button^ exitBtn;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Criminals::typeid));
			this->mainheading_criminals = (gcnew System::Windows::Forms::Label());
			this->rmv_crmnl_btn = (gcnew System::Windows::Forms::Button());
			this->view_criminal_btn = (gcnew System::Windows::Forms::Button());
			this->add_criminal_btn = (gcnew System::Windows::Forms::Button());
			this->add_crmnl_det_pnl = (gcnew System::Windows::Forms::Panel());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->durationBox1 = (gcnew System::Windows::Forms::TextBox());
			this->heightBox1 = (gcnew System::Windows::Forms::TextBox());
			this->ageBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->crimeCommitedBox1 = (gcnew System::Windows::Forms::TextBox());
			this->crimeIdBox1 = (gcnew System::Windows::Forms::TextBox());
			this->nameBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->closeBtn1 = (gcnew System::Windows::Forms::Button());
			this->resetbtn1 = (gcnew System::Windows::Forms::Button());
			this->Savebtn = (gcnew System::Windows::Forms::Button());
			this->idBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->resultPnl = (gcnew System::Windows::Forms::Panel());
			this->crimecommitecBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->durationBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->heightBox2 = (gcnew System::Windows::Forms::TextBox());
			this->ageBox2 = (gcnew System::Windows::Forms::TextBox());
			this->crimeIdBox2 = (gcnew System::Windows::Forms::TextBox());
			this->nameBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->pnlview_crmnl = (gcnew System::Windows::Forms::Panel());
			this->cls_crmnl_rec_btn = (gcnew System::Windows::Forms::Button());
			this->viewheading = (gcnew System::Windows::Forms::Label());
			this->search_CID_btn = (gcnew System::Windows::Forms::Button());
			this->IdBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->abtbtn = (gcnew System::Windows::Forms::Button());
			this->dbInfoBtn = (gcnew System::Windows::Forms::Button());
			this->exitBtn = (gcnew System::Windows::Forms::Button());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->crmnl_id_lbl = (gcnew System::Windows::Forms::Label());
			this->IdBox3 = (gcnew System::Windows::Forms::TextBox());
			this->rmv_crmnl_rcd_btn = (gcnew System::Windows::Forms::Button());
			this->rmv_crmnl_Heading = (gcnew System::Windows::Forms::Label());
			this->close_crmnl_rcd_btn = (gcnew System::Windows::Forms::Button());
			this->Rmv_crmnl_rcd_pnl = (gcnew System::Windows::Forms::Panel());
			this->add_crmnl_det_pnl->SuspendLayout();
			this->resultPnl->SuspendLayout();
			this->pnlview_crmnl->SuspendLayout();
			this->bottonPnl->SuspendLayout();
			this->Rmv_crmnl_rcd_pnl->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainheading_criminals
			// 
			this->mainheading_criminals->AutoSize = true;
			this->mainheading_criminals->BackColor = System::Drawing::Color::Transparent;
			this->mainheading_criminals->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mainheading_criminals->ForeColor = System::Drawing::Color::White;
			this->mainheading_criminals->Location = System::Drawing::Point(316, 25);
			this->mainheading_criminals->Name = L"mainheading_criminals";
			this->mainheading_criminals->Size = System::Drawing::Size(212, 59);
			this->mainheading_criminals->TabIndex = 3;
			this->mainheading_criminals->Text = L"Criminals\r\n";
			// 
			// rmv_crmnl_btn
			// 
			this->rmv_crmnl_btn->BackColor = System::Drawing::Color::DarkGray;
			this->rmv_crmnl_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->rmv_crmnl_btn->FlatAppearance->BorderSize = 0;
			this->rmv_crmnl_btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rmv_crmnl_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rmv_crmnl_btn->ForeColor = System::Drawing::Color::Black;
			this->rmv_crmnl_btn->Location = System::Drawing::Point(79, 317);
			this->rmv_crmnl_btn->Name = L"rmv_crmnl_btn";
			this->rmv_crmnl_btn->Size = System::Drawing::Size(188, 47);
			this->rmv_crmnl_btn->TabIndex = 4;
			this->rmv_crmnl_btn->Text = L"Remove Criminal";
			this->rmv_crmnl_btn->UseVisualStyleBackColor = false;
			this->rmv_crmnl_btn->Click += gcnew System::EventHandler(this, &Criminals::rmv_crmnl_btn_Click);
			// 
			// view_criminal_btn
			// 
			this->view_criminal_btn->BackColor = System::Drawing::Color::DarkGray;
			this->view_criminal_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->view_criminal_btn->FlatAppearance->BorderSize = 0;
			this->view_criminal_btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->view_criminal_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->view_criminal_btn->ForeColor = System::Drawing::Color::Black;
			this->view_criminal_btn->Location = System::Drawing::Point(79, 225);
			this->view_criminal_btn->Name = L"view_criminal_btn";
			this->view_criminal_btn->Size = System::Drawing::Size(188, 47);
			this->view_criminal_btn->TabIndex = 5;
			this->view_criminal_btn->Text = L"View Criminal";
			this->view_criminal_btn->UseVisualStyleBackColor = false;
			this->view_criminal_btn->Click += gcnew System::EventHandler(this, &Criminals::view_criminal_btn_Click);
			// 
			// add_criminal_btn
			// 
			this->add_criminal_btn->BackColor = System::Drawing::Color::DarkGray;
			this->add_criminal_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->add_criminal_btn->FlatAppearance->BorderSize = 0;
			this->add_criminal_btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->add_criminal_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->add_criminal_btn->ForeColor = System::Drawing::Color::Black;
			this->add_criminal_btn->Location = System::Drawing::Point(79, 140);
			this->add_criminal_btn->Name = L"add_criminal_btn";
			this->add_criminal_btn->Size = System::Drawing::Size(188, 47);
			this->add_criminal_btn->TabIndex = 6;
			this->add_criminal_btn->Text = L"Add Criminal";
			this->add_criminal_btn->UseVisualStyleBackColor = false;
			this->add_criminal_btn->Click += gcnew System::EventHandler(this, &Criminals::add_criminal_btn_Click);
			// 
			// add_crmnl_det_pnl
			// 
			this->add_crmnl_det_pnl->BackColor = System::Drawing::Color::Silver;
			this->add_crmnl_det_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"add_crmnl_det_pnl.BackgroundImage")));
			this->add_crmnl_det_pnl->Controls->Add(this->label16);
			this->add_crmnl_det_pnl->Controls->Add(this->durationBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->heightBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->ageBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->label8);
			this->add_crmnl_det_pnl->Controls->Add(this->label9);
			this->add_crmnl_det_pnl->Controls->Add(this->label5);
			this->add_crmnl_det_pnl->Controls->Add(this->label7);
			this->add_crmnl_det_pnl->Controls->Add(this->label4);
			this->add_crmnl_det_pnl->Controls->Add(this->label3);
			this->add_crmnl_det_pnl->Controls->Add(this->crimeCommitedBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->crimeIdBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->nameBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->label17);
			this->add_crmnl_det_pnl->Controls->Add(this->label1);
			this->add_crmnl_det_pnl->Controls->Add(this->closeBtn1);
			this->add_crmnl_det_pnl->Controls->Add(this->resetbtn1);
			this->add_crmnl_det_pnl->Controls->Add(this->Savebtn);
			this->add_crmnl_det_pnl->Controls->Add(this->idBox1);
			this->add_crmnl_det_pnl->Controls->Add(this->label6);
			this->add_crmnl_det_pnl->Controls->Add(this->label2);
			this->add_crmnl_det_pnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->add_crmnl_det_pnl->Location = System::Drawing::Point(0, 0);
			this->add_crmnl_det_pnl->Name = L"add_crmnl_det_pnl";
			this->add_crmnl_det_pnl->Size = System::Drawing::Size(845, 504);
			this->add_crmnl_det_pnl->TabIndex = 9;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->BackColor = System::Drawing::Color::Transparent;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(275, 12);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(301, 59);
			this->label16->TabIndex = 22;
			this->label16->Text = L"Add  Criminal";
			// 
			// durationBox1
			// 
			this->durationBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->durationBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->durationBox1->Location = System::Drawing::Point(668, 253);
			this->durationBox1->Multiline = true;
			this->durationBox1->Name = L"durationBox1";
			this->durationBox1->Size = System::Drawing::Size(124, 31);
			this->durationBox1->TabIndex = 21;
			this->durationBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// heightBox1
			// 
			this->heightBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->heightBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->heightBox1->Location = System::Drawing::Point(666, 194);
			this->heightBox1->Multiline = true;
			this->heightBox1->Name = L"heightBox1";
			this->heightBox1->Size = System::Drawing::Size(124, 31);
			this->heightBox1->TabIndex = 21;
			this->heightBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// ageBox1
			// 
			this->ageBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ageBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ageBox1->Location = System::Drawing::Point(666, 130);
			this->ageBox1->Multiline = true;
			this->ageBox1->Name = L"ageBox1";
			this->ageBox1->Size = System::Drawing::Size(124, 31);
			this->ageBox1->TabIndex = 21;
			this->ageBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(601, 208);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(57, 13);
			this->label8->TabIndex = 20;
			this->label8->Text = L"(In Inches)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(439, 200);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(168, 24);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Criminal\'s Height\r\n";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(445, 280);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(60, 13);
			this->label5->TabIndex = 15;
			this->label5->Text = L"(In Months)";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(440, 260);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(183, 24);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Sentence Duration\r\n";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(584, 148);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(52, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"(In Years)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(439, 140);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(151, 24);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Criminal\'s  Age";
			// 
			// crimeCommitedBox1
			// 
			this->crimeCommitedBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->crimeCommitedBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crimeCommitedBox1->Location = System::Drawing::Point(249, 290);
			this->crimeCommitedBox1->Name = L"crimeCommitedBox1";
			this->crimeCommitedBox1->Size = System::Drawing::Size(124, 34);
			this->crimeCommitedBox1->TabIndex = 9;
			this->crimeCommitedBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// crimeIdBox1
			// 
			this->crimeIdBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->crimeIdBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crimeIdBox1->Location = System::Drawing::Point(249, 236);
			this->crimeIdBox1->Name = L"crimeIdBox1";
			this->crimeIdBox1->Size = System::Drawing::Size(124, 34);
			this->crimeIdBox1->TabIndex = 9;
			this->crimeIdBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// nameBox1
			// 
			this->nameBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->nameBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameBox1->Location = System::Drawing::Point(249, 179);
			this->nameBox1->Name = L"nameBox1";
			this->nameBox1->Size = System::Drawing::Size(124, 34);
			this->nameBox1->TabIndex = 9;
			this->nameBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->BackColor = System::Drawing::Color::Transparent;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::Color::White;
			this->label17->Location = System::Drawing::Point(45, 235);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(90, 24);
			this->label17->TabIndex = 8;
			this->label17->Text = L"Crime ID";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(45, 185);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(162, 24);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Criminal\'s Name";
			// 
			// closeBtn1
			// 
			this->closeBtn1->BackColor = System::Drawing::Color::White;
			this->closeBtn1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closeBtn1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closeBtn1->FlatAppearance->BorderSize = 2;
			this->closeBtn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeBtn1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closeBtn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->closeBtn1->Location = System::Drawing::Point(682, 379);
			this->closeBtn1->Name = L"closeBtn1";
			this->closeBtn1->Size = System::Drawing::Size(124, 40);
			this->closeBtn1->TabIndex = 7;
			this->closeBtn1->Text = L"Close";
			this->closeBtn1->UseVisualStyleBackColor = false;
			this->closeBtn1->Click += gcnew System::EventHandler(this, &Criminals::closeBtn1_Click);
			// 
			// resetbtn1
			// 
			this->resetbtn1->BackColor = System::Drawing::Color::White;
			this->resetbtn1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetbtn1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn1->FlatAppearance->BorderSize = 2;
			this->resetbtn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetbtn1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetbtn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetbtn1->Location = System::Drawing::Point(196, 379);
			this->resetbtn1->Name = L"resetbtn1";
			this->resetbtn1->Size = System::Drawing::Size(124, 40);
			this->resetbtn1->TabIndex = 7;
			this->resetbtn1->Text = L"Reset";
			this->resetbtn1->UseVisualStyleBackColor = false;
			this->resetbtn1->Click += gcnew System::EventHandler(this, &Criminals::resetbtn1_Click);
			// 
			// Savebtn
			// 
			this->Savebtn->BackColor = System::Drawing::Color::White;
			this->Savebtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Savebtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->Savebtn->FlatAppearance->BorderSize = 2;
			this->Savebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Savebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Savebtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->Savebtn->Location = System::Drawing::Point(39, 379);
			this->Savebtn->Name = L"Savebtn";
			this->Savebtn->Size = System::Drawing::Size(124, 40);
			this->Savebtn->TabIndex = 7;
			this->Savebtn->Text = L"Save";
			this->Savebtn->UseVisualStyleBackColor = false;
			this->Savebtn->Click += gcnew System::EventHandler(this, &Criminals::savebtn_Click);
			// 
			// idBox1
			// 
			this->idBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->idBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->idBox1->Location = System::Drawing::Point(249, 130);
			this->idBox1->Name = L"idBox1";
			this->idBox1->Size = System::Drawing::Size(124, 34);
			this->idBox1->TabIndex = 1;
			this->idBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->idBox1->TextChanged += gcnew System::EventHandler(this, &Criminals::idBox1_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(45, 296);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(170, 24);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Crime Committed";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(45, 140);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Criminal ID";
			// 
			// resultPnl
			// 
			this->resultPnl->BackColor = System::Drawing::Color::Transparent;
			this->resultPnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"resultPnl.BackgroundImage")));
			this->resultPnl->Controls->Add(this->crimecommitecBox2);
			this->resultPnl->Controls->Add(this->label19);
			this->resultPnl->Controls->Add(this->durationBox2);
			this->resultPnl->Controls->Add(this->label12);
			this->resultPnl->Controls->Add(this->label11);
			this->resultPnl->Controls->Add(this->label15);
			this->resultPnl->Controls->Add(this->label10);
			this->resultPnl->Controls->Add(this->heightBox2);
			this->resultPnl->Controls->Add(this->ageBox2);
			this->resultPnl->Controls->Add(this->crimeIdBox2);
			this->resultPnl->Controls->Add(this->nameBox2);
			this->resultPnl->Controls->Add(this->label13);
			this->resultPnl->Location = System::Drawing::Point(6, 193);
			this->resultPnl->Name = L"resultPnl";
			this->resultPnl->Size = System::Drawing::Size(835, 305);
			this->resultPnl->TabIndex = 9;
			// 
			// crimecommitecBox2
			// 
			this->crimecommitecBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crimecommitecBox2->Location = System::Drawing::Point(633, 93);
			this->crimecommitecBox2->Multiline = true;
			this->crimecommitecBox2->Name = L"crimecommitecBox2";
			this->crimecommitecBox2->ReadOnly = true;
			this->crimecommitecBox2->Size = System::Drawing::Size(190, 34);
			this->crimecommitecBox2->TabIndex = 13;
			this->crimecommitecBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->BackColor = System::Drawing::Color::Transparent;
			this->label19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->ForeColor = System::Drawing::Color::White;
			this->label19->Location = System::Drawing::Point(422, 97);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(197, 30);
			this->label19->TabIndex = 12;
			this->label19->Text = L"Crime Committed";
			// 
			// durationBox2
			// 
			this->durationBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->durationBox2->Location = System::Drawing::Point(216, 249);
			this->durationBox2->Multiline = true;
			this->durationBox2->Name = L"durationBox2";
			this->durationBox2->ReadOnly = true;
			this->durationBox2->Size = System::Drawing::Size(190, 34);
			this->durationBox2->TabIndex = 11;
			this->durationBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(10, 249);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(204, 30);
			this->label12->TabIndex = 10;
			this->label12->Text = L"Sentence Duration";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(19, 171);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(191, 30);
			this->label11->TabIndex = 9;
			this->label11->Text = L"Criminal\'s Height";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Transparent;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(29, 95);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(161, 30);
			this->label15->TabIndex = 8;
			this->label15->Text = L"Criminal\'s Age";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(422, 23);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(103, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Crime ID";
			// 
			// heightBox2
			// 
			this->heightBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->heightBox2->Location = System::Drawing::Point(216, 171);
			this->heightBox2->Multiline = true;
			this->heightBox2->Name = L"heightBox2";
			this->heightBox2->ReadOnly = true;
			this->heightBox2->Size = System::Drawing::Size(190, 34);
			this->heightBox2->TabIndex = 5;
			this->heightBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// ageBox2
			// 
			this->ageBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ageBox2->Location = System::Drawing::Point(216, 93);
			this->ageBox2->Multiline = true;
			this->ageBox2->Name = L"ageBox2";
			this->ageBox2->ReadOnly = true;
			this->ageBox2->Size = System::Drawing::Size(190, 34);
			this->ageBox2->TabIndex = 3;
			this->ageBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// crimeIdBox2
			// 
			this->crimeIdBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crimeIdBox2->Location = System::Drawing::Point(633, 23);
			this->crimeIdBox2->Multiline = true;
			this->crimeIdBox2->Name = L"crimeIdBox2";
			this->crimeIdBox2->ReadOnly = true;
			this->crimeIdBox2->Size = System::Drawing::Size(190, 34);
			this->crimeIdBox2->TabIndex = 1;
			this->crimeIdBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// nameBox2
			// 
			this->nameBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameBox2->Location = System::Drawing::Point(216, 16);
			this->nameBox2->Multiline = true;
			this->nameBox2->Name = L"nameBox2";
			this->nameBox2->ReadOnly = true;
			this->nameBox2->Size = System::Drawing::Size(190, 34);
			this->nameBox2->TabIndex = 1;
			this->nameBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(29, 19);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(181, 30);
			this->label13->TabIndex = 0;
			this->label13->Text = L"Criminal\'s Name";
			// 
			// pnlview_crmnl
			// 
			this->pnlview_crmnl->BackColor = System::Drawing::Color::Silver;
			this->pnlview_crmnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlview_crmnl.BackgroundImage")));
			this->pnlview_crmnl->Controls->Add(this->resultPnl);
			this->pnlview_crmnl->Controls->Add(this->cls_crmnl_rec_btn);
			this->pnlview_crmnl->Controls->Add(this->viewheading);
			this->pnlview_crmnl->Controls->Add(this->search_CID_btn);
			this->pnlview_crmnl->Controls->Add(this->IdBox2);
			this->pnlview_crmnl->Controls->Add(this->label14);
			this->pnlview_crmnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlview_crmnl->Location = System::Drawing::Point(0, 0);
			this->pnlview_crmnl->Name = L"pnlview_crmnl";
			this->pnlview_crmnl->Size = System::Drawing::Size(845, 531);
			this->pnlview_crmnl->TabIndex = 10;
			// 
			// cls_crmnl_rec_btn
			// 
			this->cls_crmnl_rec_btn->BackColor = System::Drawing::Color::White;
			this->cls_crmnl_rec_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->cls_crmnl_rec_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cls_crmnl_rec_btn->FlatAppearance->BorderSize = 2;
			this->cls_crmnl_rec_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cls_crmnl_rec_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cls_crmnl_rec_btn->Location = System::Drawing::Point(707, 133);
			this->cls_crmnl_rec_btn->Name = L"cls_crmnl_rec_btn";
			this->cls_crmnl_rec_btn->Size = System::Drawing::Size(122, 45);
			this->cls_crmnl_rec_btn->TabIndex = 11;
			this->cls_crmnl_rec_btn->Text = L"Close";
			this->cls_crmnl_rec_btn->UseVisualStyleBackColor = false;
			this->cls_crmnl_rec_btn->Click += gcnew System::EventHandler(this, &Criminals::cls_crmnl_rec_btn_Click);
			// 
			// viewheading
			// 
			this->viewheading->AutoSize = true;
			this->viewheading->BackColor = System::Drawing::Color::Transparent;
			this->viewheading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewheading->ForeColor = System::Drawing::Color::White;
			this->viewheading->Location = System::Drawing::Point(251, 16);
			this->viewheading->Name = L"viewheading";
			this->viewheading->Size = System::Drawing::Size(343, 45);
			this->viewheading->TabIndex = 10;
			this->viewheading->Text = L"View Criminal\'s Record";
			this->viewheading->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// search_CID_btn
			// 
			this->search_CID_btn->BackColor = System::Drawing::Color::White;
			this->search_CID_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->search_CID_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->search_CID_btn->FlatAppearance->BorderSize = 2;
			this->search_CID_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->search_CID_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.75F, System::Drawing::FontStyle::Bold));
			this->search_CID_btn->Location = System::Drawing::Point(35, 133);
			this->search_CID_btn->Name = L"search_CID_btn";
			this->search_CID_btn->Size = System::Drawing::Size(122, 45);
			this->search_CID_btn->TabIndex = 7;
			this->search_CID_btn->Text = L"SEARCH";
			this->search_CID_btn->UseVisualStyleBackColor = false;
			this->search_CID_btn->Click += gcnew System::EventHandler(this, &Criminals::search_CID_btn_Click);
			// 
			// IdBox2
			// 
			this->IdBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->IdBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IdBox2->Location = System::Drawing::Point(202, 77);
			this->IdBox2->Multiline = true;
			this->IdBox2->Name = L"IdBox2";
			this->IdBox2->Size = System::Drawing::Size(131, 38);
			this->IdBox2->TabIndex = 1;
			this->IdBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(28, 82);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(164, 29);
			this->label14->TabIndex = 0;
			this->label14->Text = L"Criminal ID =";
			// 
			// abtbtn
			// 
			this->abtbtn->BackColor = System::Drawing::Color::DarkGray;
			this->abtbtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->abtbtn->FlatAppearance->BorderSize = 0;
			this->abtbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->abtbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->abtbtn->ForeColor = System::Drawing::Color::Black;
			this->abtbtn->Location = System::Drawing::Point(481, 140);
			this->abtbtn->Name = L"abtbtn";
			this->abtbtn->Size = System::Drawing::Size(188, 47);
			this->abtbtn->TabIndex = 6;
			this->abtbtn->Text = L"About";
			this->abtbtn->UseVisualStyleBackColor = false;
			this->abtbtn->Click += gcnew System::EventHandler(this, &Criminals::abtbtn_Click);
			// 
			// dbInfoBtn
			// 
			this->dbInfoBtn->BackColor = System::Drawing::Color::DarkGray;
			this->dbInfoBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->dbInfoBtn->FlatAppearance->BorderSize = 0;
			this->dbInfoBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->dbInfoBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dbInfoBtn->ForeColor = System::Drawing::Color::Black;
			this->dbInfoBtn->Location = System::Drawing::Point(481, 225);
			this->dbInfoBtn->Name = L"dbInfoBtn";
			this->dbInfoBtn->Size = System::Drawing::Size(188, 47);
			this->dbInfoBtn->TabIndex = 6;
			this->dbInfoBtn->Text = L"DataBase Info";
			this->dbInfoBtn->UseVisualStyleBackColor = false;
			this->dbInfoBtn->Click += gcnew System::EventHandler(this, &Criminals::dbInfoBtn_Click);
			// 
			// exitBtn
			// 
			this->exitBtn->BackColor = System::Drawing::Color::DarkGray;
			this->exitBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->exitBtn->FlatAppearance->BorderSize = 0;
			this->exitBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->exitBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exitBtn->ForeColor = System::Drawing::Color::Black;
			this->exitBtn->Location = System::Drawing::Point(481, 317);
			this->exitBtn->Name = L"exitBtn";
			this->exitBtn->Size = System::Drawing::Size(188, 47);
			this->exitBtn->TabIndex = 6;
			this->exitBtn->Text = L"Exit";
			this->exitBtn->UseVisualStyleBackColor = false;
			this->exitBtn->Click += gcnew System::EventHandler(this, &Criminals::exitBtn_Click);
			// 
			// bottonPnl
			// 
			this->bottonPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->bottonPnl->Controls->Add(this->label18);
			this->bottonPnl->Controls->Add(this->datalabel);
			this->bottonPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottonPnl->Location = System::Drawing::Point(0, 504);
			this->bottonPnl->Name = L"bottonPnl";
			this->bottonPnl->Size = System::Drawing::Size(845, 27);
			this->bottonPnl->TabIndex = 12;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->BackColor = System::Drawing::Color::Transparent;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::Color::White;
			this->label18->Location = System::Drawing::Point(1, 4);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(159, 19);
			this->label18->TabIndex = 5;
			this->label18->Text = L"WINDOWS FILE SYSTEM";
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
			// crmnl_id_lbl
			// 
			this->crmnl_id_lbl->AutoSize = true;
			this->crmnl_id_lbl->BackColor = System::Drawing::Color::Transparent;
			this->crmnl_id_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->crmnl_id_lbl->ForeColor = System::Drawing::Color::White;
			this->crmnl_id_lbl->Location = System::Drawing::Point(240, 153);
			this->crmnl_id_lbl->Name = L"crmnl_id_lbl";
			this->crmnl_id_lbl->Size = System::Drawing::Size(164, 29);
			this->crmnl_id_lbl->TabIndex = 0;
			this->crmnl_id_lbl->Text = L"Criminal ID =";
			// 
			// IdBox3
			// 
			this->IdBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->IdBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IdBox3->Location = System::Drawing::Point(407, 148);
			this->IdBox3->Multiline = true;
			this->IdBox3->Name = L"IdBox3";
			this->IdBox3->Size = System::Drawing::Size(131, 38);
			this->IdBox3->TabIndex = 1;
			this->IdBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// rmv_crmnl_rcd_btn
			// 
			this->rmv_crmnl_rcd_btn->BackColor = System::Drawing::Color::White;
			this->rmv_crmnl_rcd_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->rmv_crmnl_rcd_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->rmv_crmnl_rcd_btn->FlatAppearance->BorderSize = 2;
			this->rmv_crmnl_rcd_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->rmv_crmnl_rcd_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.75F, System::Drawing::FontStyle::Bold));
			this->rmv_crmnl_rcd_btn->Location = System::Drawing::Point(339, 234);
			this->rmv_crmnl_rcd_btn->Name = L"rmv_crmnl_rcd_btn";
			this->rmv_crmnl_rcd_btn->Size = System::Drawing::Size(122, 45);
			this->rmv_crmnl_rcd_btn->TabIndex = 7;
			this->rmv_crmnl_rcd_btn->Text = L"REMOVE";
			this->rmv_crmnl_rcd_btn->UseVisualStyleBackColor = false;
			this->rmv_crmnl_rcd_btn->Click += gcnew System::EventHandler(this, &Criminals::rmv_crmnl_rcd_btn_Click);
			// 
			// rmv_crmnl_Heading
			// 
			this->rmv_crmnl_Heading->AutoSize = true;
			this->rmv_crmnl_Heading->BackColor = System::Drawing::Color::Transparent;
			this->rmv_crmnl_Heading->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rmv_crmnl_Heading->ForeColor = System::Drawing::Color::White;
			this->rmv_crmnl_Heading->Location = System::Drawing::Point(224, 32);
			this->rmv_crmnl_Heading->Name = L"rmv_crmnl_Heading";
			this->rmv_crmnl_Heading->Size = System::Drawing::Size(396, 45);
			this->rmv_crmnl_Heading->TabIndex = 10;
			this->rmv_crmnl_Heading->Text = L"Remove Criminal\'s Record";
			// 
			// close_crmnl_rcd_btn
			// 
			this->close_crmnl_rcd_btn->BackColor = System::Drawing::Color::White;
			this->close_crmnl_rcd_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->close_crmnl_rcd_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->close_crmnl_rcd_btn->FlatAppearance->BorderSize = 2;
			this->close_crmnl_rcd_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->close_crmnl_rcd_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->close_crmnl_rcd_btn->Location = System::Drawing::Point(718, 452);
			this->close_crmnl_rcd_btn->Name = L"close_crmnl_rcd_btn";
			this->close_crmnl_rcd_btn->Size = System::Drawing::Size(122, 45);
			this->close_crmnl_rcd_btn->TabIndex = 11;
			this->close_crmnl_rcd_btn->Text = L"Close";
			this->close_crmnl_rcd_btn->UseVisualStyleBackColor = false;
			this->close_crmnl_rcd_btn->Click += gcnew System::EventHandler(this, &Criminals::close_crmnl_rcd_btn_Click);
			// 
			// Rmv_crmnl_rcd_pnl
			// 
			this->Rmv_crmnl_rcd_pnl->BackColor = System::Drawing::Color::Silver;
			this->Rmv_crmnl_rcd_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Rmv_crmnl_rcd_pnl.BackgroundImage")));
			this->Rmv_crmnl_rcd_pnl->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Rmv_crmnl_rcd_pnl->Controls->Add(this->close_crmnl_rcd_btn);
			this->Rmv_crmnl_rcd_pnl->Controls->Add(this->rmv_crmnl_Heading);
			this->Rmv_crmnl_rcd_pnl->Controls->Add(this->rmv_crmnl_rcd_btn);
			this->Rmv_crmnl_rcd_pnl->Controls->Add(this->IdBox3);
			this->Rmv_crmnl_rcd_pnl->Controls->Add(this->crmnl_id_lbl);
			this->Rmv_crmnl_rcd_pnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Rmv_crmnl_rcd_pnl->Location = System::Drawing::Point(0, 0);
			this->Rmv_crmnl_rcd_pnl->Name = L"Rmv_crmnl_rcd_pnl";
			this->Rmv_crmnl_rcd_pnl->Size = System::Drawing::Size(845, 504);
			this->Rmv_crmnl_rcd_pnl->TabIndex = 11;
			// 
			// Criminals
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(845, 531);
			this->Controls->Add(this->add_crmnl_det_pnl);
			this->Controls->Add(this->Rmv_crmnl_rcd_pnl);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->pnlview_crmnl);
			this->Controls->Add(this->rmv_crmnl_btn);
			this->Controls->Add(this->view_criminal_btn);
			this->Controls->Add(this->exitBtn);
			this->Controls->Add(this->dbInfoBtn);
			this->Controls->Add(this->abtbtn);
			this->Controls->Add(this->add_criminal_btn);
			this->Controls->Add(this->mainheading_criminals);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Criminals";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Criminals";
			this->add_crmnl_det_pnl->ResumeLayout(false);
			this->add_crmnl_det_pnl->PerformLayout();
			this->resultPnl->ResumeLayout(false);
			this->resultPnl->PerformLayout();
			this->pnlview_crmnl->ResumeLayout(false);
			this->pnlview_crmnl->PerformLayout();
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->Rmv_crmnl_rcd_pnl->ResumeLayout(false);
			this->Rmv_crmnl_rcd_pnl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void add_criminal_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		add_crmnl_det_pnl->Show();
	}


	private: System::Void savebtn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		int id, crimeid; 

		try
		{
			id = System::Convert::ToInt16(idBox1->Text); 
			crimeid = System::Convert::ToInt16(crimeIdBox1->Text); 

			if (isDbConnected)
			{
				if (!idcheckDB(id))
				{
					MessageBox::Show("A record with this FIR'ID already exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}
				addDetailDatabase(); 
			}
			else
			{
				addDetaiCSV(); 
			}
 		}
		catch (...)
		{
			MessageBox::Show("Criminal ID and Crime ID can only be digits", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		MessageBox::Show("Details have been successfully saved.", "DialogBox", MessageBoxButtons::OK, MessageBoxIcon::Information);
		textChange = false;
	}
	private: System::Void view_criminal_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		pnlview_crmnl->Show();
	}

	private: System::Void search_CID_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (IdBox2->Text == "")
		{
			MessageBox::Show("This field requires data.", "Invalid ID", MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		try
		{
			int id = System::Convert::ToInt16(IdBox2->Text);
			if (isDbConnected)
			{
				viewdetaildatabase(id); 
			}
			else
			{
				viewdetailcsv(id);
			}
		}
		catch (...)
		{
			MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}
	private: System::Void close_crmnl_res_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		pnlview_crmnl->Hide();
		resultPnl->Hide();
	}


	private: System::Void cls_crmnl_rec_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		pnlview_crmnl->Hide();
		//crmnl_resultpnl->Hide();
	}

private: System::Void rmv_crmnl_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Rmv_crmnl_rcd_pnl->Show();
}

private: System::Void rmv_crmnl_rcd_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (IdBox3->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invalid ID", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
	 	int id = System::Convert::ToInt16(IdBox3->Text);
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
		return; 
	}
	
}
private: System::Void close_crmnl_rcd_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Rmv_crmnl_rcd_pnl->Hide();
}

private: System::Void Exit_crmnl_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Criminals::Hide();
}



private: System::Void resetbtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	idBox1->Clear();
	nameBox1->Clear();
	crimeIdBox1->Clear(); 
	crimeCommitedBox1->Clear(); 
	ageBox1->Clear(); 
	durationBox1->Clear(); 
	heightBox1->Clear(); 
}
private: System::Void closeBtn1_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult msgbox;

	if (textChange == true)
	{
		msgbox = MessageBox::Show("Are you sure you want to exit without saving ? ", "SaveChanges", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (msgbox == System::Windows::Forms::DialogResult::Yes)
		{
			idBox1->Clear();
			nameBox1->Clear();
			crimeIdBox1->Clear();
			crimeCommitedBox1->Clear();
			ageBox1->Clear();
			durationBox1->Clear();
			heightBox1->Clear();
			add_crmnl_det_pnl->Hide();
		}
		else if (msgbox == System::Windows::Forms::DialogResult::No)
		{
			return;
		}
	}
	else {		
		add_crmnl_det_pnl->Hide();
	}

}
private: System::Void idBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	textChange = true; 

}
private: System::Void abtbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("This section manages keeps record to various criminals. The crime they commited , the crime record they are assocaited to and their sentence duration", "CriminalsInfo", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void dbInfoBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (isDbConnected == false)
	{
		MessageBox::Show("MYSQL Server is not installed on your system .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("MYSQL Server 8.0 .", "Database Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
private: System::Void exitBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	Criminals::Close();
}
};
}
