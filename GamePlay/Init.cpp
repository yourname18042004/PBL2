#include "Init.h"
#include "Object.h"
#include "Fly.h"

Object Butter, Bee;  Fly fly1;
Window::Window(){}
Window::~Window(){}
void Window::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) isRunning = false;
}

void Window::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// Tạo cửa sổ và render
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flag = 0;
		if (fullscreen)
			flag = SDL_WINDOW_FULLSCREEN;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);

		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	fly1.Init(40, 80, 100, 100, renderer, "Data//fly_200_100.png");
	Butter.Init(40, 80, 100, 100, renderer, "Data//butterfly1_700_100.png");
	Bee.Init(100, 200, 100, 100, renderer, "Data//bee_200_100.png");
}

void Window::update()
{	
	Butter.animation();
	Butter.update(Vector {2,2});

	fly1.animation();
	fly1.update(Vector{ 1,0 });

	Bee.animation();
	Bee.update(Vector{ 10,10 });
	
	SDL_Delay(50);

}

void Window::render()
{
	SDL_RenderClear(renderer);

	Butter.Render(renderer);
	fly1.Render(renderer);
	Bee.Render(renderer);

	SDL_RenderPresent(renderer);
	
}
void Window::destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


