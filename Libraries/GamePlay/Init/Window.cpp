#include "Window.h"



Gameplay* gameplay = nullptr;
Menu* background = nullptr;

const int FPS_rate = 120;

Window::Window() {}

char text[100] = "FLY KILLER SCORE:";// thanh ghi điểm số, ban đầu sẽ không in điểm

Window::~Window() {}


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
		SDL_ShowCursor(false);//Ẩn trỏ chuột mặc định

		TTF_Init();
		isRunning = true;
		mtimer = Timer::Init();

		background = new Menu(renderer);
		background->init();
		gameplay = new Gameplay(renderer);
		gameplay->init(xpos, ypos, width, height, flag);
	}
	else
	{
		isRunning = false;
	}
	
}

void Window::update()
{	
	background->Loop();
	gameplay->Loop();
}

void Window::destroy()
{
	mtimer->release();
	mtimer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


