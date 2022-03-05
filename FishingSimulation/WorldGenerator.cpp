#pragma once
#include "Fisher.cpp"
namespace WorldGenerator {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

public ref class WorldGenerator {
private:
	Random^ rnd;
	Timer^ timer;
	Form^ form;
	Hook::Hook^ hook;
	int isNight = false;
	int spawnCount;
	bool simpleFisher = true;
	void Spawn(System::Object^  sender, System::EventArgs^  e) {
		if (spawnCount > 0) {
			Fish::Fish^ fish = gcnew Fish::Fish();
			fish->eatEvent += hook->tryEatHandler;
			hook->foodInWaterEvent += fish->foodInWaterHandler;
			hook->foodNotInWaterEvent += fish->foodNotInWaterHandler;
			form->Controls->Add(fish);
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
	void SpawnFish(Form^ form, Hook::Hook^ hook) {
		timer = gcnew Timer();
		timer->Tick += gcnew EventHandler(this, &WorldGenerator::Spawn);
		this->timer->Interval = 10;
		this->timer->Enabled = true;
		this->form = form;
		this->hook = hook;

	}
};
}