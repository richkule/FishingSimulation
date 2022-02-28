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
	int dive25YPos = defaultYPos+1;
	System::Drawing::Image^ dive50 = System::Drawing::Image::FromFile("..\\static\\float50.png");
	int dive50YPos = defaultYPos+9;
	System::Drawing::Image^ dive75 = System::Drawing::Image::FromFile("..\\static\\float75.png");
	int dive75YPos = defaultYPos+13;
	System::Drawing::Image^ dive100 = System::Drawing::Image::FromFile("..\\static\\float100.png");
	int dive100YPos = defaultYPos+19;
	System::Drawing::Image^ floatUp = System::Drawing::Image::FromFile("..\\static\\float_up.png");
	EventHandler^ changeCouplePointStartHandler;
	EventHandler^ changeCouplePointEndHandler;
	EventHandler^ catchHandler;
public:
	Point downCouplingPoint;
	Point upperCouplingPoint;
	Float(EventHandler^ changeCouplePointStartHandler, EventHandler^ changeCouplePointEndHandler)
	{
		this->changeCouplePointStartHandler = changeCouplePointStartHandler;
		this->changeCouplePointEndHandler = changeCouplePointEndHandler;
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
		changeCouplePointStartHandler(this, gcnew EventArgs());
		downCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y + this->Size.Height);
		upperCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y);
		changeCouplePointEndHandler(this, gcnew EventArgs());
		timer->Enabled = true;
		Visible = true;
	}
	void GetUp(Point pnt) {
		this->posX = posX;
		this->Location = pnt;
		this->Image = floatUp;
		changeCouplePointStartHandler(this, gcnew EventArgs());
		downCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y + this->Size.Height);
		upperCouplingPoint = Point(this->Location.X + this->Size.Width / 2, this->Location.Y);
		changeCouplePointEndHandler(this, gcnew EventArgs());
		timer->Enabled = false;
		Visible = true;
	}
	void AddCatchHandler(EventHandler^ catchHandler) {
		this->catchHandler += catchHandler;
	}
private:
	void ChangeCouplePoint(System::Drawing::Point loc, System::Drawing::Image^ image) {
		changeCouplePointStartHandler(this, gcnew EventArgs());
		this->Location = loc;
		this->Image = image;
		upperCouplingPoint.Y = loc.Y;
		changeCouplePointEndHandler(this, gcnew EventArgs());
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
public: void Catch(System::Object^  sender, System::EventArgs^  e) {
	catchHandler(sender, e);
	this->Refresh();
}

public: void Touch(System::Object^  sender, System::EventArgs^  e) {
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





public ref class Tackle : public Component {
private:
	bool isActivate = false;
	Float^ fl;
	Graphics^ gr;
	Control^ control;
	Timer^ timer = gcnew Timer();
	Color color;
	Point fsp;
	int defaultWidth = 2;
public:
	Hook^ hook;
	Tackle(Control^ control, Color color)
	{
		this->control = control;
		this->color = color;
		gr = control->CreateGraphics();
		hook = gcnew Hook();
		fl = gcnew Float(gcnew System::EventHandler(this, &Tackle::ChangeCouplePointStart), gcnew System::EventHandler(this, &Tackle::ChangeCouplePointEnd));
		hook->AddCatchHandler(gcnew System::EventHandler(fl, &Float::Catch));
		hook->AddTouchHandler(gcnew System::EventHandler(fl, &Float::Touch));
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
		fl->Activate(posX);
		hook->Activate(Point(fl->downCouplingPoint.X, fl->downCouplingPoint.Y + height));
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
	void AddCatchHandler(EventHandler^ catchHandler) {
		fl->AddCatchHandler(catchHandler);
	}
	Hook^ GetHook() {
		return hook;
	}
	void SetFsp(Point fsp) {
		timer->Enabled = false;
		this->ClearLine();
		this->fsp = fsp;
		timer->Enabled = true;
	}
	void ChangeCouplePointStart(System::Object^  sender, System::EventArgs^  e) {
		timer->Enabled = false;
		this->ClearLine();
	}
	void ChangeCouplePointEnd(System::Object^  sender, System::EventArgs^  e) {
		timer->Enabled = true;
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
};


public ref class Fisher : public System::Windows::Forms::PictureBox {
protected:
	Point posCatch = Point(133, 42);
	System::Drawing::Size sizeCatch = System::Drawing::Size(99, 392);
	Point posWait = Point(133, 194);
	System::Drawing::Size sizeWait = System::Drawing::Size(280, 242);
	Tackle^ tackle;
	Random^ rnd =gcnew Random();
	int minTacklePos = 133+280;
	int maxTacklePos = minTacklePos+500;
	int minTackleHeight = 10;
	int maxTackleHeight = 300;
	bool isWait = false;
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

	void Catch(System::Object^  sender, System::EventArgs^  e) {
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

	void Throw(System::Object^  sender, System::EventArgs^  e) {
		this->Wait();
		this->SetTackle();
	}
public:
	Fisher(Control^ control, Color color)
	{
		tackle = gcnew Tackle(control, color);
		tackle-> AddCatchHandler(gcnew System::EventHandler(this, &Fisher::AutoCatch));
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
	void AutoCatch(System::Object^  sender, System::EventArgs^  e) {
		this->waitTaimer->Enabled = false;
		this->waitTaimer->Interval = 2000;
		this->waitTaimer->Enabled = true;
	}
	void Action(System::Object^  sender, System::EventArgs^  e) {
		this->waitTaimer->Enabled = false;
		this->waitTaimer->Interval = 30000;
		if (this->isWait) {
			this->Catch(this, gcnew EventArgs());
			this->waitTaimer->Interval = 2000;
		}
		else {
			this->Throw(this, gcnew EventArgs());
			this->waitTaimer->Interval = 30000;
		}
		this->waitTaimer->Enabled = true;
	}
	Hook^ GetHook() {
		return tackle->GetHook();
	}
};

public ref class WorldGenerator{
private:
	Random^ rnd;
	Timer^ timer;
	Form^ form;
	Hook^ hook;
	int isNight = false;
	int spawnCount;
	bool simpleFisher = true;
	void Spawn(System::Object^  sender, System::EventArgs^  e) {
		if (spawnCount > 0) {
			form->Controls->Add(gcnew Fish(hook));
			spawnCount -= 1;
		}
		else {
			timer->Enabled = false;
		}
	}
public: 
	WorldGenerator() {
		rnd = gcnew Random();
		if (rnd->Next(1, 4) == 1) {
			isNight = true;
			spawnCount = 10;
		}
		else {
			spawnCount = 20;
		}
	}
		System::Drawing::Image^ ReturnWhetherImage() {
			if (isNight) {
				return  System::Drawing::Image::FromFile("..\\static\\moon.png");
			}
			else {
				return System::Drawing::Image::FromFile("..\\static\\sun.png");
			}
		}
		System::Drawing::Color ReturnColor() {
			if (isNight) {
				return  System::Drawing::Color::MidnightBlue;
			}
			else {
				return System::Drawing::Color::DeepSkyBlue;
			}
		}
		void SpawnFish(Form^ form, Hook^ hook) {
			timer = gcnew Timer();
			timer->Tick += gcnew EventHandler(this, &WorldGenerator::Spawn);
			this->timer->Interval = 10;
			this->timer->Enabled = true;
			this->form = form;
			this->hook = hook;

		}
};

public ref class FisherWithBoat : Fisher {
private:
	PictureBox^ boat;
	Timer^ timerMove;
	int maxXPos = 800;
	int minXPos = 0;
	int yPosBoat = 412;
	int speedX = 0;
public: FisherWithBoat(Control^ control, Color color) : Fisher(control,color){
	boat = gcnew PictureBox();
	boat->BackColor = Color::Transparent;
	boat->Image = System::Drawing::Image::FromFile("..\\static\\boat.png");
	boat->Location = Point(this->Location.X - 120, yPosBoat);
	boat->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
	boat->Size = System::Drawing::Size(263, 54);
	boat->Visible = true;
	control->Controls->Add(boat);
	this->timerMove = gcnew System::Windows::Forms::Timer();
	this->timerMove->Tick += gcnew System::EventHandler(this, &FisherWithBoat::Move);
	this->timerMove->Enabled = false;

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
			this->Catch(this, gcnew EventArgs());

		}
		void Left(System::Object^  sender, System::EventArgs^  e) {
			speedX = -40;
			timerMove->Enabled = true;
		}
		void Right(System::Object^  sender, System::EventArgs^  e) {
			speedX = 40;
			timerMove->Enabled = true;
		}
		void KeyUp(System::Object^  sender, System::EventArgs^  e) {
			timerMove->Enabled = false;
			this->Catch(this, gcnew EventArgs());
		}
};