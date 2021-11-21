#pragma once
#include "Classes.h"
namespace FishingSimulation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->sun->Image = System::Drawing::Image::FromFile("..\\static\\sun.png");
			this->sky->Image = System::Drawing::Image::FromFile("..\\static\\sky.png");
			this->berth->Image = System::Drawing::Image::FromFile("..\\static\\berth.png");
			this->water->Controls->Add(gcnew Fish());
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  berth;
	protected:

	private: System::Windows::Forms::PictureBox^  sky;
	private: System::Windows::Forms::PictureBox^  sun;
	protected:



	private: System::Windows::Forms::Panel^  water;

	private: System::ComponentModel::IContainer^  components;



	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->berth = (gcnew System::Windows::Forms::PictureBox());
			this->sky = (gcnew System::Windows::Forms::PictureBox());
			this->sun = (gcnew System::Windows::Forms::PictureBox());
			this->water = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->berth))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sky))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sun))->BeginInit();
			this->SuspendLayout();
			// 
			// berth
			// 
			this->berth->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"berth.Image")));
			this->berth->Location = System::Drawing::Point(-10, 237);
			this->berth->Name = L"berth";
			this->berth->Size = System::Drawing::Size(263, 491);
			this->berth->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->berth->TabIndex = 0;
			this->berth->TabStop = false;
			// 
			// sky
			// 
			this->sky->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sky.Image")));
			this->sky->Location = System::Drawing::Point(-373, 1);
			this->sky->Name = L"sky";
			this->sky->Size = System::Drawing::Size(1823, 245);
			this->sky->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->sky->TabIndex = 2;
			this->sky->TabStop = false;
			// 
			// sun
			// 
			this->sun->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->sun->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sun.Image")));
			this->sun->Location = System::Drawing::Point(1322, 12);
			this->sun->Name = L"sun";
			this->sun->Size = System::Drawing::Size(100, 82);
			this->sun->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->sun->TabIndex = 3;
			this->sun->TabStop = false;
			// 
			// water
			// 
			this->water->BackColor = System::Drawing::Color::RoyalBlue;
			this->water->Location = System::Drawing::Point(253, 246);
			this->water->Name = L"water";
			this->water->Size = System::Drawing::Size(1197, 461);
			this->water->TabIndex = 4;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1450, 707);
			this->Controls->Add(this->water);
			this->Controls->Add(this->sun);
			this->Controls->Add(this->sky);
			this->Controls->Add(this->berth);
			this->Name = L"MyForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->berth))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sky))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sun))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
};
}
