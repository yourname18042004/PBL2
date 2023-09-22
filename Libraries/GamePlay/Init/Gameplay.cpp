#include "Gameplay.h"

//Khai bao
Manager ManagerObject;

Gameplay::Gameplay(SDL_Renderer* renderer){
	this->renderer = renderer;
}

Gameplay::~Gameplay(){}

void Gameplay::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) isRunning = false;

	// Nhận sự kiện
	Event.Handel(event);
}

void Gameplay::init(int xpos, int ypos, int width, int height, bool fullscreen)
{
		
		for (int i = 0; i < 1; i++) {
			int ranx = rand() % 1400;
			int rany = rand() % 720;
			ManagerObject.Add(new Fly(ranx, rany, 100, 100, Vector{ 0.01,0.03 }, renderer));
		}
		ManagerObject.Add(new Racket(100, 100, 75, 75, renderer, &Event));
		
		isRunning = true;
}

void Gameplay::Loop() {
	SDL_ShowCursor(false);
	while(isRunning){
		handleEvent();
		update();
		render();
	}
}

void Gameplay::update()
{
	Timer::sInit->Update();
	ManagerObject.Update();
}

void Gameplay::render()
{
	if (Timer::sInit->DeltaTime() >= 1.0f / FPS_rate) {
		SDL_RenderClear(renderer);
		ManagerObject.render(renderer);
		SDL_RenderPresent(renderer);
		Timer::sInit->reset();
	}
}
void Gameplay::destroy()
{
	Timer::sInit->release();
	SDL_DestroyRenderer(renderer);
}
