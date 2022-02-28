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

			
			this->platrorm->Image = System::Drawing::Image::FromFile("..\\static\\berth.png");
			WorldGenerator^ wg = gcnew WorldGenerator();
			this->platrorm->Visible = false;
			this->whether->Image = wg->ReturnWhetherImage();
			this->BackColor = wg->ReturnColor();
			this->fisherBoat = gcnew FisherWithBoat(this, this->BackColor);
			this->Controls->Add(this->fisherBoat);
			Hook^ hook = this->fisherBoat->GetHook();
			wg->SpawnFish(this, hook);			
		
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


	private: System::Windows::Forms::PictureBox^  whether;


	protected:




	private: System::Windows::Forms::PictureBox^  platrorm;







			 FisherWithBoat^ fisherBoat;
			 Fisher^ fisher;
	private: System::Windows::Forms::Button^  left;
	private: System::Windows::Forms::Button^  right;
	private: System::Windows::Forms::Button^  stop;


















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
			this->whether = (gcnew System::Windows::Forms::PictureBox());
			this->platrorm = (gcnew System::Windows::Forms::PictureBox());
			this->left = (gcnew System::Windows::Forms::Button());
			this->right = (gcnew System::Windows::Forms::Button());
			this->stop = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->whether))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->platrorm))->BeginInit();
			this->SuspendLayout();
			// 
			// whether
			// 
			this->whether->BackColor = System::Drawing::Color::Transparent;
			this->whether->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whether.Image")));
			this->whether->Location = System::Drawing::Point(1350, 0);
			this->whether->Name = L"whether";
			this->whether->Size = System::Drawing::Size(100, 100);
			this->whether->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->whether->TabIndex = 3;
			this->whether->TabStop = false;
			// 
			// platrorm
			// 
			this->platrorm->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"platrorm.Image")));
			this->platrorm->Location = System::Drawing::Point(0, 428);
			this->platrorm->Name = L"platrorm";
			this->platrorm->Size = System::Drawing::Size(263, 476);
			this->platrorm->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->platrorm->TabIndex = 1;
			this->platrorm->TabStop = false;
			// 
			// left
			// 
			this->left->Location = System::Drawing::Point(32, 21);
			this->left->Name = L"left";
			this->left->Size = System::Drawing::Size(41, 27);
			this->left->TabIndex = 4;
			this->left->Text = L"left";
			this->left->UseVisualStyleBackColor = true;
			this->left->Click += gcnew System::EventHandler(this, &MyForm::left_Click);

			// 
			// right
			// 
			this->right->Location = System::Drawing::Point(157, 21);
			this->right->Name = L"right";
			this->right->Size = System::Drawing::Size(41, 27);
			this->right->TabIndex = 5;
			this->right->Text = L"right";
			this->right->UseVisualStyleBackColor = true;
			this->right->Click += gcnew System::EventHandler(this, &MyForm::right_Click);

			// 
			// stop
			// 
			this->stop->Location = System::Drawing::Point(60, 54);
			this->stop->Name = L"stop";
			this->stop->Size = System::Drawing::Size(109, 27);
			this->stop->TabIndex = 6;
			this->stop->Text = L"stop";
			this->stop->UseVisualStyleBackColor = true;
			this->stop->Click += gcnew System::EventHandler(this, &MyForm::stop_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->ClientSize = System::Drawing::Size(1450, 901);
			this->Controls->Add(this->stop);
			this->Controls->Add(this->right);
			this->Controls->Add(this->left);
			this->Controls->Add(this->platrorm);
			this->Controls->Add(this->whether);
			this->Name = L"MyForm";
			this->Text = L"MainForm";
			this->Click += gcnew System::EventHandler(this, &MyForm::MyForm_Click);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::PaintWater);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->whether))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->platrorm))->EndInit();
			this->ResumeLayout(false);

		}

private: System::Void PaintWater(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	e->Graphics->FillRectangle(Brushes::RoyalBlue, 0, 466, 1500, 600);
}
private: System::Void MyForm_Click(System::Object^  sender, System::EventArgs^  e) {
	if (fisherBoat != nullptr) {
		fisherBoat->Action(sender, e);
	}
	else {
		this->fisher->Action(this, gcnew EventArgs());
	}
	
}
	private: System::Void left_Click(System::Object^  sender, System::EventArgs^  e) {
		if (fisherBoat != nullptr) {
			fisherBoat->Left(sender, e);
		}
	}
private: System::Void right_Click(System::Object^  sender, System::EventArgs^  e) {
	if (fisherBoat != nullptr) {
		fisherBoat->Right(sender, e);
	}
}
private: System::Void stop_Click(System::Object^  sender, System::EventArgs^  e) {
	if (fisherBoat != nullptr) {
		fisherBoat->KeyUp(sender, e);
	}
}
};
}
