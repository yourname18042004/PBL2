#include "MenuAndBackground.h"
#include "ScrollBar.h"

FramesObject *background;
FramesObject* introduction1 = nullptr;
FramesObject* introduction2 = nullptr;
FramesObject* Options = nullptr;
FramesObject* quitNote = nullptr;

Buttons* buttonStart = nullptr;
Buttons* buttonTool = nullptr;
Buttons* buttonEnd = nullptr;
Buttons* introduce = nullptr;
Buttons* backIntro = nullptr;
Buttons* MusicOptions = nullptr;
Buttons* backOptions = nullptr;
Buttons* next = nullptr;
Buttons* Back = nullptr;
Buttons* quitNo = nullptr;
Buttons* quitYes = nullptr;

Buttons* abc = nullptr;

Text Question;

int introduceStatus;
bool musicOptions = false;
bool questionQuit = false;


ScrollHorizontal* volumeBackground_menu = nullptr; 

LoadMusic* backgroundMusic = nullptr;

Menu::Menu(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
Menu::~Menu() {

}
void Menu::init(int *volume, bool *check) {
	this->check = check;
	this->volume = volume;
	background = new FramesObject(new SDL_FRect{0, 0, 1440.0f, 720.0f}, "Data//Picture//Main_640_320_640_320.png", renderer, false);
	introduction1 = new FramesObject(new SDL_FRect{ 10,10,1400,700 }, "Data//Picture//Introducetion_2200_1100_2200_1100.png", renderer, false);
	introduction2 = new FramesObject(new SDL_FRect{ 10,10,1400,700 }, "Data//Picture//Introduction_2200_1100_2200_1100.png", renderer, false);
	Options = new FramesObject(new SDL_FRect{ 500,300,600,200 }, "Data//Picture//Setting_540_160_540_160.png", renderer, false);
	quitNote = new FramesObject(new SDL_FRect{ 450,200,700,200 }, "Data//Picture//ScoreTab_600_100_600_100.png", renderer, false);


	buttonStart = new Buttons(880,520, 280, 85, "Data//Picture//Button_350_100_700_100.png", renderer);
	buttonEnd = new Buttons(880, 620, 280, 85, "Data//Picture//ButtonEnd_350_100_700_100.png", renderer);
	buttonTool = new Buttons(1380, 660, 100, 100, "Data//Picture//Gear_100_100_200_100.png", renderer);
	introduce = new Buttons(1280, 660, 100, 100, "Data//Picture//huongdan_100_100_200_100.png", renderer);
	backIntro= new Buttons(1300, 100, 100, 100, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
	backOptions = new Buttons(1070, 340, 70, 70, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
	next = new Buttons(680, 600, 75, 75, "Data//Picture//Next_50_50_100_50.png", renderer);
	Back = new Buttons(580, 600, 75, 75, "Data//Picture//Back_50_50_100_50.png", renderer);
	MusicOptions = new Buttons(80, 660, 100, 100, "Data//Picture//music_100_100_200_100.png", renderer);
	quitNo = new Buttons(730, 380, 100, 100, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
	quitYes = new Buttons(830, 380, 100, 100, "Data//Picture//ButtonEnd_100_100_200_100.png", renderer);
	abc = new Buttons(995, 400, 50, 50, "Data//Picture//OK_100_100_200_100.png", renderer);

	Question.init(600, 250, 400, 60, "Data//Galhau_Regular.ttf", 50, { 255,0,0, 255 }, "Are you sure you want to quit?", renderer);

	backgroundMusic = new LoadMusic(4);
	backgroundMusic->addSound("Data//Sound//Ground.mp3");

	volumeBackground_menu = new ScrollHorizontal(620, 380, 250, 50, renderer);
	volumeBackground_menu->setValue(0, 128);
	
	// cho chạy map
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
	
	if (introduceStatus == 0 && !musicOptions && !questionQuit) {
		buttonStart->Setclick(Event.BUTTON_LEFT);
		buttonEnd->Setclick(Event.BUTTON_LEFT);
		buttonTool->Setclick(Event.BUTTON_LEFT);
		introduce->Setclick(Event.BUTTON_LEFT);
		if (introduce->Getclick()) {
			introduceStatus = 1;
		}
		
		MusicOptions->Setclick(Event.BUTTON_LEFT);
	}
	if (abc->Getclick()) {
		
		if (*check) *check = false;
		else *check = true;
	}
	if (next->Getclick()) {
		introduceStatus = 2;
	}
	if (Back->Getclick()) {
		introduceStatus = 1;
	}
	if (introduceStatus != 0) {
		backIntro->Setclick(Event.BUTTON_LEFT);
		next->Setclick(Event.BUTTON_LEFT);
		Back->Setclick(Event.BUTTON_LEFT);
		if (backIntro->Getclick()) introduceStatus = 0;
	}
	if (buttonEnd->Getclick()) {
		questionQuit = true;
	}
	if (buttonStart->Getclick()) {
		isRunning = false;
		Index = 0;
	}
	if (buttonTool->Getclick()) {
		isRunning = false;
		Index = 1;
	}
	if (MusicOptions->Getclick()) {
		musicOptions = true;
	}
	if (musicOptions) {
		abc->Setclick(Event.BUTTON_LEFT);
		volumeBackground_menu->MoveCroll(Event.BUTTON_LEFT_PRESS);
		backOptions->Setclick(Event.BUTTON_LEFT);
		if (backOptions->Getclick()) musicOptions = false;
	}
	if (questionQuit) {
		quitNo->Setclick(Event.BUTTON_LEFT);
		quitYes->Setclick(Event.BUTTON_LEFT);
	}
	if (quitYes->Getclick()) quit = true;
	if (quitNo->Getclick()) questionQuit = false;
	if (!*check) {
		*volume = 0;
		volumeBackground_menu->setValue(*volume);
	}
	else {
		*volume = volumeBackground_menu->getValue();
	}
	
	backgroundMusic->updateVolume(*volume);
}
void Menu::render() {
	SDL_RenderClear(renderer);

	background->Get_Texture();
	buttonStart->Render();
	buttonEnd->Render();
	buttonTool->Render();
	introduce->Render();
	MusicOptions->Render();
	
	
	
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

	if (musicOptions) {
		Options->Get_Texture();
		volumeBackground_menu->Render();
		backOptions->Render();
		if (!*check) {
			abc->Render();
		}
	}
	if (questionQuit) {
		quitNote->Get_Texture();
		quitNo->Render();
		quitYes->Render();
		Question.render();
	}

	SDL_RenderPresent(renderer);
}
void Menu::destroy() {
	backgroundMusic->stopMusic();
}
void Menu::Loop() {

	isRunning = true;


	volumeBackground_menu->setValue(*(this->volume));
	
	backgroundMusic->playSound(-1);
	
	while (isRunning && !quit) {
		
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();
	}
	backgroundMusic->stopMusic();
}
