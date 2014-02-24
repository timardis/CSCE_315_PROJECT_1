#pragma once
#include <msclr\marshal_cppstd.h>
#include "Parser.h"

namespace DatabaseGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for View
	/// </summary>
	public ref class View : public System::Windows::Forms::Form
	{
	public:
		
		

		View(void)
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
		~View()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^  btn_delete;
	private: System::Windows::Forms::ComboBox^  combo_choose_table;
	private: System::Windows::Forms::DataGridView^  view_table;
	private: System::Windows::Forms::Button^  btn_update;
	private: System::Windows::Forms::Button^  btn_new_year;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		Parser *parser;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_delete = (gcnew System::Windows::Forms::Button());
			this->combo_choose_table = (gcnew System::Windows::Forms::ComboBox());
			this->view_table = (gcnew System::Windows::Forms::DataGridView());
			this->btn_update = (gcnew System::Windows::Forms::Button());
			this->btn_new_year = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->view_table))->BeginInit();
			this->SuspendLayout();

			//parser->process_input("OPEN user_data;");
			// 
			// btn_delete
			// 
			this->btn_delete->Enabled = false;
			this->btn_delete->Location = System::Drawing::Point(635, 313);
			this->btn_delete->Name = L"btn_delete";
			this->btn_delete->Size = System::Drawing::Size(75, 24);
			this->btn_delete->TabIndex = 1;
			this->btn_delete->Text = L"Delete";
			this->btn_delete->UseVisualStyleBackColor = true;
			// 
			// combo_choose_table
			// 
			this->combo_choose_table->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->combo_choose_table->FormattingEnabled = true;
			this->combo_choose_table->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Students", L"Assignments", L"Sections",
					L"Roster", L"Grades", L"Detailed Grades", L"Contact Info", L"Upperclassmen", L"Underclassmen"
			});
			this->combo_choose_table->Location = System::Drawing::Point(12, 12);
			this->combo_choose_table->Name = L"combo_choose_table";
			this->combo_choose_table->Size = System::Drawing::Size(116, 21);
			this->combo_choose_table->TabIndex = 2;
			this->combo_choose_table->SelectedIndexChanged += gcnew System::EventHandler(this, &View::combo_choose_table_SelectedIndexChanged);
			// 
			// view_table
			// 
			this->view_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->view_table->Location = System::Drawing::Point(12, 45);
			this->view_table->Name = L"view_table";
			this->view_table->Size = System::Drawing::Size(697, 262);
			this->view_table->TabIndex = 3;
			// 
			// btn_update
			// 
			this->btn_update->Enabled = false;
			this->btn_update->Location = System::Drawing::Point(554, 313);
			this->btn_update->Name = L"btn_update";
			this->btn_update->Size = System::Drawing::Size(75, 24);
			this->btn_update->TabIndex = 4;
			this->btn_update->Text = L"Update";
			this->btn_update->UseVisualStyleBackColor = true;
			// 
			// btn_new_year
			// 
			this->btn_new_year->Enabled = false;
			this->btn_new_year->Location = System::Drawing::Point(12, 313);
			this->btn_new_year->Name = L"btn_new_year";
			this->btn_new_year->Size = System::Drawing::Size(75, 24);
			this->btn_new_year->TabIndex = 5;
			this->btn_new_year->Text = L"New Year!";
			this->btn_new_year->UseVisualStyleBackColor = true;
			// 
			// View
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(722, 347);
			this->Controls->Add(this->btn_new_year);
			this->Controls->Add(this->btn_update);
			this->Controls->Add(this->view_table);
			this->Controls->Add(this->combo_choose_table);
			this->Controls->Add(this->btn_delete);
			this->Name = L"View";
			this->Text = L"View";
			this->Load += gcnew System::EventHandler(this, &View::View_Load);
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

	private: System::Void View_Load(System::Object^  sender, System::EventArgs^  e) {
				// parser->process_input("OPEN user_data;");
	}

	private: System::Void update_view(std::string table_name) {
				 Parser p;
				 p.process_input("OPEN user_data;");
				 std::string command = "SHOW " + table_name + ";";
				 p.process_input(command);
				 vector<vector<std::string>> vec = p.data_vec;

				 for (int i = 0; i < vec.at(0).size(); i++) {
					 view_table->Columns->Add(fromString(vec.at(0).at(i)), fromString(vec.at(0).at(i)));
				 }

				 for (int i = 1; i < vec.size() - 1; i++) {
					 view_table->Rows->Add();
					 for (int j = 0; j < vec.at(i).size(); j++) {
						 view_table->Rows[i-1]->Cells[j]->Value = fromString(vec.at(i).at(j));
					 }
				 }
	}

	private: System::Void combo_choose_table_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 // (0) Students
				 // (1) Assignments
				 // (2) Sections
				 // (3) Roster
				 // (4) Grades
				 // (5) Detailed Grades
				 // (6) Contact Info
				 // (7) Upperclassmen
				 // (8) Underclassmen
				 std::string test = "user_data";
				 update_view(test);

	}
	};
}
