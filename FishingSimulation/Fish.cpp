namespace Fish {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
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
			 System::Drawing::Image^ catchImage = System::Drawing::Image::FromFile("..\\static\\catch_fish.png");
			 System::Drawing::Image^ swimImage = System::Drawing::Image::FromFile("..\\static\\fish.png");
	public: 
		void Pick() {
			if (!isCatch) return;
			if (!this->Visible) return;
			this->Visible = false;
			this->timerEat->Enabled = false;
			this->timerMove->Enabled = false;
			this->Parent->Controls->Remove(this);
			return;
		}
		void Catch() {
			if (isCatch) return;
			this->timerEat->Enabled = false;
			this->timerMove->Enabled = false;
			this->isCatch = true;
			this->Size = System::Drawing::Size(sizeY, sizeX);
			this->Image = catchImage;
			this->Image->RotateFlip(RotateFlipType::Rotate90FlipY);
			int hookMiddleX = foodArea.Location.X + foodArea.Size.Width / 2;
			int hookMiddleY = foodArea.Location.Y - foodArea.Size.Height / 2;
			int newX = hookMiddleX - sizeY / 3.75;
			this->Location = System::Drawing::Point(newX, hookMiddleY);
			this->Refresh();
			return;
		}
		void Free() {
			if (!isCatch) return;
			if (!this->Visible) return;
			this->timerEat->Enabled = true;
			this->timerMove->Enabled = true;
			this->Image->RotateFlip(RotateFlipType::Rotate270FlipY);
			return;
		}
		
	public:
		delegate void EatEventHandler(Fish^);
		delegate void FoodInWaterHandler(Point, System::Drawing::Size);
		FoodInWaterHandler^ foodInWaterHandler;
		delegate void FoodNotInWaterHandler();
		FoodNotInWaterHandler^ foodNotInWaterHandler;
		static event EatEventHandler^ eatEvent;

		Fish()
		{
			this->Image = swimImage;
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
			this->foodNotInWaterHandler = gcnew FoodNotInWaterHandler(this, &Fish::FoodNotInWater);
			this->foodInWaterHandler = gcnew FoodInWaterHandler(this, &Fish::FoodInWater);
		}

	private:
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
		if (Rectangle(this->Location, this->Size).IntersectsWith(foodArea)) eatEvent(this);
	}


	};
}