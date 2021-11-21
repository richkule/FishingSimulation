#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Fish : public System::Windows::Forms::PictureBox {
private: System::Windows::Forms::Timer^  moveTimer;
		 int speedX;
		 int speedY;
public:
	Fish(void)
	{
		this->Image = System::Drawing::Image::FromFile("..\\static\\fish.png");
		this->Location = System::Drawing::Point(0, 0);
		this->Size = System::Drawing::Size(100, 100);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::RoyalBlue;
		this->moveTimer=gcnew System::Windows::Forms::Timer();
		this->moveTimer->Tick += gcnew System::EventHandler(this, &Fish::move);
		this->moveTimer->Enabled = true;
		this->speedX = 1;
		this->speedY = 1;

		
	}
private: System::Void move(System::Object^  sender, System::EventArgs^  e) {
	this->Location = System::Drawing::Point(this->Location.X+speedX, this->Location.Y + speedY);
}
};