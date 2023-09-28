#include "MenuAndBackground.h"


FramesObject *background;
SDL_FRect Dest;
Buttons* buttonStart = nullptr;
Buttons* buttonEnd = nullptr;


Menu::Menu(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
Menu::~Menu() {

}
void Menu::init() {

	background = new FramesObject(new SDL_FRect{0, 0, 1440.0f, 720.0f}, "Data//Main_640_320_640_320.png", renderer, false);
	buttonStart = new Buttons(880,520, 280, 85, "Data//Button_350_100_700_100.png", renderer);
	buttonEnd = new Buttons(880, 620, 280, 85, "Data//ButtonEnd_350_100_700_100.png", renderer);
	
	isRunning = true;
	next = false;
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
	if (buttonEnd->Getclick()) quit = true;
	if (buttonStart->Getclick()) {
		isRunning = false;
		next = true;
	}
}
void Menu::render() {
	SDL_RenderClear(renderer);

	background->Get_Texture();
	buttonStart->Render();
	buttonEnd->Render();


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
void Menu::SetIsrunning() {
	isRunning = true;
}