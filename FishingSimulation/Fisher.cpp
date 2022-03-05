#pragma once
#include "Tackle.cpp"
namespace Fisher {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Fisher : public System::Windows::Forms::PictureBox {
	protected:
		Point posCatch = Point(133, 42);
		System::Drawing::Size sizeCatch = System::Drawing::Size(99, 392);
		Point posWait = Point(133, 194);
		System::Drawing::Size sizeWait = System::Drawing::Size(280, 242);
		Tackle::Tackle^ tackle;
		Random^ rnd = gcnew Random();
		int minTacklePos = 133 + 280;
		int maxTacklePos = minTacklePos + 500;
		int minTackleHeight = 10;
		int maxTackleHeight = 300;
		bool isWait = false;
		bool moveDisable = true;
	public:
		Point couplingPoint;
		Timer^ waitTaimer;

	protected:
		void SetTackle() {
			int tacklePos = rnd->Next(minTacklePos, maxTacklePos);
			int tackleHeight = rnd->Next(minTackleHeight, maxTackleHeight);
			tackle->SetTackle(tackleHeight, tacklePos);
		}
		void GetTackle() {
			//int tacklePos = rnd->Next(minTacklePos, maxTacklePos);
			//int tackleHeight = rnd->Next(minTackleHeight, maxTackleHeight);
			tackle->GetTackle(Point(this->Location.X + 90, this->Location.Y + 150));
		}
		void Wait() {
			this->Image = System::Drawing::Image::FromFile("..\\static\\fisher_wait.png");
			this->Location = posWait;
			this->Size = sizeWait;
			this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->BackColor = System::Drawing::Color::Transparent;
			this->couplingPoint = Point(posWait.X + Size.Width, posWait.Y + Size.Height*0.18);
			this->Refresh();
			this->tackle->SetFsp(this->couplingPoint);
			this->isWait = true;
		}

		void Catch() {
			this->Image = System::Drawing::Image::FromFile("..\\static\\fisher_catch.png");
			this->Location = posCatch;
			this->Size = sizeCatch;
			this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->BackColor = System::Drawing::Color::Transparent;
			this->couplingPoint = Point(posCatch.X + Size.Width, posCatch.Y);
			this->Refresh();
			this->tackle->SetFsp(this->couplingPoint);
			this->GetTackle();
			this->isWait = false;
		}

		void Throw() {
			this->Wait();
			this->SetTackle();
		}
	public:
		Fisher(Control^ control, Color color, Tackle::Tackle^ tackle)
		{
			this->tackle = tackle;
			tackle->AddCatchHandler(gcnew Hook::Hook::HookEventHandler(this, &Fisher::AutoCatch));
			//
			this->Image = System::Drawing::Image::FromFile("..\\static\\fisher_catch.png");
			this->Location = posCatch;
			this->Size = sizeCatch;
			this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->BackColor = System::Drawing::Color::Transparent;
			this->couplingPoint = Point(posCatch.X + Size.Width, posCatch.Y);
			this->tackle->SetFsp(this->couplingPoint);
			this->Refresh();
			this->GetTackle();
			this->waitTaimer = gcnew System::Windows::Forms::Timer();
			this->waitTaimer->Interval = 2000;
			this->waitTaimer->Tick += gcnew System::EventHandler(this, &Fisher::Action);
			this->waitTaimer->Enabled = true;
		}
		void AutoCatch() {
			this->waitTaimer->Enabled = false;
			this->waitTaimer->Interval = 2000;
			this->waitTaimer->Enabled = true;
		}
		void Disable() {
			this->Visible = false;
			this->waitTaimer->Enabled = false;
			moveDisable = true;
		}
		void Enable() {
			this->Visible = true;
			this->waitTaimer->Enabled = true;
			moveDisable = false;
			this->Catch();
		}

		void Action(System::Object^  sender, System::EventArgs^  e) {
			if (this->moveDisable) return;
			this->waitTaimer->Enabled = false;
			this->waitTaimer->Interval = 30000;
			if (this->isWait) {
				this->Catch();
				this->waitTaimer->Interval = 2000;
			}
			else {
				this->Throw();
				this->waitTaimer->Interval = 30000;
			}
			this->waitTaimer->Enabled = true;
		}
	};
}