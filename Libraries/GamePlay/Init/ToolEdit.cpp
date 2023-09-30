#include "ToolEdit.h"

Buttons* toolback = nullptr;

Tool::Tool(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
Tool::~Tool() {

}
void Tool::init() {
	toolback = new Buttons(630, 450, 100, 100, "Data//ButtonBack_100_100_200_100.png", renderer);
	isRunning = true;
	Index = -1;
	back = false;
}
void Tool::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) quit = true;

	// Nhận sự kiện
	Event.Handel(event);
}
void Tool::update() {
	toolback->Setclick(Event.BUTTON_LEFT);
	if (toolback->Getclick()) {
		isRunning = false;
		back = true;
	}
}
void Tool::render() {
	SDL_RenderClear(renderer);
	toolback->Render();
	SDL_RenderPresent(renderer);
}
void Tool::destroy() {

}
void Tool::Loop() {
	isRunning = true;
	while (isRunning && !quit) {
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();
	}
}

