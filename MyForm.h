#pragma once
#include"Main.h"

namespace CMS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			panelterms->Hide();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label3;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ homebtn;
	private: System::Windows::Forms::Button^ abtbutton;


	private: System::Windows::Forms::Button^ updatebtn;
	private: System::Windows::Forms::Button^ helpbtn;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Panel^ panelterms;

	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Panel^ designPnl;
	private: System::Windows::Forms::Label^ label8;




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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->homebtn = (gcnew System::Windows::Forms::Button());
			this->abtbutton = (gcnew System::Windows::Forms::Button());
			this->updatebtn = (gcnew System::Windows::Forms::Button());
			this->helpbtn = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panelterms = (gcnew System::Windows::Forms::Panel());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->designPnl = (gcnew System::Windows::Forms::Panel());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panelterms->SuspendLayout();
			this->designPnl->SuspendLayout();
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label3->Font = (gcnew System::Drawing::Font(L"Cambria", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(35, 215);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(622, 57);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Crime Management System";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::otherclicks);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(750, 110);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 45);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Sign In";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::otherclicks);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(1)), static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Location = System::Drawing::Point(750, 198);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(297, 40);
			this->panel1->TabIndex = 4;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(1)), static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.25F));
			this->textBox3->ForeColor = System::Drawing::Color::White;
			this->textBox3->Location = System::Drawing::Point(7, 6);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(277, 24);
			this->textBox3->TabIndex = 5;
			this->textBox3->Text = L"Username";
			this->textBox3->Click += gcnew System::EventHandler(this, &MyForm::textBox3_Click);
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox3_KeyPress);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(1)), static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Location = System::Drawing::Point(750, 251);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(297, 46);
			this->panel2->TabIndex = 7;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(1)), static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->textBox2->ForeColor = System::Drawing::Color::White;
			this->textBox2->Location = System::Drawing::Point(8, 11);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(277, 22);
			this->textBox2->TabIndex = 5;
			this->textBox2->Text = L"Password";
			this->textBox2->UseSystemPasswordChar = true;
			this->textBox2->Click += gcnew System::EventHandler(this, &MyForm::textBox2_Click);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox2_KeyPress);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(922, 359);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Terms and Conditions";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::White;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Bold));
			this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(1)), static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->button1->Location = System::Drawing::Point(769, 383);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(116, 38);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Sign In";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Transparent;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::AliceBlue;
			this->button2->FlatAppearance->BorderSize = 2;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(907, 383);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(116, 38);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Exit";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// homebtn
			// 
			this->homebtn->BackColor = System::Drawing::Color::Transparent;
			this->homebtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->homebtn->FlatAppearance->BorderSize = 0;
			this->homebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->homebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->homebtn->ForeColor = System::Drawing::Color::White;
			this->homebtn->Location = System::Drawing::Point(114, 39);
			this->homebtn->Name = L"homebtn";
			this->homebtn->Size = System::Drawing::Size(88, 31);
			this->homebtn->TabIndex = 11;
			this->homebtn->Text = L"Home";
			this->homebtn->UseVisualStyleBackColor = false;
			this->homebtn->Click += gcnew System::EventHandler(this, &MyForm::homebtn_Click);
			// 
			// abtbutton
			// 
			this->abtbutton->BackColor = System::Drawing::Color::Transparent;
			this->abtbutton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->abtbutton->FlatAppearance->BorderSize = 0;
			this->abtbutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->abtbutton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->abtbutton->ForeColor = System::Drawing::Color::White;
			this->abtbutton->Location = System::Drawing::Point(364, 39);
			this->abtbutton->Name = L"abtbutton";
			this->abtbutton->Size = System::Drawing::Size(88, 31);
			this->abtbutton->TabIndex = 12;
			this->abtbutton->Text = L"About";
			this->abtbutton->UseVisualStyleBackColor = false;
			this->abtbutton->Click += gcnew System::EventHandler(this, &MyForm::abtbutton_Click);
			// 
			// updatebtn
			// 
			this->updatebtn->BackColor = System::Drawing::Color::Transparent;
			this->updatebtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->updatebtn->FlatAppearance->BorderSize = 0;
			this->updatebtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->updatebtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->updatebtn->ForeColor = System::Drawing::Color::White;
			this->updatebtn->Location = System::Drawing::Point(239, 39);
			this->updatebtn->Name = L"updatebtn";
			this->updatebtn->Size = System::Drawing::Size(88, 31);
			this->updatebtn->TabIndex = 13;
			this->updatebtn->Text = L"Updates";
			this->updatebtn->UseVisualStyleBackColor = false;
			this->updatebtn->Click += gcnew System::EventHandler(this, &MyForm::updatebtn_Click);
			// 
			// helpbtn
			// 
			this->helpbtn->BackColor = System::Drawing::Color::Transparent;
			this->helpbtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->helpbtn->FlatAppearance->BorderSize = 0;
			this->helpbtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->helpbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->helpbtn->ForeColor = System::Drawing::Color::White;
			this->helpbtn->Location = System::Drawing::Point(489, 39);
			this->helpbtn->Name = L"helpbtn";
			this->helpbtn->Size = System::Drawing::Size(88, 31);
			this->helpbtn->TabIndex = 14;
			this->helpbtn->Text = L"Help";
			this->helpbtn->UseVisualStyleBackColor = false;
			this->helpbtn->Click += gcnew System::EventHandler(this, &MyForm::helpbtn_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Location = System::Drawing::Point(757, 359);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(165, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"By signing in, you agree to our";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::otherclicks);
			// 
			// panelterms
			// 
			this->panelterms->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panelterms.BackgroundImage")));
			this->panelterms->Controls->Add(this->button7);
			this->panelterms->Controls->Add(this->textBox1);
			this->panelterms->Controls->Add(this->label4);
			this->panelterms->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelterms->Location = System::Drawing::Point(0, 0);
			this->panelterms->Name = L"panelterms";
			this->panelterms->Size = System::Drawing::Size(1188, 681);
			this->panelterms->TabIndex = 17;
			this->panelterms->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelterms_Paint);
			// 
			// button7
			// 
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(3)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->button7->Location = System::Drawing::Point(708, 522);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(111, 47);
			this->button7->TabIndex = 2;
			this->button7->Text = L"OK";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click_1);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(3)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::Color::White;
			this->textBox1->Location = System::Drawing::Point(101, 118);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(718, 379);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = resources->GetString(L"textBox1.Text");
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28, System::Drawing::FontStyle::Bold));
			this->label4->Location = System::Drawing::Point(94, 38);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(417, 51);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Terms And Conditions";
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::Silver;
			this->label6->Location = System::Drawing::Point(49, 279);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(608, 127);
			this->label6->TabIndex = 18;
			this->label6->Text = resources->GetString(L"label6.Text");
			this->label6->Click += gcnew System::EventHandler(this, &MyForm::otherclicks);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Bauhaus 93", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0), true));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(1, 6);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(109, 18);
			this->label7->TabIndex = 5;
			this->label7->Text = L"designed by : ";
			// 
			// designPnl
			// 
			this->designPnl->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(54)));
			this->designPnl->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->designPnl->Controls->Add(this->label8);
			this->designPnl->Controls->Add(this->label7);
			this->designPnl->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->designPnl->Location = System::Drawing::Point(0, 651);
			this->designPnl->Name = L"designPnl";
			this->designPnl->Size = System::Drawing::Size(1188, 30);
			this->designPnl->TabIndex = 29;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(107, 5);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(169, 17);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Devanshi Vishwakarma";
			this->label8->UseMnemonic = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1188, 681);
			this->Controls->Add(this->designPnl);
			this->Controls->Add(this->panelterms);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->helpbtn);
			this->Controls->Add(this->updatebtn);
			this->Controls->Add(this->abtbutton);
			this->Controls->Add(this->homebtn);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label3);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0), true));
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Crime Management System";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Click += gcnew System::EventHandler(this, &MyForm::otherclicks);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panelterms->ResumeLayout(false);
			this->panelterms->PerformLayout();
			this->designPnl->ResumeLayout(false);
			this->designPnl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void textBox3_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (textBox3->Text == "Username")
		{
			textBox3->Text = "";
		}
		if (textBox2->Text == "")
		{
			textBox2->Text = "Password";
		}

	}
	private: System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (textBox2->Text == "Password")
		{
			textBox2->Text = "";
		}
		if (textBox3->Text == "")
		{
			textBox3->Text = "Username";
		}
	}


	private: System::Void otherclicks(System::Object^ sender, System::EventArgs^ e) 
	{
		if (textBox3->Text == "")
		{
			textBox3->Text = "Username";
		}
		if (textBox2->Text == "")
		{
			textBox2->Text = "Password";
		}
	}
	private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (textBox3 ->Text != "Username")
		{
			String^ username = "admin";
			String^ password = "admin";
			if (textBox3->Text != username && textBox2->Text != password)
			{
				MessageBox::Show("Incorrect Username and Password", "Wrong Credentials", MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}

			else if (textBox3->Text != username)
			{
				MessageBox::Show("Invalid User", "Wrong Credentials", MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}

			else if (textBox2->Text != password)
			{
				MessageBox::Show("Invalid Password", "Wrong Credentials", MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}

			else
			{
				this->Hide();
				Main^ main = gcnew Main();
				main->Show();
				/*MessageBox::Show("Sign In Successful", "Access Granted", MessageBoxButtons::OK,
					MessageBoxIcon::Asterisk);
				Application::Exit();*/
			}
		}
		else
		{
			MessageBox::Show("Invalid username. Try Again", "Wrong Credentials", MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		if (textBox3->Text == "")
		{
			textBox3->Text = "Username";
		}
		if (textBox2->Text == "")
		{
			textBox2->Text = "Password";
		}

	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Application::Exit();
	}

	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		panelterms->Show();
	}
	private: System::Void button7_Click_1(System::Object^ sender, System::EventArgs^ e) {
		panelterms->Hide();
	}
		   //EVENTS//
	private: System::Void panelterms_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
	}
		   bool dragging;
		   Point Offset;
	private: System::Void MyForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (dragging)
		{
			Point CurrentScreenPosition = PointToScreen(Point(e->X, e->Y));
			Location = Point(CurrentScreenPosition.X - Offset.X, CurrentScreenPosition.Y - Offset.Y);
		}
	}
	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		dragging = true;
		Offset.X = e->X;
		Offset.Y = e->Y;
	}

	private: System::Void MyForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		dragging = false;
	}

private: System::Void textBox3_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {

	if (e->KeyChar == int(Keys::Enter))
	{
		textBox2->Focus(); 
	}
}
private: System::Void textBox2_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == int(Keys::Enter))
	{
		button1->PerformClick(); 
	}
}

private: System::Void updatebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("No Updates Available", "Check For Updates", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void abtbutton_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("This C++ windows application is designed using dotnet framework. Data Storage Options include MYSQL Server and CSV File Format.", "About", MessageBoxButtons::OK, MessageBoxIcon::Information);
	
}	   

private: System::Void homebtn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Sign In to access the homepage", "Home", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void helpbtn_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("You need to have atleast DOTNET Framework 4.7 to run this application smoothly. MYSQL Server 8.0 is used as a database.\n\n 1) Create table with the given queries.txt file in SQL Queries Folder. \n\n 2)Connect to database using your MYSQL SERVER Username and Password . \n\n 3)If you don't have MYSQL installed , CSV File Storage can also be used . \n\n 4)To change your username and password contact the developers . ", "Help Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);

}
};

}