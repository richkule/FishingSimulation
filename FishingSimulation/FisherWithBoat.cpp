#pragma once
#include "Fisher.cpp"
namespace FisherWithBoat {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class FisherWithBoat : Fisher::Fisher {
	private:
		PictureBox^ boat;
		Timer^ timerMove;
		int maxXPos = 800;
		int minXPos = 0;
		int yPosBoat = 412;
		int speedX = 0;
	public: FisherWithBoat(Control^ control, Color color, Tackle::Tackle^ tackle) : Fisher::Fisher(control, color, tackle) {
		boat = gcnew PictureBox();
		boat->BackColor = Color::Transparent;
		boat->Image = System::Drawing::Image::FromFile("..\\static\\boat.png");
		boat->Location = Point(this->Location.X - 120, yPosBoat);
		boat->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		boat->Size = System::Drawing::Size(263, 54);
		boat->Visible = true;
		control->Controls->Add(boat);
		this->tackle = tackle;
		this->timerMove = gcnew System::Windows::Forms::Timer();
		this->timerMove->Tick += gcnew System::EventHandler(this, &FisherWithBoat::Move);
		this->timerMove->Enabled = false;

	}
			void Disable() {
				this->Visible = false;
				this->waitTaimer->Enabled = false;
				this->boat->Visible = false;
				moveDisable = true;
			}
			void Enable() {
				this->Visible = true;
				this->waitTaimer->Enabled = true;
				this->boat->Visible = true;
				moveDisable = false;
				this->Catch();
			}
			void Move(System::Object^  sender, System::EventArgs^  e) {
				Point newPoint = System::Drawing::Point(this->Location.X + this->speedX, this->Location.Y);
				if (newPoint.X > maxXPos) return;
				if (newPoint.X < minXPos) return;
				this->maxTacklePos += speedX;
				this->minTacklePos += speedX;
				this->Location = newPoint;
				this->waitTaimer->Enabled = false;
				this->posWait = Point(posWait.X + speedX, posWait.Y);
				this->posCatch = Point(posCatch.X + speedX, posCatch.Y);
				this->boat->Location = System::Drawing::Point(boat->Location.X + this->speedX, yPosBoat);
				this->Catch();

			}
			void Left(System::Object^  sender, System::EventArgs^  e) {
				speedX = -40;
				if (!moveDisable) timerMove->Enabled = true;
			}
			void Right(System::Object^  sender, System::EventArgs^  e) {
				speedX = 40;
				if (!moveDisable) timerMove->Enabled = true;
			}
			void KeyUp(System::Object^  sender, System::EventArgs^  e) {
				timerMove->Enabled = false;
				if (!moveDisable)this->Catch();
			}
	};

}