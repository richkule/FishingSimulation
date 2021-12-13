using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


public ref class Hook : public System::Windows::Forms::PictureBox {
private:
	int posX = -1e300;
	int posY = -1e300;
public:
	bool isEmpty = false;
	int sizeX = 20;
	int sizeY = 25;
	Point couplingPoint;
public:
	Hook()
	{
		this->posX = posX;
		this->posY = posY;
		this->Image = System::Drawing::Image::FromFile("..\\static\\hook.png");
		this->Size = System::Drawing::Size(sizeX, sizeY);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::Transparent;
		this->Visible = false;
	}
	bool CheckCatch(System::Drawing::Point^ fish_coor, System::Drawing::Size^ fish_size) {
		if (!this->isEmpty) {
			return false;
		}
		int fish_y = fish_coor->Y;
		int fish_y1 = fish_y + fish_size->Height;
		int fish_x = fish_coor->X;
		int fish_x1 = fish_x + fish_size->Width;

		int hook_y = this->Location.Y;
		int hook_y1 = hook_y + this->Size.Height;
		int hook_x = this->Location.X;
		int hook_x1 = hook_x + this->Size.Width;

		if (fish_y < hook_y1 || fish_y1 > hook_y || fish_x1 < hook_x || fish_x > hook_x1) {
			return false;
		}
		else {
			this->isEmpty = false;
			return true;
		}
	}
public:
	void Activate(Point couplingPoint) {
		this->couplingPoint = couplingPoint;
		this->SetLocationFromCouplingPoint(couplingPoint);
		this->isEmpty = true;
		this->Visible = true;
	}
	void SetLocationFromCouplingPoint(Point couplingPoint) {
		this->Location = Point(couplingPoint.X - this->Size.Width * 0.85, couplingPoint.Y);
	}
};


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
	int defaultYPos = 19;
	System::Drawing::Image^ dive25 = System::Drawing::Image::FromFile("..\\static\\float25.png");
	int dive25YPos = 20;
	System::Drawing::Image^ dive50 = System::Drawing::Image::FromFile("..\\static\\float50.png");
	int dive50YPos = 28;
	System::Drawing::Image^ dive75 = System::Drawing::Image::FromFile("..\\static\\float75.png");
	int dive75YPos = 32;
	System::Drawing::Image^ dive100 = System::Drawing::Image::FromFile("..\\static\\float100.png");
	int dive100YPos = 38;
public:
	Point couplingPoint;
	Float()
	{
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
	void Activate(int posX) {
		this->posX = posX;
		this->Location = System::Drawing::Point(posX, defaultYPos);
		couplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y + this->Size.Height);
		timer->Enabled = true;
		Visible = true;
	}
private: void Animate(System::Object^  sender, System::EventArgs^  e) {
	if (isUpperPosition) {
		isUpperPosition = false;
		if (isTouch) {
			this->Location = System::Drawing::Point(posX, dive75YPos);
			this->Image = this->dive75;
			this->Refresh();
		}
		else {
			this->Location = System::Drawing::Point(posX, dive25YPos);
			this->Image = this->dive25;
			this->Refresh();
		}
	}
	else
	{
		isUpperPosition = true;
		if (isTouch) {
			this->Location = System::Drawing::Point(posX, dive50YPos);
			this->Image = this->dive50;
			this->Refresh();
			isTouch = false;
			timer->Interval = 300;
		}
		else {
			this->Location = System::Drawing::Point(posX, defaultYPos);
			this->Image = this->diveDefault;
			this->Refresh();
		}
	}
}
public: void Touch(System::Object^  sender, System::EventArgs^  e) {
	this->timer->Enabled = false;
	this->Location = System::Drawing::Point(posX, dive50YPos);
	this->Image = this->dive50;
	this->Refresh();
	isUpperPosition = true;
	isTouch = true;
	timer->Interval = 50;
	timer->Enabled = true;
}
};

public ref class Fish : public System::Windows::Forms::PictureBox {
private: System::Windows::Forms::Timer^  timer;
		 int speedX = -5;
		 int speedY = 0;
		 int sizeX = 110;
		 int sizeY = 50;
		 int minXPos = 800;
		 int minYPos = 40;
		 int maxXPos = 1185;
		 int maxYPos = 420;
		 bool isForwardDirection = true;
		 bool isCatch = false;
		 Hook^ hook;
public:
	Fish(Hook^ hook)
	{
		this->hook = hook;
		this->Image = System::Drawing::Image::FromFile("..\\static\\fish.png");
		this->Location = System::Drawing::Point(minXPos, minYPos);
		this->Size = System::Drawing::Size(sizeX, sizeY);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::Transparent;
		this->timer = gcnew System::Windows::Forms::Timer();
		this->timer->Tick += gcnew System::EventHandler(this, &Fish::tick);
		this->timer->Enabled = true;
	}
private: void move(void) {
	if (isCatch) {
		return;
	}
	if (this->speedX < 0) {
		if (this->isForwardDirection) {
			this->isForwardDirection = false;
			this->Image->RotateFlip(RotateFlipType::Rotate180FlipY);
			this->Refresh();
		}
	}
	else
	{
		if (!this->isForwardDirection) {
			this->isForwardDirection = true;
			this->Image->RotateFlip(RotateFlipType::RotateNoneFlipX);
			this->Refresh();
		}
	}
	this->Location = System::Drawing::Point(this->Location.X + this->speedX, this->Location.Y + this->speedY);
}
private: void checkCatch(void) {
	if (!hook->isEmpty) return;
	if (Rectangle(this->Location,this->Size).IntersectsWith(Rectangle(this->hook->Location,this->hook->Size))){
		this->timer->Enabled = false;
		this->isCatch = true;
		this->Size = System::Drawing::Size(sizeY, sizeX);
		this->Image = System::Drawing::Image::FromFile("..\\static\\catch_fish.png");
		this->Image->RotateFlip(RotateFlipType::Rotate90FlipY);

		int hookMiddleX = hook->Location.X + hook->sizeX/2;
		int hookMiddleY = hook->Location.Y - hook->sizeY / 2;
		int newX = hookMiddleX - sizeY / 2;
		this->Location = System::Drawing::Point(newX, hookMiddleY);
		this->hook->Visible = false;
		this->Refresh();
	}
}
private: System::Void tick(System::Object^  sender, System::EventArgs^  e) {
	this->checkCatch();
	this->move();
}

};



public ref class Tackle : public Component {
private:
	Float^ fl;
	Graphics^ gr;
	Panel^ panel;
	Timer^ timer = gcnew Timer();
public:
	Hook^ hook;
	Tackle(Panel^ panel)
	{
		this->panel = panel;
		gr = panel->CreateGraphics();
		fl = gcnew Float();
		panel->Controls->Add(fl);
		hook = gcnew Hook();
		panel->Controls->Add(hook);
		this->timer->Interval = 1;
		this->timer->Tick += gcnew System::EventHandler(this, &Tackle::DrawLine);
		this->timer->Enabled = false;
	}

public:
	void SetTackle(int height, int posX) {
		fl->Activate(posX);
		hook->Activate(Point(fl->couplingPoint.X, fl->couplingPoint.Y + height));
		timer->Enabled = true;
	}

private: void DrawLine(System::Object^  sender, System::EventArgs^  e){
	Pen^ p = gcnew Pen(Color::White, 1);
	Point p1 = fl->couplingPoint;
	Point p2 = hook->couplingPoint;
	gr->DrawLine(p, p1, p2);
}
};