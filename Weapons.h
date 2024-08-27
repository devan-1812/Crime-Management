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
	/// Summary for Weapons
	/// </summary>
	public ref class Weapons : public System::Windows::Forms::Form
	{
	public:
	MYSQL* currentconn;
	bool isDbConnected;
	bool textChange = false;
		Weapons(void)
		{
			InitializeComponent();
			add_wpn_dtl_pnl->Hide();
			view_wpn_dtl_pnl->Hide();
			wpn_result_pnl->Hide();
			Rmv_wpnrcd_pnl->Hide();
			//
			//TODO: Add the constructor code here
			//
		}
		Weapons(MYSQL* db, bool isDb)
		{
			InitializeComponent();
			add_wpn_dtl_pnl->Hide();
			view_wpn_dtl_pnl->Hide();
			wpn_result_pnl->Hide();
			Rmv_wpnrcd_pnl->Hide();
			currentconn = db;
			isDbConnected = isDb; 

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
			ss << "select ID from cms.weapons where id = " << id ; 
			std::string abc = ss.str();
			char* arrayqueue ;
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
				return false ; 
			}
		}
		void addDetailsDatabase(String^ Name ,int ID ,String^ Category, String^ Color , String^ Reg, int rpm)
		{
			msclr::interop::marshal_context converter;
			std::string name, category, color, regno; 
			std::stringstream ss; 
			
			name = converter.marshal_as<std::string>(wp_NameBox1->Text);
			category = converter.marshal_as<std::string>(wp_CategoryBox1->Text);
			color = converter.marshal_as<std::string>(wp_ColorBox1->Text);
			regno = converter.marshal_as<std::string>(wp_regBox1->Text);

			ID = System::Convert::ToInt16(wp_IdBox1->Text); 
			rpm = System::Convert::ToInt16(wp_rpmBox1->Text);

			ss << "insert into cms.weapons (Name, ID, Category, Color, RegistrationNo, RPM) values (" << "'"<< name << "' ,  "<< ID << ", '" << category << "' , '" << color << "', '" << regno << "', " << rpm << ")";

			std::string query = ss.str(); 
			char* arrayqueue;
			arrayqueue = &query[0];

			if (mysql_query(currentconn, arrayqueue))
			{
				MessageBox::Show("Error"); 
			}
			else
			{
				MessageBox::Show("Details have been successfully entered into the database", "Add Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		void addDetailsCSV(String^ Name, int ID, String^ Category, String^ Color, String^ Reg, int rpm)
		{
			std::fstream file1; 
			file1.open("Weapons.csv", std::ios::out | std::ios::app);
			
			msclr::interop::marshal_context converter;
			std::string name, category, color, regno;
			std::stringstream ss;

			name = converter.marshal_as<std::string>(wp_NameBox1->Text);
			category = converter.marshal_as<std::string>(wp_CategoryBox1->Text);
			color = converter.marshal_as<std::string>(wp_ColorBox1->Text);
			regno = converter.marshal_as<std::string>(wp_regBox1->Text);

			file1 << ID << "," << name << "," << category << "," << color << "," << regno << "," << rpm << std::endl;
			file1.close(); 
			MessageBox::Show("Details have been successfully entered into a CSV file format", "Add Details", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		void viewDetailsDatabase(int id)
		{

			MYSQL_ROW row;
			MYSQL_RES* res;
			std::string name, category, color, regno, rpm;
			std::stringstream ss;

			//now we add system datatypes
			String^ Name, ^ Category, ^ Color, ^ Regno, ^Rpm;

			ss << "select * from cms.weapons where id = " << id; 
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
					wpn_result_pnl->Show();
					name = row[0];
					category = row[2]; 
					color = row[3]; 
					regno = row[4]; 
					rpm = row[5]; 

					Name = gcnew String(name.c_str());
					Category = gcnew String(category.c_str());
					Color = gcnew String(color.c_str());
					Regno = gcnew String(regno.c_str());
					Rpm = gcnew String(rpm.c_str());

					nameBox2->Text = Name; 
					categoryBox2->Text = Category; 
					colorBox2->Text = Color; 
					regisBox2->Text = Regno; 
					rpmbox2->Text = Rpm; 
				}
			}
			else
			{
				MessageBox::Show("Error");
			}
		}
		void viewDetailsCSV(int id)
		{
			int id2;
			std::fstream file1;
			file1.open("Weapons.csv", std::ios::in);

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
					wpn_result_pnl->Show();
					std::string name, category, color, regno, rpm;
					std::getline(ss, name, ',');
					std::getline(ss, category, ',');
					std::getline(ss, color, ',');
					std::getline(ss, regno, ',');
					std::getline(ss, rpm, ',');

					String^ Name, ^ Category, ^ Color, ^ Regno, ^ Rpm;
					Name = gcnew String(name.c_str());
					Category = gcnew String(category.c_str());
					Color = gcnew String(color.c_str());
					Regno = gcnew String(regno.c_str());
					Rpm = gcnew String(rpm.c_str());

					nameBox2->Text = Name;
					categoryBox2->Text = Category;
					colorBox2->Text = Color;
					regisBox2->Text = Regno;
					rpmbox2->Text = Rpm;
					break; 
				}
				else
				{
					continue; 
				}
			}
			file1.close();
		}
		void removedetailDatabase(int id)
		{
			MYSQL_ROW row;
			MYSQL_RES* res;
			std::stringstream ss, delquery;
			char* arrayqueue;

			ss << "select * from cms.weapons where id = " << id;
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
					delquery << "delete from cms.weapons where id = " << id;
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
		void removeDetailCSV(int id)
		{
			std::fstream file1, file2;
			file1.open("Weapons.csv", std::ios::in);
			file2.open("WeaponsNew.csv", std::ios::out);
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
					std::string name, category, color, regno, rpm;
					std::getline(ss, name, ',');
					std::getline(ss, category, ',');
					std::getline(ss, color, ',');
					std::getline(ss, regno, ',');
					std::getline(ss, rpm, ',');

					file2 << id2 << "," << name << "," << category << "," << color << "," << regno << "," << rpm << std::endl;
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

			remove("Weapons.csv");
			rename("WeaponsNew.csv", "Weapons.csv");
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Weapons()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ mainhdng_Wpns;
	private: System::Windows::Forms::Button^ rmv_wpn_btn;
	private: System::Windows::Forms::Button^ view_wpn_btn;
	private: System::Windows::Forms::Button^ add_wpn_btn;
	private: System::Windows::Forms::Button^ wpn_dbinfo;
	private: System::Windows::Forms::Button^ wpn_abt_Btn;
	private: System::Windows::Forms::Button^ wpn_Exitbtn;
	private: System::Windows::Forms::Panel^ add_wpn_dtl_pnl;
	private: System::Windows::Forms::Button^ wpn_dtl_cls;
	private: System::Windows::Forms::Button^ save_wpd_dtl;
	private: System::Windows::Forms::TextBox^ wp_NameBox1;
	private: System::Windows::Forms::Label^ Wpn_reg;
	private: System::Windows::Forms::Label^ wpn_clr;
	private: System::Windows::Forms::Label^ wpn_cat;
	private: System::Windows::Forms::Label^ Wpn_id;
	private: System::Windows::Forms::Label^ wpn_name;
	private: System::Windows::Forms::Label^ Rounds_pm;
	private: System::Windows::Forms::Panel^ view_wpn_dtl_pnl;
	private: System::Windows::Forms::Panel^ wpn_result_pnl;
private: System::Windows::Forms::TextBox^ regisBox2;

	private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::TextBox^ colorBox2;

	private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::TextBox^ categoryBox2;

	private: System::Windows::Forms::Label^ wpn_cat_lbl;
private: System::Windows::Forms::TextBox^ nameBox2;

	private: System::Windows::Forms::Label^ wpn_name_lbl;
	private: System::Windows::Forms::Label^ view_wpn_heading;
	private: System::Windows::Forms::Button^ search_wpnid_btn;
	private: System::Windows::Forms::TextBox^ wpnID_tbx;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Button^ cls_wpn_dtlbtn;
	private: System::Windows::Forms::Panel^ bottonPnl;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ datalabel;
private: System::Windows::Forms::NumericUpDown^ rpmbox2;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ Rmv_wpnrcd_pnl;
	private: System::Windows::Forms::Button^ cls_wpnrcd_btn;
	private: System::Windows::Forms::Label^ rmvwpn_Heading;
	private: System::Windows::Forms::Button^ rmv_wpnrcd_btn;
	private: System::Windows::Forms::TextBox^ wpn_id_tbox;
	private: System::Windows::Forms::Label^ w_id_lbl;
	private: System::Windows::Forms::Button^ resetBtn;
	private: System::Windows::Forms::NumericUpDown^ wp_rpmBox1;

private: System::Windows::Forms::TextBox^ wp_regBox1;

private: System::Windows::Forms::TextBox^ wp_ColorBox1;

private: System::Windows::Forms::TextBox^ wp_CategoryBox1;

private: System::Windows::Forms::TextBox^ wp_IdBox1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Weapons::typeid));
			this->mainhdng_Wpns = (gcnew System::Windows::Forms::Label());
			this->rmv_wpn_btn = (gcnew System::Windows::Forms::Button());
			this->view_wpn_btn = (gcnew System::Windows::Forms::Button());
			this->add_wpn_btn = (gcnew System::Windows::Forms::Button());
			this->wpn_dbinfo = (gcnew System::Windows::Forms::Button());
			this->wpn_abt_Btn = (gcnew System::Windows::Forms::Button());
			this->wpn_Exitbtn = (gcnew System::Windows::Forms::Button());
			this->add_wpn_dtl_pnl = (gcnew System::Windows::Forms::Panel());
			this->Rmv_wpnrcd_pnl = (gcnew System::Windows::Forms::Panel());
			this->cls_wpnrcd_btn = (gcnew System::Windows::Forms::Button());
			this->rmvwpn_Heading = (gcnew System::Windows::Forms::Label());
			this->rmv_wpnrcd_btn = (gcnew System::Windows::Forms::Button());
			this->wpn_id_tbox = (gcnew System::Windows::Forms::TextBox());
			this->w_id_lbl = (gcnew System::Windows::Forms::Label());
			this->view_wpn_dtl_pnl = (gcnew System::Windows::Forms::Panel());
			this->wpn_result_pnl = (gcnew System::Windows::Forms::Panel());
			this->rpmbox2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->regisBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->colorBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->categoryBox2 = (gcnew System::Windows::Forms::TextBox());
			this->wpn_cat_lbl = (gcnew System::Windows::Forms::Label());
			this->nameBox2 = (gcnew System::Windows::Forms::TextBox());
			this->wpn_name_lbl = (gcnew System::Windows::Forms::Label());
			this->view_wpn_heading = (gcnew System::Windows::Forms::Label());
			this->search_wpnid_btn = (gcnew System::Windows::Forms::Button());
			this->wpnID_tbx = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->cls_wpn_dtlbtn = (gcnew System::Windows::Forms::Button());
			this->resetBtn = (gcnew System::Windows::Forms::Button());
			this->wpn_dtl_cls = (gcnew System::Windows::Forms::Button());
			this->save_wpd_dtl = (gcnew System::Windows::Forms::Button());
			this->wp_regBox1 = (gcnew System::Windows::Forms::TextBox());
			this->wp_ColorBox1 = (gcnew System::Windows::Forms::TextBox());
			this->wp_CategoryBox1 = (gcnew System::Windows::Forms::TextBox());
			this->wp_IdBox1 = (gcnew System::Windows::Forms::TextBox());
			this->wp_NameBox1 = (gcnew System::Windows::Forms::TextBox());
			this->Wpn_reg = (gcnew System::Windows::Forms::Label());
			this->wpn_clr = (gcnew System::Windows::Forms::Label());
			this->wpn_cat = (gcnew System::Windows::Forms::Label());
			this->Wpn_id = (gcnew System::Windows::Forms::Label());
			this->wpn_name = (gcnew System::Windows::Forms::Label());
			this->Rounds_pm = (gcnew System::Windows::Forms::Label());
			this->wp_rpmBox1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->bottonPnl = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->datalabel = (gcnew System::Windows::Forms::Label());
			this->add_wpn_dtl_pnl->SuspendLayout();
			this->Rmv_wpnrcd_pnl->SuspendLayout();
			this->view_wpn_dtl_pnl->SuspendLayout();
			this->wpn_result_pnl->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rpmbox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->wp_rpmBox1))->BeginInit();
			this->bottonPnl->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainhdng_Wpns
			// 
			this->mainhdng_Wpns->AutoSize = true;
			this->mainhdng_Wpns->BackColor = System::Drawing::Color::Transparent;
			this->mainhdng_Wpns->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mainhdng_Wpns->ForeColor = System::Drawing::Color::White;
			this->mainhdng_Wpns->Location = System::Drawing::Point(325, 9);
			this->mainhdng_Wpns->Name = L"mainhdng_Wpns";
			this->mainhdng_Wpns->Size = System::Drawing::Size(211, 59);
			this->mainhdng_Wpns->TabIndex = 4;
			this->mainhdng_Wpns->Text = L"Weapons";
			// 
			// rmv_wpn_btn
			// 
			this->rmv_wpn_btn->BackColor = System::Drawing::Color::White;
			this->rmv_wpn_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->rmv_wpn_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->rmv_wpn_btn->FlatAppearance->BorderSize = 2;
			this->rmv_wpn_btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rmv_wpn_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rmv_wpn_btn->ForeColor = System::Drawing::Color::Black;
			this->rmv_wpn_btn->Location = System::Drawing::Point(88, 344);
			this->rmv_wpn_btn->Name = L"rmv_wpn_btn";
			this->rmv_wpn_btn->Size = System::Drawing::Size(166, 39);
			this->rmv_wpn_btn->TabIndex = 7;
			this->rmv_wpn_btn->Text = L"Remove Details";
			this->rmv_wpn_btn->UseVisualStyleBackColor = false;
			this->rmv_wpn_btn->Click += gcnew System::EventHandler(this, &Weapons::rmv_wpn_btn_Click);
			// 
			// view_wpn_btn
			// 
			this->view_wpn_btn->BackColor = System::Drawing::Color::White;
			this->view_wpn_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->view_wpn_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->view_wpn_btn->FlatAppearance->BorderSize = 2;
			this->view_wpn_btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->view_wpn_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->view_wpn_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->view_wpn_btn->Location = System::Drawing::Point(88, 239);
			this->view_wpn_btn->Name = L"view_wpn_btn";
			this->view_wpn_btn->Size = System::Drawing::Size(166, 39);
			this->view_wpn_btn->TabIndex = 8;
			this->view_wpn_btn->Text = L"View Details";
			this->view_wpn_btn->UseVisualStyleBackColor = false;
			this->view_wpn_btn->Click += gcnew System::EventHandler(this, &Weapons::view_wpn_btn_Click);
			// 
			// add_wpn_btn
			// 
			this->add_wpn_btn->BackColor = System::Drawing::Color::White;
			this->add_wpn_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->add_wpn_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->add_wpn_btn->FlatAppearance->BorderSize = 2;
			this->add_wpn_btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->add_wpn_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->add_wpn_btn->ForeColor = System::Drawing::Color::Black;
			this->add_wpn_btn->Location = System::Drawing::Point(88, 134);
			this->add_wpn_btn->Name = L"add_wpn_btn";
			this->add_wpn_btn->Size = System::Drawing::Size(166, 39);
			this->add_wpn_btn->TabIndex = 9;
			this->add_wpn_btn->Text = L"Add Details";
			this->add_wpn_btn->UseVisualStyleBackColor = false;
			this->add_wpn_btn->Click += gcnew System::EventHandler(this, &Weapons::add_wpn_btn_Click);
			// 
			// wpn_dbinfo
			// 
			this->wpn_dbinfo->BackColor = System::Drawing::Color::White;
			this->wpn_dbinfo->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->wpn_dbinfo->FlatAppearance->BorderSize = 2;
			this->wpn_dbinfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->wpn_dbinfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_dbinfo->ForeColor = System::Drawing::Color::Black;
			this->wpn_dbinfo->Location = System::Drawing::Point(554, 239);
			this->wpn_dbinfo->Name = L"wpn_dbinfo";
			this->wpn_dbinfo->Size = System::Drawing::Size(166, 39);
			this->wpn_dbinfo->TabIndex = 11;
			this->wpn_dbinfo->Text = L"Database Info";
			this->wpn_dbinfo->UseVisualStyleBackColor = false;
			this->wpn_dbinfo->Click += gcnew System::EventHandler(this, &Weapons::wpn_dbinfo_Click);
			// 
			// wpn_abt_Btn
			// 
			this->wpn_abt_Btn->BackColor = System::Drawing::Color::White;
			this->wpn_abt_Btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->wpn_abt_Btn->FlatAppearance->BorderSize = 2;
			this->wpn_abt_Btn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->wpn_abt_Btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_abt_Btn->ForeColor = System::Drawing::Color::Black;
			this->wpn_abt_Btn->Location = System::Drawing::Point(554, 134);
			this->wpn_abt_Btn->Name = L"wpn_abt_Btn";
			this->wpn_abt_Btn->Size = System::Drawing::Size(166, 39);
			this->wpn_abt_Btn->TabIndex = 12;
			this->wpn_abt_Btn->Text = L"About";
			this->wpn_abt_Btn->UseVisualStyleBackColor = false;
			this->wpn_abt_Btn->Click += gcnew System::EventHandler(this, &Weapons::wpn_abt_Btn_Click);
			// 
			// wpn_Exitbtn
			// 
			this->wpn_Exitbtn->BackColor = System::Drawing::Color::White;
			this->wpn_Exitbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->wpn_Exitbtn->FlatAppearance->BorderSize = 2;
			this->wpn_Exitbtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->wpn_Exitbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_Exitbtn->ForeColor = System::Drawing::Color::Black;
			this->wpn_Exitbtn->Location = System::Drawing::Point(554, 344);
			this->wpn_Exitbtn->Name = L"wpn_Exitbtn";
			this->wpn_Exitbtn->Size = System::Drawing::Size(166, 39);
			this->wpn_Exitbtn->TabIndex = 13;
			this->wpn_Exitbtn->Text = L"Exit";
			this->wpn_Exitbtn->UseVisualStyleBackColor = false;
			this->wpn_Exitbtn->Click += gcnew System::EventHandler(this, &Weapons::wpn_Exitbtn_Click);
			// 
			// add_wpn_dtl_pnl
			// 
			this->add_wpn_dtl_pnl->BackColor = System::Drawing::Color::Silver;
			this->add_wpn_dtl_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"add_wpn_dtl_pnl.BackgroundImage")));
			this->add_wpn_dtl_pnl->Controls->Add(this->resetBtn);
			this->add_wpn_dtl_pnl->Controls->Add(this->wpn_dtl_cls);
			this->add_wpn_dtl_pnl->Controls->Add(this->save_wpd_dtl);
			this->add_wpn_dtl_pnl->Controls->Add(this->wp_regBox1);
			this->add_wpn_dtl_pnl->Controls->Add(this->wp_ColorBox1);
			this->add_wpn_dtl_pnl->Controls->Add(this->wp_CategoryBox1);
			this->add_wpn_dtl_pnl->Controls->Add(this->wp_IdBox1);
			this->add_wpn_dtl_pnl->Controls->Add(this->wp_NameBox1);
			this->add_wpn_dtl_pnl->Controls->Add(this->Wpn_reg);
			this->add_wpn_dtl_pnl->Controls->Add(this->wpn_clr);
			this->add_wpn_dtl_pnl->Controls->Add(this->wpn_cat);
			this->add_wpn_dtl_pnl->Controls->Add(this->Wpn_id);
			this->add_wpn_dtl_pnl->Controls->Add(this->wpn_name);
			this->add_wpn_dtl_pnl->Controls->Add(this->Rounds_pm);
			this->add_wpn_dtl_pnl->Controls->Add(this->wp_rpmBox1);
			this->add_wpn_dtl_pnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->add_wpn_dtl_pnl->Location = System::Drawing::Point(0, 0);
			this->add_wpn_dtl_pnl->Name = L"add_wpn_dtl_pnl";
			this->add_wpn_dtl_pnl->Size = System::Drawing::Size(861, 570);
			this->add_wpn_dtl_pnl->TabIndex = 14;
			// 
			// Rmv_wpnrcd_pnl
			// 
			this->Rmv_wpnrcd_pnl->BackColor = System::Drawing::Color::Silver;
			this->Rmv_wpnrcd_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Rmv_wpnrcd_pnl.BackgroundImage")));
			this->Rmv_wpnrcd_pnl->Controls->Add(this->cls_wpnrcd_btn);
			this->Rmv_wpnrcd_pnl->Controls->Add(this->rmvwpn_Heading);
			this->Rmv_wpnrcd_pnl->Controls->Add(this->rmv_wpnrcd_btn);
			this->Rmv_wpnrcd_pnl->Controls->Add(this->wpn_id_tbox);
			this->Rmv_wpnrcd_pnl->Controls->Add(this->w_id_lbl);
			this->Rmv_wpnrcd_pnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Rmv_wpnrcd_pnl->Location = System::Drawing::Point(0, 0);
			this->Rmv_wpnrcd_pnl->Name = L"Rmv_wpnrcd_pnl";
			this->Rmv_wpnrcd_pnl->Size = System::Drawing::Size(861, 543);
			this->Rmv_wpnrcd_pnl->TabIndex = 16;
			this->Rmv_wpnrcd_pnl->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Weapons::Rmv_wpnrcd_pnl_Paint);
			// 
			// cls_wpnrcd_btn
			// 
			this->cls_wpnrcd_btn->BackColor = System::Drawing::Color::White;
			this->cls_wpnrcd_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->cls_wpnrcd_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cls_wpnrcd_btn->FlatAppearance->BorderSize = 2;
			this->cls_wpnrcd_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cls_wpnrcd_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cls_wpnrcd_btn->Location = System::Drawing::Point(727, 486);
			this->cls_wpnrcd_btn->Name = L"cls_wpnrcd_btn";
			this->cls_wpnrcd_btn->Size = System::Drawing::Size(122, 45);
			this->cls_wpnrcd_btn->TabIndex = 11;
			this->cls_wpnrcd_btn->Text = L"Close";
			this->cls_wpnrcd_btn->UseVisualStyleBackColor = false;
			this->cls_wpnrcd_btn->Click += gcnew System::EventHandler(this, &Weapons::cls_wpnrcd_btn_Click);
			// 
			// rmvwpn_Heading
			// 
			this->rmvwpn_Heading->AutoSize = true;
			this->rmvwpn_Heading->BackColor = System::Drawing::Color::Transparent;
			this->rmvwpn_Heading->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rmvwpn_Heading->ForeColor = System::Drawing::Color::White;
			this->rmvwpn_Heading->Location = System::Drawing::Point(242, 32);
			this->rmvwpn_Heading->Name = L"rmvwpn_Heading";
			this->rmvwpn_Heading->Size = System::Drawing::Size(376, 45);
			this->rmvwpn_Heading->TabIndex = 10;
			this->rmvwpn_Heading->Text = L"Remove Weapon Record";
			// 
			// rmv_wpnrcd_btn
			// 
			this->rmv_wpnrcd_btn->BackColor = System::Drawing::Color::White;
			this->rmv_wpnrcd_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->rmv_wpnrcd_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->rmv_wpnrcd_btn->FlatAppearance->BorderSize = 2;
			this->rmv_wpnrcd_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->rmv_wpnrcd_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.75F, System::Drawing::FontStyle::Bold));
			this->rmv_wpnrcd_btn->Location = System::Drawing::Point(319, 250);
			this->rmv_wpnrcd_btn->Name = L"rmv_wpnrcd_btn";
			this->rmv_wpnrcd_btn->Size = System::Drawing::Size(122, 45);
			this->rmv_wpnrcd_btn->TabIndex = 7;
			this->rmv_wpnrcd_btn->Text = L"REMOVE";
			this->rmv_wpnrcd_btn->UseVisualStyleBackColor = false;
			this->rmv_wpnrcd_btn->Click += gcnew System::EventHandler(this, &Weapons::rmv_wpnrcd_btn_Click);
			// 
			// wpn_id_tbox
			// 
			this->wpn_id_tbox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wpn_id_tbox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_id_tbox->Location = System::Drawing::Point(411, 163);
			this->wpn_id_tbox->Multiline = true;
			this->wpn_id_tbox->Name = L"wpn_id_tbox";
			this->wpn_id_tbox->Size = System::Drawing::Size(131, 38);
			this->wpn_id_tbox->TabIndex = 1;
			this->wpn_id_tbox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// w_id_lbl
			// 
			this->w_id_lbl->AutoSize = true;
			this->w_id_lbl->BackColor = System::Drawing::Color::Transparent;
			this->w_id_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->w_id_lbl->ForeColor = System::Drawing::Color::White;
			this->w_id_lbl->Location = System::Drawing::Point(222, 169);
			this->w_id_lbl->Name = L"w_id_lbl";
			this->w_id_lbl->Size = System::Drawing::Size(163, 29);
			this->w_id_lbl->TabIndex = 0;
			this->w_id_lbl->Text = L"Weapon ID =";
			// 
			// view_wpn_dtl_pnl
			// 
			this->view_wpn_dtl_pnl->BackColor = System::Drawing::Color::Silver;
			this->view_wpn_dtl_pnl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"view_wpn_dtl_pnl.BackgroundImage")));
			this->view_wpn_dtl_pnl->Controls->Add(this->wpn_result_pnl);
			this->view_wpn_dtl_pnl->Controls->Add(this->view_wpn_heading);
			this->view_wpn_dtl_pnl->Controls->Add(this->search_wpnid_btn);
			this->view_wpn_dtl_pnl->Controls->Add(this->wpnID_tbx);
			this->view_wpn_dtl_pnl->Controls->Add(this->label11);
			this->view_wpn_dtl_pnl->Controls->Add(this->cls_wpn_dtlbtn);
			this->view_wpn_dtl_pnl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->view_wpn_dtl_pnl->Location = System::Drawing::Point(0, 0);
			this->view_wpn_dtl_pnl->Name = L"view_wpn_dtl_pnl";
			this->view_wpn_dtl_pnl->Size = System::Drawing::Size(861, 570);
			this->view_wpn_dtl_pnl->TabIndex = 15;
			// 
			// wpn_result_pnl
			// 
			this->wpn_result_pnl->BackColor = System::Drawing::Color::Transparent;
			this->wpn_result_pnl->Controls->Add(this->rpmbox2);
			this->wpn_result_pnl->Controls->Add(this->label2);
			this->wpn_result_pnl->Controls->Add(this->regisBox2);
			this->wpn_result_pnl->Controls->Add(this->label10);
			this->wpn_result_pnl->Controls->Add(this->colorBox2);
			this->wpn_result_pnl->Controls->Add(this->label9);
			this->wpn_result_pnl->Controls->Add(this->categoryBox2);
			this->wpn_result_pnl->Controls->Add(this->wpn_cat_lbl);
			this->wpn_result_pnl->Controls->Add(this->nameBox2);
			this->wpn_result_pnl->Controls->Add(this->wpn_name_lbl);
			this->wpn_result_pnl->Location = System::Drawing::Point(0, 247);
			this->wpn_result_pnl->Name = L"wpn_result_pnl";
			this->wpn_result_pnl->Size = System::Drawing::Size(858, 233);
			this->wpn_result_pnl->TabIndex = 9;
			// 
			// rpmbox2
			// 
			this->rpmbox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rpmbox2->Location = System::Drawing::Point(657, 138);
			this->rpmbox2->Name = L"rpmbox2";
			this->rpmbox2->Size = System::Drawing::Size(179, 34);
			this->rpmbox2->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(469, 131);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(172, 30);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Rounds/minute";
			// 
			// regisBox2
			// 
			this->regisBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->regisBox2->Location = System::Drawing::Point(657, 53);
			this->regisBox2->Multiline = true;
			this->regisBox2->Name = L"regisBox2";
			this->regisBox2->Size = System::Drawing::Size(179, 39);
			this->regisBox2->TabIndex = 7;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(469, 53);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(181, 30);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Registration No.";
			// 
			// colorBox2
			// 
			this->colorBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->colorBox2->Location = System::Drawing::Point(229, 168);
			this->colorBox2->Multiline = true;
			this->colorBox2->Name = L"colorBox2";
			this->colorBox2->Size = System::Drawing::Size(190, 37);
			this->colorBox2->TabIndex = 5;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(12, 163);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(173, 30);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Weapon\'s Color";
			// 
			// categoryBox2
			// 
			this->categoryBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->categoryBox2->Location = System::Drawing::Point(229, 87);
			this->categoryBox2->Multiline = true;
			this->categoryBox2->Name = L"categoryBox2";
			this->categoryBox2->Size = System::Drawing::Size(190, 37);
			this->categoryBox2->TabIndex = 3;
			// 
			// wpn_cat_lbl
			// 
			this->wpn_cat_lbl->AutoSize = true;
			this->wpn_cat_lbl->BackColor = System::Drawing::Color::Transparent;
			this->wpn_cat_lbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_cat_lbl->ForeColor = System::Drawing::Color::White;
			this->wpn_cat_lbl->Location = System::Drawing::Point(12, 83);
			this->wpn_cat_lbl->Name = L"wpn_cat_lbl";
			this->wpn_cat_lbl->Size = System::Drawing::Size(214, 30);
			this->wpn_cat_lbl->TabIndex = 2;
			this->wpn_cat_lbl->Text = L"Weapon\'s Category";
			// 
			// nameBox2
			// 
			this->nameBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameBox2->Location = System::Drawing::Point(229, 15);
			this->nameBox2->Multiline = true;
			this->nameBox2->Name = L"nameBox2";
			this->nameBox2->Size = System::Drawing::Size(190, 37);
			this->nameBox2->TabIndex = 1;
			// 
			// wpn_name_lbl
			// 
			this->wpn_name_lbl->AutoSize = true;
			this->wpn_name_lbl->BackColor = System::Drawing::Color::Transparent;
			this->wpn_name_lbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_name_lbl->ForeColor = System::Drawing::Color::White;
			this->wpn_name_lbl->Location = System::Drawing::Point(12, 15);
			this->wpn_name_lbl->Name = L"wpn_name_lbl";
			this->wpn_name_lbl->Size = System::Drawing::Size(179, 30);
			this->wpn_name_lbl->TabIndex = 0;
			this->wpn_name_lbl->Text = L"Weapon\'s Name";
			// 
			// view_wpn_heading
			// 
			this->view_wpn_heading->AutoSize = true;
			this->view_wpn_heading->BackColor = System::Drawing::Color::Transparent;
			this->view_wpn_heading->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->view_wpn_heading->ForeColor = System::Drawing::Color::White;
			this->view_wpn_heading->Location = System::Drawing::Point(252, 29);
			this->view_wpn_heading->Name = L"view_wpn_heading";
			this->view_wpn_heading->Size = System::Drawing::Size(356, 45);
			this->view_wpn_heading->TabIndex = 10;
			this->view_wpn_heading->Text = L"View Weapon\'s Details";
			// 
			// search_wpnid_btn
			// 
			this->search_wpnid_btn->BackColor = System::Drawing::Color::White;
			this->search_wpnid_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->search_wpnid_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->search_wpnid_btn->FlatAppearance->BorderSize = 2;
			this->search_wpnid_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->search_wpnid_btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->search_wpnid_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->search_wpnid_btn->Location = System::Drawing::Point(35, 153);
			this->search_wpnid_btn->Name = L"search_wpnid_btn";
			this->search_wpnid_btn->Size = System::Drawing::Size(122, 45);
			this->search_wpnid_btn->TabIndex = 7;
			this->search_wpnid_btn->Text = L"Search";
			this->search_wpnid_btn->UseVisualStyleBackColor = false;
			this->search_wpnid_btn->Click += gcnew System::EventHandler(this, &Weapons::search_wpnid_btn_Click);
			// 
			// wpnID_tbx
			// 
			this->wpnID_tbx->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wpnID_tbx->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpnID_tbx->Location = System::Drawing::Point(215, 93);
			this->wpnID_tbx->Multiline = true;
			this->wpnID_tbx->Name = L"wpnID_tbx";
			this->wpnID_tbx->Size = System::Drawing::Size(131, 38);
			this->wpnID_tbx->TabIndex = 1;
			this->wpnID_tbx->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(28, 98);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(181, 29);
			this->label11->TabIndex = 0;
			this->label11->Text = L"Weapon\'s ID =";
			// 
			// cls_wpn_dtlbtn
			// 
			this->cls_wpn_dtlbtn->BackColor = System::Drawing::Color::White;
			this->cls_wpn_dtlbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->cls_wpn_dtlbtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cls_wpn_dtlbtn->FlatAppearance->BorderSize = 2;
			this->cls_wpn_dtlbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cls_wpn_dtlbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cls_wpn_dtlbtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cls_wpn_dtlbtn->Location = System::Drawing::Point(745, 496);
			this->cls_wpn_dtlbtn->Name = L"cls_wpn_dtlbtn";
			this->cls_wpn_dtlbtn->Size = System::Drawing::Size(110, 44);
			this->cls_wpn_dtlbtn->TabIndex = 11;
			this->cls_wpn_dtlbtn->Text = L"Close";
			this->cls_wpn_dtlbtn->UseVisualStyleBackColor = false;
			this->cls_wpn_dtlbtn->Click += gcnew System::EventHandler(this, &Weapons::cls_wpn_dtlbtn_Click);
			// 
			// resetBtn
			// 
			this->resetBtn->BackColor = System::Drawing::Color::White;
			this->resetBtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetBtn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetBtn->FlatAppearance->BorderSize = 2;
			this->resetBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetBtn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->resetBtn->Location = System::Drawing::Point(690, 95);
			this->resetBtn->Name = L"resetBtn";
			this->resetBtn->Size = System::Drawing::Size(118, 58);
			this->resetBtn->TabIndex = 7;
			this->resetBtn->Text = L"Reset";
			this->resetBtn->UseVisualStyleBackColor = false;
			this->resetBtn->Click += gcnew System::EventHandler(this, &Weapons::resetBtn_Click);
			// 
			// wpn_dtl_cls
			// 
			this->wpn_dtl_cls->BackColor = System::Drawing::Color::White;
			this->wpn_dtl_cls->Cursor = System::Windows::Forms::Cursors::Hand;
			this->wpn_dtl_cls->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->wpn_dtl_cls->FlatAppearance->BorderSize = 2;
			this->wpn_dtl_cls->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->wpn_dtl_cls->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_dtl_cls->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->wpn_dtl_cls->Location = System::Drawing::Point(690, 253);
			this->wpn_dtl_cls->Name = L"wpn_dtl_cls";
			this->wpn_dtl_cls->Size = System::Drawing::Size(118, 58);
			this->wpn_dtl_cls->TabIndex = 7;
			this->wpn_dtl_cls->Text = L"Close";
			this->wpn_dtl_cls->UseVisualStyleBackColor = false;
			this->wpn_dtl_cls->Click += gcnew System::EventHandler(this, &Weapons::wpn_dtl_cls_Click);
			// 
			// save_wpd_dtl
			// 
			this->save_wpd_dtl->BackColor = System::Drawing::Color::White;
			this->save_wpd_dtl->Cursor = System::Windows::Forms::Cursors::Hand;
			this->save_wpd_dtl->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->save_wpd_dtl->FlatAppearance->BorderSize = 2;
			this->save_wpd_dtl->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->save_wpd_dtl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->save_wpd_dtl->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->save_wpd_dtl->Location = System::Drawing::Point(690, 174);
			this->save_wpd_dtl->Name = L"save_wpd_dtl";
			this->save_wpd_dtl->Size = System::Drawing::Size(118, 58);
			this->save_wpd_dtl->TabIndex = 7;
			this->save_wpd_dtl->Text = L"Save";
			this->save_wpd_dtl->UseVisualStyleBackColor = false;
			this->save_wpd_dtl->Click += gcnew System::EventHandler(this, &Weapons::save_wpd_dtl_Click);
			// 
			// wp_regBox1
			// 
			this->wp_regBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wp_regBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wp_regBox1->Location = System::Drawing::Point(334, 325);
			this->wp_regBox1->Name = L"wp_regBox1";
			this->wp_regBox1->Size = System::Drawing::Size(124, 34);
			this->wp_regBox1->TabIndex = 1;
			// 
			// wp_ColorBox1
			// 
			this->wp_ColorBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wp_ColorBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wp_ColorBox1->Location = System::Drawing::Point(334, 258);
			this->wp_ColorBox1->Name = L"wp_ColorBox1";
			this->wp_ColorBox1->Size = System::Drawing::Size(124, 34);
			this->wp_ColorBox1->TabIndex = 1;
			// 
			// wp_CategoryBox1
			// 
			this->wp_CategoryBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wp_CategoryBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wp_CategoryBox1->Location = System::Drawing::Point(334, 203);
			this->wp_CategoryBox1->Name = L"wp_CategoryBox1";
			this->wp_CategoryBox1->Size = System::Drawing::Size(124, 34);
			this->wp_CategoryBox1->TabIndex = 1;
			// 
			// wp_IdBox1
			// 
			this->wp_IdBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wp_IdBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wp_IdBox1->Location = System::Drawing::Point(334, 142);
			this->wp_IdBox1->Name = L"wp_IdBox1";
			this->wp_IdBox1->Size = System::Drawing::Size(124, 34);
			this->wp_IdBox1->TabIndex = 1;
			// 
			// wp_NameBox1
			// 
			this->wp_NameBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->wp_NameBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wp_NameBox1->Location = System::Drawing::Point(334, 84);
			this->wp_NameBox1->Name = L"wp_NameBox1";
			this->wp_NameBox1->Size = System::Drawing::Size(124, 34);
			this->wp_NameBox1->TabIndex = 1;
			// 
			// Wpn_reg
			// 
			this->Wpn_reg->AutoSize = true;
			this->Wpn_reg->BackColor = System::Drawing::Color::Transparent;
			this->Wpn_reg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Wpn_reg->ForeColor = System::Drawing::Color::White;
			this->Wpn_reg->Location = System::Drawing::Point(35, 325);
			this->Wpn_reg->Name = L"Wpn_reg";
			this->Wpn_reg->Size = System::Drawing::Size(201, 24);
			this->Wpn_reg->TabIndex = 0;
			this->Wpn_reg->Text = L"Registration Number";
			// 
			// wpn_clr
			// 
			this->wpn_clr->AutoSize = true;
			this->wpn_clr->BackColor = System::Drawing::Color::Transparent;
			this->wpn_clr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_clr->ForeColor = System::Drawing::Color::White;
			this->wpn_clr->Location = System::Drawing::Point(35, 264);
			this->wpn_clr->Name = L"wpn_clr";
			this->wpn_clr->Size = System::Drawing::Size(159, 24);
			this->wpn_clr->TabIndex = 0;
			this->wpn_clr->Text = L"Weapon\'s Color";
			// 
			// wpn_cat
			// 
			this->wpn_cat->AutoSize = true;
			this->wpn_cat->BackColor = System::Drawing::Color::Transparent;
			this->wpn_cat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_cat->ForeColor = System::Drawing::Color::White;
			this->wpn_cat->Location = System::Drawing::Point(35, 203);
			this->wpn_cat->Name = L"wpn_cat";
			this->wpn_cat->Size = System::Drawing::Size(198, 24);
			this->wpn_cat->TabIndex = 0;
			this->wpn_cat->Text = L"Weapon\'s Category ";
			// 
			// Wpn_id
			// 
			this->Wpn_id->AutoSize = true;
			this->Wpn_id->BackColor = System::Drawing::Color::Transparent;
			this->Wpn_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Wpn_id->ForeColor = System::Drawing::Color::White;
			this->Wpn_id->Location = System::Drawing::Point(35, 142);
			this->Wpn_id->Name = L"Wpn_id";
			this->Wpn_id->Size = System::Drawing::Size(128, 24);
			this->Wpn_id->TabIndex = 0;
			this->Wpn_id->Text = L"Weapon\'s ID";
			// 
			// wpn_name
			// 
			this->wpn_name->AutoSize = true;
			this->wpn_name->BackColor = System::Drawing::Color::Transparent;
			this->wpn_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wpn_name->ForeColor = System::Drawing::Color::White;
			this->wpn_name->Location = System::Drawing::Point(35, 81);
			this->wpn_name->Name = L"wpn_name";
			this->wpn_name->Size = System::Drawing::Size(164, 24);
			this->wpn_name->TabIndex = 0;
			this->wpn_name->Text = L"Weapon\'s Name";
			// 
			// Rounds_pm
			// 
			this->Rounds_pm->AutoSize = true;
			this->Rounds_pm->BackColor = System::Drawing::Color::Transparent;
			this->Rounds_pm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Rounds_pm->ForeColor = System::Drawing::Color::White;
			this->Rounds_pm->Location = System::Drawing::Point(35, 386);
			this->Rounds_pm->Name = L"Rounds_pm";
			this->Rounds_pm->Size = System::Drawing::Size(179, 24);
			this->Rounds_pm->TabIndex = 12;
			this->Rounds_pm->Text = L"Round Per Minute";
			// 
			// wp_rpmBox1
			// 
			this->wp_rpmBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->wp_rpmBox1->Location = System::Drawing::Point(334, 381);
			this->wp_rpmBox1->Name = L"wp_rpmBox1";
			this->wp_rpmBox1->Size = System::Drawing::Size(124, 34);
			this->wp_rpmBox1->TabIndex = 16;
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
			this->bottonPnl->TabIndex = 13;
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
			// Weapons
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(861, 570);
			this->Controls->Add(this->Rmv_wpnrcd_pnl);
			this->Controls->Add(this->bottonPnl);
			this->Controls->Add(this->view_wpn_dtl_pnl);
			this->Controls->Add(this->add_wpn_dtl_pnl);
			this->Controls->Add(this->wpn_dbinfo);
			this->Controls->Add(this->wpn_abt_Btn);
			this->Controls->Add(this->wpn_Exitbtn);
			this->Controls->Add(this->rmv_wpn_btn);
			this->Controls->Add(this->view_wpn_btn);
			this->Controls->Add(this->add_wpn_btn);
			this->Controls->Add(this->mainhdng_Wpns);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Weapons";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Weapons";
			this->add_wpn_dtl_pnl->ResumeLayout(false);
			this->add_wpn_dtl_pnl->PerformLayout();
			this->Rmv_wpnrcd_pnl->ResumeLayout(false);
			this->Rmv_wpnrcd_pnl->PerformLayout();
			this->view_wpn_dtl_pnl->ResumeLayout(false);
			this->view_wpn_dtl_pnl->PerformLayout();
			this->wpn_result_pnl->ResumeLayout(false);
			this->wpn_result_pnl->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rpmbox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->wp_rpmBox1))->EndInit();
			this->bottonPnl->ResumeLayout(false);
			this->bottonPnl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

private: System::Void add_wpn_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	add_wpn_dtl_pnl->Show();
}


private: System::Void save_wpd_dtl_Click(System::Object^ sender, System::EventArgs^ e) 
{	
	int wid, wrpm; 
	try
	{
		wid = System::Convert::ToInt16(wp_IdBox1->Text);
		wrpm = System::Convert::ToInt16(wp_rpmBox1->Value); 
		if (isDbConnected==true)
		{
			if (!IDcheckDb(wid))
			{
				MessageBox::Show("A record with this weapon ID already exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return; 
			}
			addDetailsDatabase(wp_NameBox1->Text, wid, wp_CategoryBox1->Text, wp_ColorBox1->Text, wp_regBox1->Text, wrpm);
		}
		else
		{
			/*if (!IDCheckCSV(wid)) {
				MessageBox::Show("A record with this weapon ID already exists.", "PrimaryKeyError", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}*/
			addDetailsCSV(wp_NameBox1->Text, wid, wp_CategoryBox1->Text, wp_ColorBox1->Text, wp_regBox1->Text, wrpm);
			
		}
	}
	catch (...)
	{
		MessageBox::Show("ID and Rounds per minutes can only be digits", "Incorrect Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
}


private: System::Void wpn_dtl_cls_Click(System::Object^ sender, System::EventArgs^ e) 
{
	add_wpn_dtl_pnl->Hide();
}


private: System::Void view_wpn_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	view_wpn_dtl_pnl->Show();
}


private: System::Void search_wpnid_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (wpnID_tbx->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invaid ID", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(wpnID_tbx->Text);
		if (isDbConnected == true)
		{
			viewDetailsDatabase(id);
		}
		else
		{
			viewDetailsCSV(id);
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		wpnID_tbx->Clear();
	}
}


private: System::Void cls_wpn_dtlbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	view_wpn_dtl_pnl->Hide();
	wpn_result_pnl->Hide();
}


private: System::Void rmv_wpn_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	add_wpn_dtl_pnl->Hide();
	view_wpn_dtl_pnl->Hide();
	wpn_result_pnl->Hide();
	Rmv_wpnrcd_pnl->Show();
}
private: System::Void rmv_wpnrcd_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (wpn_id_tbox->Text == "")
	{
		MessageBox::Show("This field requires data.", "Invalid ID", MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	try
	{
		int id = System::Convert::ToInt16(wpn_id_tbox->Text);
		if (isDbConnected == true)
		{
			removedetailDatabase(id);
		}
		else
		{
			removeDetailCSV(id); 
		}
	}
	catch (...)
	{
		MessageBox::Show("Enter a numeric value", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
		wpn_id_tbox->Clear();
	}
}



private: System::Void cls_wpnrcd_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Rmv_wpnrcd_pnl->Hide();
}


private: System::Void wpn_abt_Btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	MessageBox::Show("This Tab Stores the information of all the weapons stored in the inventory. Each weapon is distinguished by its unique Weapon ID . Other Details are also Stored ", "Weapon's Info",
		MessageBoxButtons::OK, MessageBoxIcon::Information);
}




private: System::Void wpn_dbinfo_Click(System::Object^ sender, System::EventArgs^ e) 
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


private: System::Void wpn_Exitbtn_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Weapons::Hide();
}
private: System::Void Rmv_wpnrcd_pnl_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}

private: System::Void resetBtn_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
