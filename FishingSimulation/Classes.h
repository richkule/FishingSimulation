using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Hook : public System::Windows::Forms::PictureBox {
private:
	bool isEmpty = true;
	int posX = 600;
	int posY = 85;
public:
	int sizeX = 20;
	int sizeY = 25;
public:
	Hook(void)
	{
		this->Image = System::Drawing::Image::FromFile("..\\static\\hook.png");
		this->Location = System::Drawing::Point(posX, posY);
		this->Size = System::Drawing::Size(sizeX, sizeY);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::Transparent;

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
};


public ref class Float : public System::Windows::Forms::PictureBox {
private:
	bool isEmpty = true;
	int posX = 400;
	int sizeX = 25;
	int sizeY = 50;
	int deep = 40;
	System::Drawing::Image^ diveDefault = System::Drawing::Image::FromFile("..\\static\\floatDefault.png");
	int defaultYPos = 220;
	System::Drawing::Image^ dive25 = System::Drawing::Image::FromFile("..\\static\\float25.png");
	int dive25YPos = 232;
	System::Drawing::Image^ dive50 = System::Drawing::Image::FromFile("..\\static\\float50.png");
	int dive50YPos = 234;
	System::Drawing::Image^ dive75 = System::Drawing::Image::FromFile("..\\static\\float75.png");
	int dive75YPos = 238;
	System::Drawing::Image^ dive100 = System::Drawing::Image::FromFile("..\\static\\float100.png");
	int dive100YPos = 246;
public:
	Float(void)
	{
		this->Image = System::Drawing::Image::FromFile("..\\static\\floatDefault.png");
		this->Location = System::Drawing::Point(posX, defaultYPos);
		this->Size = System::Drawing::Size(sizeX, sizeY);
		this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->BackColor = System::Drawing::Color::Transparent;

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
};

public ref class Fish : public System::Windows::Forms::PictureBox {
private: System::Windows::Forms::Timer^  timer;
		 int speedX = 0;
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
	Random^ random = gcnew Random();
	speedX = random->Next(-10, 10);
}
private: void checkCatch(void) {
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