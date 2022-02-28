#include "Fish.h"
namespace Hook {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Hook : public System::Windows::Forms::PictureBox {
	private:
		System::Drawing::Image^ clue;
		System::Drawing::Image^ empty;
		Random^ rnd = gcnew Random();
		int sizeX = 20;
		int sizeY = 25;
		bool isEmpty = true;
		Point cP;
		void SetLocationFromCouplingPoint(Point couplingPoint) {
			this->cP = couplingPoint;
			this->Location = Point(couplingPoint.X - this->Size.Width * 0.85, couplingPoint.Y);
		}
	public:
		delegate void HookEventHandler();
		static event HookEventHandler^ CatchEvent;
		static event HookEventHandler^ TouchEvent;
		static event HookEventHandler^ EatEvent;
		static event HookEventHandler^ GetUpEvent;
		static event HookEventHandler^ SetUpEvent;

	public:
		Hook()
		{
			this->empty = System::Drawing::Image::FromFile("..\\static\\hook.png");
			this->clue = System::Drawing::Image::FromFile("..\\static\\hook_clue.png");
			this->Image = this->empty;
			this->Size = System::Drawing::Size(sizeX, sizeY);
			this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Visible = false;
		}
		/*
		void SetUp(Point couplingPoint) {
			this->cP = couplingPoint;
			this->SetLocationFromCouplingPoint(couplingPoint);
			this->Image = this->clue;
			this->isEmpty = false;
			this->Visible = true;
			this->Refresh();
		}
		*/
		void GetUp(Point couplingPoint) {
			this->cP = couplingPoint;
			this->SetLocationFromCouplingPoint(couplingPoint);
			this->isEmpty = true;
			this->Visible = true;
			this->Image = this->empty;
			this->Refresh();
			GetUpEvent();
		}

		property Point couplingPoint {
			void set(Point couplingPoint) {
				this->cP = couplingPoint;
				this->SetLocationFromCouplingPoint(couplingPoint);
				this->Image = this->clue;
				this->isEmpty = false;
				this->Visible = true;
				this->Refresh();
			}
			Point get() {
				return this->cP;
			}
		}
		void Catch() {
			if (isEmpty) return;
			this->Visible = false;
			CatchEvent();
			this->isEmpty = true;
		}
		void Touch(Fish::Fish^ fish) {
			if (isEmpty) return;
			if (rnd->Next(1, 6) == 5) {
				this->Eat();
				return;
			}
			if (rnd->Next(1, 3) == 5) {
				
				this->CatchEvent();
				return;
			}
			TouchEvent();
		}
		void Eat() {
			if (isEmpty) return;
			this->Image = this->empty;
			this->Refresh();
			this->isEmpty = true;
			EatEvent();
		}
	};
}