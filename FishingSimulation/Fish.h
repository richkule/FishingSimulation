namespace Fish {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	const int PICK_STATUS = 1;
	const int FREE_STATUS = 2;
	const int CATCH_STATUS = 3;
	public ref class Fish : public System::Windows::Forms::PictureBox {
	private: System::Windows::Forms::Timer^  timerEat;
			 System::Windows::Forms::Timer^  timerMove;
			 int minSpeedX = -5;
			 int maxSpeedX = 5;
			 int minSpeedY = -5;
			 int maxSpeedY = 5;
			 int speedX = 0;
			 int speedY = 0;
			 int sizeX = 110;
			 int sizeY = 50;
			 int minXPos = 280;
			 int minYPos = 450;
			 int maxXPos = 1200;
			 int maxYPos = 750;
			 bool isForwardDirection = true;
			 bool isCatch = false;
			 bool foodHere;
			 Rectangle foodArea;
			 Random^ rnd = gcnew Random();
	property int catchStatus {
		void set(int catchStatus) {
			switch (catchStatus)
			{
			PICK_STATUS:
				if (!isCatch) return;
				this->Visible = false;
				this->timerEat->Enabled = false;
				this->timerMove->Enabled = false;
				this->Parent->Controls->Remove(this);
				return;
			CATCH_STATUS:
				this->timerEat->Enabled = false;
				this->timerMove->Enabled = false;
				this->isCatch = true;
				this->Size = System::Drawing::Size(sizeY, sizeX);
				this->Image = System::Drawing::Image::FromFile("..\\static\\catch_fish.png");
				this->Image->RotateFlip(RotateFlipType::Rotate90FlipY);
			}
			if (catchStatus == PICK_STATUS) {
				if (!isCatch) return;
				this->Visible = false;
				this->timerEat->Enabled = false;
				this->timerMove->Enabled = false;
				this->Parent->Controls->Remove(this);
				return;
			}
			

			int hookMiddleX = hook->Location.X + hook->sizeX / 2;
			int hookMiddleY = hook->Location.Y - hook->sizeY / 2;
			int newX = hookMiddleX - sizeY / 2;
			this->Location = System::Drawing::Point(newX, hookMiddleY);
			this->hook->Visible = false;
			this->Refresh();
		}
		int get() {
			return this->isCatch;
		}
	}
	public:
		delegate void EatEventHandler(Fish^);
		static event EatEventHandler^ EatEvent;

		Fish()
		{
			this->Image = System::Drawing::Image::FromFile("..\\static\\fish.png");
			this->Spawn();
			this->Size = System::Drawing::Size(sizeX, sizeY);
			this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->BackColor = System::Drawing::Color::Transparent;
			this->timerMove = gcnew System::Windows::Forms::Timer();
			this->timerMove->Tick += gcnew System::EventHandler(this, &Fish::Move);
			this->timerMove->Enabled = true;
			this->timerEat = gcnew System::Windows::Forms::Timer();
			this->timerEat->Tick += gcnew System::EventHandler(this, &Fish::TryEat);
			this->timerEat->Interval = 500;
			this->timerEat->Enabled = true;
		}

	public:
		void Catch() {
			if (!isCatch) return;
			this->Visible = false;
			this->timerEat->Enabled = false;
			this->timerMove->Enabled = false;
			this->Parent->Controls->Remove(this);
		}
		void FoodNotInWater() {
			foodHere = false;
		}
		void FoodInWater(Point loc, System::Drawing::Size size) {
			foodHere = true;
			foodArea = Rectangle(loc, size);
		}
	private:
		void Spawn() {
			this->Location = System::Drawing::Point(rnd->Next(minXPos, maxXPos + 1), rnd->Next(minYPos, maxYPos + 1));
		}
	private: System::Void Move(System::Object^  sender, System::EventArgs^  e) {
		if (rnd->Next(1, 10) == 5) {
			speedX = rnd->Next(minSpeedX, maxSpeedX + 1);
			speedY = rnd->Next(minSpeedY, maxSpeedY + 1);
		}
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
		Point newPoint = System::Drawing::Point(this->Location.X + this->speedX, this->Location.Y + this->speedY);
		if (newPoint.X > maxXPos) return;
		if (newPoint.X < minXPos) return;
		if (newPoint.Y > maxXPos) return;
		if (newPoint.Y < minYPos) return;
		this->Location = newPoint;
	}
	private: void TryEat(System::Object^  sender, System::EventArgs^  e) {
		if (!foodHere) return;
		if (Rectangle(this->Location, this->Size).IntersectsWith(foodArea)) EatEvent(this);
	}


	};
}