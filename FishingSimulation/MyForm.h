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
			tl = gcnew Tackle(this->water);
			this->sky->SendToBack();
			this->water->Controls->Add(gcnew Fish(tl->hook));
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

	protected:


	private: System::Windows::Forms::PictureBox^  sun;
	protected:



	private: System::Windows::Forms::Panel^  water;
	private: System::Windows::Forms::PictureBox^  berth;


	private: System::Windows::Forms::PictureBox^  sky;
	private: System::Windows::Forms::Button^  button1;
			 Tackle^ tl;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;








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
			this->sun = (gcnew System::Windows::Forms::PictureBox());
			this->water = (gcnew System::Windows::Forms::Panel());
			this->berth = (gcnew System::Windows::Forms::PictureBox());
			this->sky = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sun))->BeginInit();
			this->water->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->berth))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sky))->BeginInit();
			this->SuspendLayout();
			// 
			// sun
			// 
			this->sun->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->sun->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sun.Image")));
			this->sun->Location = System::Drawing::Point(1350, 0);
			this->sun->Name = L"sun";
			this->sun->Size = System::Drawing::Size(100, 100);
			this->sun->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->sun->TabIndex = 3;
			this->sun->TabStop = false;
			// 
			// water
			// 
			this->water->BackColor = System::Drawing::Color::RoyalBlue;
			this->water->Controls->Add(this->berth);
			this->water->Controls->Add(this->sky);
			this->water->Location = System::Drawing::Point(0, 246);
			this->water->Name = L"water";
			this->water->Size = System::Drawing::Size(1450, 461);
			this->water->TabIndex = 4;
			// 
			// berth
			// 
			this->berth->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"berth.Image")));
			this->berth->Location = System::Drawing::Point(0, 0);
			this->berth->Name = L"berth";
			this->berth->Size = System::Drawing::Size(263, 461);
			this->berth->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->berth->TabIndex = 1;
			this->berth->TabStop = false;
			// 
			// sky
			// 
			this->sky->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sky.Image")));
			this->sky->Location = System::Drawing::Point(262, 0);
			this->sky->Name = L"sky";
			this->sky->Size = System::Drawing::Size(1188, 38);
			this->sky->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->sky->TabIndex = 2;
			this->sky->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(24, 77);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(425, 63);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 100);
			this->panel1->TabIndex = 6;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(24, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 7;
			this->textBox1->Text = L"400";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(24, 51);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 8;
			this->textBox2->Text = L"50";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->ClientSize = System::Drawing::Size(1450, 707);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->sun);
			this->Controls->Add(this->water);
			this->Name = L"MyForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sun))->EndInit();
			this->water->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->berth))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sky))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	int posX = Convert::ToInt64(textBox1->Text);
	int height = Convert::ToInt64(textBox2->Text);
	tl->SetTackle(height, posX);
}
};
}
