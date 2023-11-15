#include "MenuAndBackground.h"


FramesObject *background;


Buttons* buttonStart = nullptr;
Buttons* buttonTool = nullptr;
Buttons* buttonEnd = nullptr;
Buttons* introduce = nullptr;
Buttons* backIntro = nullptr;

Buttons* next = nullptr;
Buttons* Back = nullptr;

int introduceStatus;

FramesObject* introduction1 = nullptr;
FramesObject* introduction2 = nullptr;

LoadMusic* backgroundMusic = nullptr;

Menu::Menu(SDL_Renderer* renderer) {
	
	this->renderer = renderer;
}
Menu::~Menu() {

}
void Menu::init() {

	background = new FramesObject(new SDL_FRect{0, 0, 1440.0f, 720.0f}, "Data//Picture//Main_640_320_640_320.png", renderer, false);
	buttonStart = new Buttons(880,520, 280, 85, "Data//Picture//Button_350_100_700_100.png", renderer);
	buttonEnd = new Buttons(880, 620, 280, 85, "Data//Picture//ButtonEnd_350_100_700_100.png", renderer);
	buttonTool = new Buttons(1380, 660, 100, 100, "Data//Picture//Gear_100_100_200_100.png", renderer);
	introduce = new Buttons(1280, 660, 100, 100, "Data//Picture//huongdan_100_100_200_100.png", renderer);
	backIntro= new Buttons(1300, 100, 100, 100, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
	next = new Buttons(680, 600, 75, 75, "Data//Picture//Next_50_50_100_50.png", renderer);
	Back = new Buttons(580, 600, 75, 75, "Data//Picture//Back_50_50_100_50.png", renderer);

	introduction1 = new FramesObject(new SDL_FRect{10,10,1400,700 }, "Data//Picture//Introducetion_2200_1100_2200_1100.png", renderer, false);
	introduction2 = new FramesObject(new SDL_FRect{ 10,10,1400,700 }, "Data//Picture//Introduction_2200_1100_2200_1100.png", renderer, false);

	backgroundMusic = new LoadMusic(4);
	backgroundMusic->addSound("Data//Sound//Ground.mp3");

	introduceStatus = 0;

	isRunning = true;
	Index = -1;
	back = false;
}
void Menu::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) quit = true;

	// Nhận sự kiện
	Event.Handel(event);
}
void Menu::update() {
	
	if (introduceStatus == 0) {
		buttonStart->Setclick(Event.BUTTON_LEFT);
		buttonEnd->Setclick(Event.BUTTON_LEFT);
		buttonTool->Setclick(Event.BUTTON_LEFT);
	}
	introduce->Setclick(Event.BUTTON_LEFT);
	if (introduceStatus != 0) {
		backIntro->Setclick(Event.BUTTON_LEFT);
		next->Setclick(Event.BUTTON_LEFT);
		Back->Setclick(Event.BUTTON_LEFT);
		if (backIntro->Getclick()) introduceStatus = false;
	}
	if (buttonEnd->Getclick()) quit = true;
	if (buttonStart->Getclick()) {
		isRunning = false;
		Index = 0;
	}
	if (buttonTool->Getclick()) {
		isRunning = false;
		Index = 1;
	}
	if (introduce->Getclick() || Back->Getclick()) {
		introduceStatus = 1;
	}
	if (next->Getclick()) {
		introduceStatus = 2;
	}
}
void Menu::render() {
	SDL_RenderClear(renderer);

	background->Get_Texture();
	buttonStart->Render();
	buttonEnd->Render();
	buttonTool->Render();
	introduce->Render();
	
	if (introduceStatus == 1) {
		introduction1->Get_Texture();
		
	}
	if (introduceStatus == 2) {
		introduction2->Get_Texture();
	}
	if (introduceStatus != 0) {
		backIntro->Render();
		Back->Render();
		next->Render();
	}
	SDL_RenderPresent(renderer);
}
void Menu::destroy() {
	backgroundMusic->stopMusic();
}
void Menu::Loop() {

	isRunning = true;
	backgroundMusic->playSound(-1);
	while (isRunning && !quit) {
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();
	}
	backgroundMusic->stopMusic();
}
