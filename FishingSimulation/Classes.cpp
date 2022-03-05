using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


public ref class Hook : public System::Windows::Forms::PictureBox {
private:
	int posX;
	int posY;
	EventHandler^ catchHandler;
	EventHandler^ touchHandler;
	EventHandler^ eatHandler;
	EventHandler^ getUpHandler;
	System::Drawing::Image^ clue;
	System::Drawing::Image^ empty;
	Random^ rnd = gcnew Random();
public:
	bool isEmpty = true;
	int sizeX = 20;
	int sizeY = 25;
	Point couplingPoint;
public:
	Hook()
	{
		this->posX = posX;
		this->posY = posY;
		this->empty = System::Drawing::Image::FromFile("..\\static\\hook.png");
		this->clue = System::Drawing::Image::FromFile("..\\static\\hook_clue.png");
		this->Image = this->empty;
		this->Size = System::Drawing::Size(sizeX, sizeY);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::Transparent;
		this->Visible = false;
	}
public:
	void Activate(Point couplingPoint) {
		this->couplingPoint = couplingPoint;
		this->SetLocationFromCouplingPoint(couplingPoint);
		this->Image = this->clue;
		this->isEmpty = false;
		this->Visible = true;
	}
	void GetUp(Point couplingPoint) {
		this->couplingPoint = couplingPoint;
		this->SetLocationFromCouplingPoint(couplingPoint);
		this->isEmpty = true;
		this->Visible = true;
		this->Image = this->empty;
		this->Refresh();
		if (getUpHandler != nullptr) {
			getUpHandler(this, gcnew EventArgs());
		}

	}
	void SetLocationFromCouplingPoint(Point couplingPoint) {
		this->Location = Point(couplingPoint.X - this->Size.Width * 0.85, couplingPoint.Y);
	}
	void AddCatchHandler(EventHandler^ catchHandler) {
		this->catchHandler += catchHandler;
	}
	void AddTouchHandler(EventHandler^ touchHandler) {
		this->touchHandler += touchHandler;
	}
	void AddGetUpHandler(EventHandler^ getUpHandler) {
		this->getUpHandler += getUpHandler;
	}
	void DelGetUpHandler(EventHandler^ getUpHandler) {
		this->getUpHandler -= getUpHandler;
	}
	void Catch() {
		this->Visible = false;
		catchHandler(this, gcnew EventArgs());
		this->isEmpty = true;
	}
	void Touch() {
		if (rnd->Next(1, 6) == 5) {
			this->Eat();
		}
		touchHandler(this, gcnew EventArgs());
	}
	void Eat() {
		this->Image = this->empty;
		this->Refresh();
		this->isEmpty = true;
	}
};

