#include "MenuAndBackground.h"


FramesObject *background;
SDL_FRect Dest;
Buttons* buttonStart = nullptr;
Buttons* buttonTool = nullptr;
Buttons* buttonEnd = nullptr;


Menu::Menu(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
Menu::~Menu() {

}
void Menu::init() {

	background = new FramesObject(new SDL_FRect{0, 0, 1440.0f, 720.0f}, "Data//Picture//Main_640_320_640_320.png", renderer, false);
	buttonStart = new Buttons(880,520, 280, 85, "Data//Picture//Button_350_100_700_100.png", renderer);
	buttonEnd = new Buttons(880, 620, 280, 85, "Data//Picture//ButtonEnd_350_100_700_100.png", renderer);
	buttonTool = new Buttons(880, 120, 280, 85, "Data//Picture//ButtonEnd_350_100_700_100.png", renderer);

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
	buttonStart->Setclick(Event.BUTTON_LEFT);
	buttonEnd->Setclick(Event.BUTTON_LEFT);
	buttonTool->Setclick(Event.BUTTON_LEFT);
	if (buttonEnd->Getclick()) quit = true;
	if (buttonStart->Getclick()) {
		isRunning = false;
		Index = 0;
	}
	if (buttonTool->Getclick()) {
		isRunning = false;
		Index = 1;
	}
}
void Menu::render() {
	SDL_RenderClear(renderer);

	background->Get_Texture();
	buttonStart->Render();
	buttonEnd->Render();
	buttonTool->Render();

	SDL_RenderPresent(renderer);
}
void Menu::destroy() {
	
}
void Menu::Loop() {
	isRunning = true;
	while (isRunning && !quit) {
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();
	}
}
