#pragma once

namespace DatabaseGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::ListBox^  listBox1;
	protected:
	private: System::Windows::Forms::Button^  btn_delete;

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
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->btn_delete = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(12, 19);
			this->listBox1->MultiColumn = true;
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(698, 251);
			this->listBox1->TabIndex = 0;
			// 
			// btn_delete
			// 
			this->btn_delete->Enabled = false;
			this->btn_delete->Location = System::Drawing::Point(316, 300);
			this->btn_delete->Name = L"btn_delete";
			this->btn_delete->Size = System::Drawing::Size(75, 24);
			this->btn_delete->TabIndex = 1;
			this->btn_delete->Text = L"Delete";
			this->btn_delete->UseVisualStyleBackColor = true;
			// 
			// View
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(722, 349);
			this->Controls->Add(this->btn_delete);
			this->Controls->Add(this->listBox1);
			this->Name = L"View";
			this->Text = L"View";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
