#pragma once
#include "Hook.cpp"
#include "Float.cpp"
namespace Tackle {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class Tackle : public Component {
	private:
		bool isActivate = false;
		Float::Float^ fl;
		Graphics^ gr;
		Control^ control;
		Timer^ timer = gcnew Timer();
		Color color;
		Point fsp;
		int defaultWidth = 2;
		Hook::Hook^ hook;
	public:
		Tackle(Control^ control, Color color)
		{
			this->control = control;
			this->color = color;
			hook = gcnew Hook::Hook();
			gr = control->CreateGraphics();
			fl = gcnew Float::Float(gcnew Float::Float::FloatEventHandler(this, &Tackle::ChangeCouplePointStart), gcnew Float::Float::FloatEventHandler(this, &Tackle::ChangeCouplePointEnd));
			hook->CatchEvent += gcnew Hook::Hook::HookEventHandler(fl, &Float::Float::Catch);
			hook->TouchEvent += gcnew Hook::Hook::HookEventHandler(fl, &Float::Float::Touch);
			control->Controls->Add(fl);
			control->Controls->Add(hook);
			this->timer->Interval = 1;
			this->timer->Tick += gcnew System::EventHandler(this, &Tackle::DrawLine);
			this->timer->Enabled = false;
		}

	public:
		void SetTackle(int height, int posX) {
			if (isActivate == true) {
				timer->Enabled = false;
				this->ClearLine();
			}
			isActivate = true;
			fl->SetUp(posX);
			hook->couplingPoint = (Point(fl->downCouplingPoint.X, fl->downCouplingPoint.Y + height));
			timer->Enabled = true;
		}
		void GetTackle(Point pnt) {
			timer->Enabled = false;
			this->ClearLine();
			isActivate = false;
			fl->GetUp(pnt);
			hook->GetUp(Point(fl->downCouplingPoint.X, fl->downCouplingPoint.Y + 10));
			timer->Enabled = true;
		}
		void SetFsp(Point fsp) {
			timer->Enabled = false;
			this->ClearLine();
			this->fsp = fsp;
			timer->Enabled = true;
		}
		void ChangeCouplePointStart() {
			timer->Enabled = false;
			this->ClearLine();
		}
		void ChangeCouplePointEnd() {
			timer->Enabled = true;
		}
		void AddCatchHandler(Hook::Hook::HookEventHandler^ catchHandler) {
			hook->CatchEvent += catchHandler;
		}

	private: void DrawLine(System::Object^  sender, System::EventArgs^  e) {
		Pen^ p = gcnew Pen(Color::White, defaultWidth);
		Point flpd = fl->downCouplingPoint;
		Point flpu = fl->upperCouplingPoint;
		Point hkp = hook->couplingPoint;
		gr->DrawLine(p, flpd, hkp);
		gr->DrawLine(p, flpu, fsp);
	}
	void ClearLine() {
		Point flpu = fl->upperCouplingPoint;
		Point hkp = hook->couplingPoint;
		Pen^ pa = gcnew Pen(color, defaultWidth);
		gr->DrawLine(pa, flpu, fsp);
		gr->FillRectangle(Brushes::RoyalBlue, 0, 466, 1500, 600);
	}
	public: Hook::Hook^ GetHook() {
		return this->hook;
	}
	};


}