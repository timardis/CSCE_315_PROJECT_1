#pragma once
#include <msclr\marshal_cppstd.h>
#include "View.h"
#include "Parser.h"

namespace DatabaseGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
			
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox4;


	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox6;

	private: System::Windows::Forms::TextBox^  textBox5;




	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  btn_add;

		/// Parser pointer
		Parser* parser;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			parser = new Parser();

			parser->process_input("OPEN user_data;");
			parser->process_input("OPEN assignment_data;");
			parser->process_input("OPEN section_data;");

			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->btn_add = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Add", L"View" });
			this->comboBox1->Location = System::Drawing::Point(26, 21);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(123, 21);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &GUI::comboBox1_SelectedIndexChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Assignments", L"Students", L"Sections", L"Grades",
					L"Roster"
			});
			this->comboBox2->Location = System::Drawing::Point(26, 48);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(122, 21);
			this->comboBox2->TabIndex = 1;
			this->comboBox2->Visible = false;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &GUI::comboBox2_SelectedIndexChanged);
			// 
			// comboBox3
			// 
			this->comboBox3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Assignments", L"Students", L"Sections", L"Grades",
					L"Roster", L"Upperclassmen", L"Underclassmen", L"Assignment Info", L"Contact Info"
			});
			this->comboBox3->Location = System::Drawing::Point(26, 48);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(122, 21);
			this->comboBox3->TabIndex = 2;
			this->comboBox3->Visible = false;
			this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &GUI::comboBox3_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(398, 21);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(259, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Visible = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(398, 47);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(259, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->Visible = false;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(398, 104);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(259, 20);
			this->textBox4->TabIndex = 6;
			this->textBox4->Visible = false;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(398, 75);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(259, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->Visible = false;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(398, 157);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(259, 20);
			this->textBox6->TabIndex = 8;
			this->textBox6->Visible = false;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(398, 130);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(259, 20);
			this->textBox5->TabIndex = 7;
			this->textBox5->Visible = false;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(398, 184);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(259, 20);
			this->textBox7->TabIndex = 9;
			this->textBox7->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(284, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 10;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(284, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"label2";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label2->Visible = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(284, 78);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"label3";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label3->Visible = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(284, 106);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"label4";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label4->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(284, 132);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"label5";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label5->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(284, 160);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"label6";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(284, 186);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(35, 13);
			this->label7->TabIndex = 16;
			this->label7->Text = L"label7";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label7->Visible = false;
			// 
			// btn_add
			// 
			this->btn_add->Location = System::Drawing::Point(484, 210);
			this->btn_add->Name = L"btn_add";
			this->btn_add->Size = System::Drawing::Size(94, 26);
			this->btn_add->TabIndex = 17;
			this->btn_add->Text = L"Add";
			this->btn_add->UseVisualStyleBackColor = true;
			this->btn_add->Click += gcnew System::EventHandler(this, &GUI::btn_add_Click);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(669, 249);
			this->Controls->Add(this->btn_add);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			// Options: (0) Add, (1) View
					 switch (comboBox1->SelectedIndex) {
					 case 0:
						 comboBox2->Show();
						 comboBox3->Hide();
						 break;
					 case 1:
						 hide_all_7();
						 comboBox2->Hide();
						 comboBox3->Show();
						 break;
					 }
		}

		private: System::Void show_all_7() {
					 textBox1->Show();
					 textBox2->Show();
					 textBox3->Show();
					 textBox4->Show();
					 textBox5->Show();
					 textBox6->Show();
					 textBox7->Show();

					 label1->Show();
					 label2->Show();
					 label3->Show();
					 label4->Show();
					 label5->Show();
					 label6->Show();
					 label7->Show();
		}

		private: System::Void hide_all_7() {
					 textBox1->Hide();
					 textBox2->Hide();
					 textBox3->Hide();
					 textBox4->Hide();
					 textBox5->Hide();
					 textBox6->Hide();
					 textBox7->Hide();

					 label1->Hide();
					 label2->Hide();
					 label3->Hide();
					 label4->Hide();
					 label5->Hide();
					 label6->Hide();
					 label7->Hide();
		}

		private: System::Void clear_all_7() {
					 textBox1->Clear();
					 textBox2->Clear();
					 textBox3->Clear();
					 textBox4->Clear();
					 textBox5->Clear();
					 textBox6->Clear();
					 textBox7->Clear();
		}

		private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			// Options: (0) Assignments, (1) Students, (2) Sections, (3) Grades, (4) Roster
					 clear_all_7();

						 switch (comboBox2->SelectedIndex) {
						 case 0:
							 label1->Text = "Assignment ID";
							 label2->Text = "Assignment Name";
							 label3->Text = "Points";
							 label4->Text = "Date Assigned";
							 label5->Text = "Date Due";
							 label6->Text = "Type";
							 label7->Text = "Weight";

							 show_all_7();
							 break;
						 case 1:
							 label1->Text = "Student ID";
							 label2->Text = "Student Name";
							 label3->Text = "Address";
							 label4->Text = "Phone Number";
							 label5->Text = "Email";
							 label6->Text = "Classification";
							 label7->Text = "Gender";

							 show_all_7();
							 break;
						 case 2:
							 label1->Text = "Section ID";
							 label2->Text = "Section Name";
							 label3->Text = "Start Time";
							 label4->Text = "End Time";
							 label5->Text = "Day";
							 label6->Text = "Building";
							 label7->Text = "Room";

							 show_all_7();
							 break;
						 case 3:
							 hide_all_7();

							 label1->Text = "Student ID";
							 label2->Text = "Assignment ID";
							 label3->Text = "Grade";

							 label1->Show();
							 label2->Show();
							 label3->Show();

							 textBox1->Show();
							 textBox2->Show();
							 textBox3->Show();

							 break;
						 case 4:
							 hide_all_7();

							 label1->Text = "Student ID";
							 label2->Text = "Section ID";

							 label1->Show();
							 label2->Show();

							 textBox1->Show();
							 textBox2->Show();

							 break;
						 }
		}

		private: System::Void comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
					 View^ popup = gcnew View();
					 popup->Show();
		}

		private: std::string toString(String^ _string) {
					 msclr::interop::marshal_context context;
					 return context.marshal_as<std::string>(_string);
		}

		private: System::String^ fromString(std::string _string) {
					 return gcnew String(_string.c_str());
		}

		private: System::Void btn_add_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Options: (0) Assignments, (1) Students, (2) Sections, (3) Grades, (4) Roster
					 string line = "INSERT INTO ";
					 switch (comboBox2->SelectedIndex) {
					 case 0:
						 line += "assignment_data VALUES FROM ("
							 + toString(textBox1->Text) + ", \""
							 + toString(textBox2->Text) + "\", "
							 + toString(textBox3->Text) + ", \""
							 + toString(textBox4->Text) + "\", \""
							 + toString(textBox5->Text) + "\", \""
							 + toString(textBox6->Text) + "\", \""
							 + toString(textBox7->Text) + "\");";
						 break;
					 case 1:
						 line += "user_data VALUES FROM ("
							 + toString(textBox1->Text) + ", \""
							 + toString(textBox2->Text) + "\", \""
							 + toString(textBox3->Text) + "\", \""
							 + toString(textBox4->Text) + "\", \""
							 + toString(textBox5->Text) + "\", \""
							 + toString(textBox6->Text) + "\", \""
							 + toString(textBox7->Text) + "\");";
						 break;
					 case 2:
						 line += "section_data VALUES FROM ("
							 + toString(textBox1->Text) + ", \""
							 + toString(textBox2->Text) + "\", \""
							 + toString(textBox3->Text) + "\", \""
							 + toString(textBox4->Text) + "\", \""
							 + toString(textBox5->Text) + "\", \""
							 + toString(textBox6->Text) + "\", \""
							 + toString(textBox7->Text) + "\");";
						 break;
					 case 3:
						 line += "grade_data VALUES FROM ("
							 + toString(textBox1->Text) + ", "
							 + toString(textBox2->Text) + ", "
							 + toString(textBox3->Text) + ");";
						 break;
					 case 4:
						 line += "roster_data VALUES FROM (" 
							 + toString(textBox1->Text) + ", "
							 + toString(textBox2->Text) + ");";
						 break;
					 }
					 parser->process_input(line);
					 parser->process_input("WRITE section_data");
					 clear_all_7();
		}
};
}
