#pragma once

#include "Parser.h"
#include <msclr\marshal_cppstd.h>

namespace GUI_App {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TableForm
	/// </summary>
	public ref class TableForm : public System::Windows::Forms::Form
	{
	public:
		TableForm(void)
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
		~TableForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  combo_select;
	protected:
	private: System::Windows::Forms::DataGridView^  view_table;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		Parser *parser;
	private: System::Windows::Forms::Button^  button1;
			 std::string *current_table;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->combo_select = (gcnew System::Windows::Forms::ComboBox());
			this->view_table = (gcnew System::Windows::Forms::DataGridView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->view_table))->BeginInit();
			this->SuspendLayout();
			// 
			// combo_select
			// 
			this->combo_select->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->combo_select->FormattingEnabled = true;
			this->combo_select->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Students", L"Assignments", L"Sections", L"Roster",
					L"Grades", L"Detailed Grades", L"Contact Info", L"Upperclassmen", L"Underclassmen"
			});
			this->combo_select->Location = System::Drawing::Point(12, 9);
			this->combo_select->Name = L"combo_select";
			this->combo_select->Size = System::Drawing::Size(111, 21);
			this->combo_select->TabIndex = 0;
			this->combo_select->SelectedIndexChanged += gcnew System::EventHandler(this, &TableForm::combo_select_SelectedIndexChanged);
			// 
			// view_table
			// 
			this->view_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->view_table->Location = System::Drawing::Point(12, 36);
			this->view_table->Name = L"view_table";
			this->view_table->Size = System::Drawing::Size(869, 418);
			this->view_table->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(38, 472);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 36);
			this->button1->TabIndex = 2;
			this->button1->Text = L"New year";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TableForm::button1_Click);
			// 
			// TableForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(893, 529);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->view_table);
			this->Controls->Add(this->combo_select);
			this->Name = L"TableForm";
			this->Text = L"Class Helper";
			this->Load += gcnew System::EventHandler(this, &TableForm::TableForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->view_table))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	/* Convert a managed String to an std::string */
	private: std::string toString(String^ _string) {
				 msclr::interop::marshal_context context;
				 return context.marshal_as<std::string>(_string);
	}

	/* Convert an std::string to a managed String */
	private: System::String^ fromString(std::string _string) {
				 return gcnew String(_string.c_str());
	}

	private: System::Void update_view(std::string table_name) {
				 std::string command;

				 if (table_name == "upperclassmen" || table_name == "underclassmen")
				 {
					 command = "senior <- select (classification == \"SENIOR\") user_data;"; 
					 parser->process_input(command);
					 command = "junior <- select(classification == \"JUNIOR\") user_data;";
					 parser->process_input(command);
					 command = "upperclassmen <- junior + senior;";
					 parser->process_input(command);
					 command = "WRITE upperclassmen;";
					 parser->process_input(command);
					 //fix set difference function
					 command = "underclassmen <- user_data - upperclassmen ;";

					 parser->process_input(command);
					 command = "WRITE underclassmen;";
					 parser->process_input(command);
				 }
				 else  if (table_name == "contact_info")
				 {
					 command = "contact_info <- project(user_name, address, email, phone_number) user_data;";
					 parser->process_input(command);
					 command = "WRITE contact_info;";
					 parser->process_input(command);
				 }
				 else if (table_name == "detailed_grades")
				 {
					 command = "detailed_grades <- gradebook_data JOIN user_data;";
					 parser->process_input(command);
					 command = "WRITE detailed_grades;";
					 parser->process_input(command);

				 }

				command = "SHOW " + table_name + ";";
				parser->process_input(command);
				vector<vector<std::string>> vec = parser->data_vec;

				for (int i = 0; i < vec.at(0).size(); i++) {
					view_table->Columns->Add(fromString(vec.at(0).at(i)), fromString(vec.at(0).at(i)));
				}

				for (int i = 1; i < vec.size(); i++) {
					view_table->Rows->Add();
					for (int j = 0; j < vec.at(i).size(); j++) {
						view_table->Rows[i - 1]->Cells[j]->Value = fromString(vec.at(i).at(j));
					}
				}
	}

	private: System::Void combo_select_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 view_table->Rows->Clear();
				 view_table->Columns->Clear();

				 int current_index = combo_select->SelectedIndex;

				 // (0) Students
				 // (1) Assignments
				 // (2) Sections
				 // (3) Roster
				 // (4) Grades
				 // (5) Detailed Grades
				 // (6) Contact Info
				 // (7) Upperclassmen
				 // (8) Underclassmen

				 switch (current_index) {
				 case 0:
					 *current_table = std::string("user_data");
					 break;
				 case 1:
					 *current_table = std::string("assignment_data");
					 break;
				 case 2:
					 *current_table = std::string("section_data");
					 break;
				 case 3:
					 *current_table = std::string("roster_data");
					 break;
				 case 4:
					 *current_table = std::string("gradebook_data");
					 break;
				 case 5:
					 *current_table = std::string("detailed_grades");
					 break;
				 case 6:
					 *current_table = std::string("contact_info");
					 break;
				 case 7:
					 *current_table = std::string("upperclassmen");
					 break;
				 case 8:
					 *current_table = std::string("underclassmen");
					 break;

				 }

				 update_view(*current_table);
	}

	private: System::Void TableForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->parser = new Parser();
				 this->current_table = new std::string();

				 this->parser->process_input("OPEN user_data;");
				 this->parser->process_input("OPEN assignment_data;");
				 this->parser->process_input("OPEN section_data;");
				 this->parser->process_input("OPEN gradebook_data;");
				 this->parser->process_input("OPEN roster_data;");

				 
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 std::string command;
			 command = "DELETE FROM user_data WHERE (classification == \"SENIOR\");";
			 parser->process_input(command);
			 command = "UPDATE user_data SET classification = SENIOR WHERE (classification == \"JUNIOR\");";
			 parser->process_input(command);
			 command = "UPDATE user_data SET classification = JUNIOR WHERE (classification == \"SOPHMORE\");";
			 parser->process_input(command);
			 command = "UPDATE user_data SET classification = SOPHMORE WHERE (classification == \"FRESHMAN\");";
			 parser->process_input(command);
			 command = "WRITE user_data;";
			 parser->process_input(command);

			 //updating all the other tables that are using user_Data
			 update_view("contact_info");
			 update_view("upperclassmen");
			 update_view("underclassmen");
			 update_view("user_data");

}
};
}
