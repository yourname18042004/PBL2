#include "MenuAndBackground.h"

HandelEvent Event1;
FramesObject *background;
SDL_FRect Dest;
Buttons* buttonStart = nullptr;
Menu::Menu(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
Menu::~Menu() {

}
void Menu::init() {
	Dest.x = 0;
	Dest.y = 0;
	Dest.w = 1440.0f;
	Dest.h = 720.0f;
	background = new FramesObject(&Dest, "Data//Main_640_320_640_320.png", renderer, false);
	buttonStart = new Buttons(870, 550, 300, 150, "Data//Button_500_250_500_250.png", renderer);
	isRunning = true;
}
void Menu::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) isRunning = false;

	// Nhận sự kiện
	Event1.Handel(event);
}
void Menu::update() {
	buttonStart->Setclick(Event1.BUTTON_LEFT);
	if (buttonStart->Getclick()) isRunning = false;
}
void Menu::render() {
	SDL_RenderClear(renderer);
	background->Get_Texture();
	buttonStart->Render();
	SDL_RenderPresent(renderer);
}
void Menu::destroy() {
	
}
void Menu::Loop() {
	while (isRunning) {
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();

	}
}