#pragma once
namespace Float {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Float : public System::Windows::Forms::PictureBox {
	private:
		int current_frame = 0;
		bool isUpperPosition = true;
		bool isTouch = false;
		int sizeX = 19;
		int sizeY = 38;
		int deep = 40;
		int posX;
		Timer^ timer;
		System::Drawing::Image^ diveDefault = System::Drawing::Image::FromFile("..\\static\\floatDefault.png");
		int defaultYPos = 447;
		System::Drawing::Image^ dive25 = System::Drawing::Image::FromFile("..\\static\\float25.png");
		int dive25YPos = defaultYPos + 1;
		System::Drawing::Image^ dive50 = System::Drawing::Image::FromFile("..\\static\\float50.png");
		int dive50YPos = defaultYPos + 9;
		System::Drawing::Image^ dive75 = System::Drawing::Image::FromFile("..\\static\\float75.png");
		int dive75YPos = defaultYPos + 13;
		System::Drawing::Image^ dive100 = System::Drawing::Image::FromFile("..\\static\\float100.png");
		int dive100YPos = defaultYPos + 19;
		System::Drawing::Image^ floatUp = System::Drawing::Image::FromFile("..\\static\\float_up.png");
	public:
		Point downCouplingPoint;
		Point upperCouplingPoint;
		delegate void FloatEventHandler();
		static event FloatEventHandler^ changeCouplePointStart;
		static event FloatEventHandler^ changeCouplePointEnd;
		static event FloatEventHandler^ catchEvent;
		Float(FloatEventHandler^ changeCouplePointStartHandler, FloatEventHandler^ changeCouplePointEndHandler)
		{
			this->changeCouplePointStart += changeCouplePointStartHandler;
			this->changeCouplePointEnd += changeCouplePointEndHandler;
			this->Image = System::Drawing::Image::FromFile("..\\static\\floatDefault.png");
			this->Size = System::Drawing::Size(sizeX, sizeY);
			this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->BackColor = System::Drawing::Color::Transparent;
			this->timer = gcnew System::Windows::Forms::Timer();
			this->timer->Interval = 300;
			this->timer->Tick += gcnew System::EventHandler(this, &Float::Animate);
			this->timer->Enabled = false;
			this->Visible = false;
		}
	public:
		void SetUp(int posX) {
			this->posX = posX;
			this->Location = System::Drawing::Point(posX, defaultYPos);
			changeCouplePointStart();
			downCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y + this->Size.Height);
			upperCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y);
			changeCouplePointEnd();
			timer->Enabled = true;
			Visible = true;
		}
		void GetUp(Point pnt) {
			this->posX = posX;
			this->Location = pnt;
			this->Image = floatUp;
			changeCouplePointStart();
			downCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y + this->Size.Height);
			upperCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y);
			changeCouplePointEnd();
			timer->Enabled = false;
			Visible = true;
		}

	private:
		void ChangeCouplePoint(System::Drawing::Point loc, System::Drawing::Image^ image) {
			changeCouplePointStart();
			this->Location = loc;
			this->Image = image;
			upperCouplingPoint.Y = loc.Y;
			changeCouplePointEnd();
		}
		void Animate(System::Object^  sender, System::EventArgs^  e) {
			if (isUpperPosition) {
				isUpperPosition = false;
				if (isTouch) {
					ChangeCouplePoint(System::Drawing::Point(posX, dive75YPos), dive75);
					this->Refresh();
					timer->Interval = 300;
					isTouch = false;
				}
				else {
					ChangeCouplePoint(System::Drawing::Point(posX, dive25YPos), dive25);
					this->Refresh();
				}
			}
			else
			{
				isUpperPosition = true;
				if (isTouch) {
					ChangeCouplePoint(System::Drawing::Point(posX, dive50YPos), dive50);
					this->Refresh();
				}
				else {
					ChangeCouplePoint(System::Drawing::Point(posX, defaultYPos), diveDefault);
					this->Refresh();
				}
			}
		}
	public: void Catch() {
		catchEvent();
		this->Refresh();
	}

	public: void Touch() {
		if (isTouch) return;
		this->timer->Enabled = false;
		this->Location = System::Drawing::Point(posX, dive50YPos);
		this->Image = this->dive50;
		this->Refresh();
		isUpperPosition = false;
		isTouch = true;
		timer->Interval = 100;
		timer->Enabled = true;
	}
	};
}