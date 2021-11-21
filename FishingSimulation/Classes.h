#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Fish : public System::Windows::Forms::PictureBox {
public:
	Fish(void)
	{
		this->Image = System::Drawing::Image::FromFile("..\\static\\fish.png");
		this->Location = System::Drawing::Point(0, 0);
		this->Size = System::Drawing::Size(100, 100);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::RoyalBlue;
	}

};