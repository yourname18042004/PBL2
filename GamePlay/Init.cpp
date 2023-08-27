#include "Init.h"

SDL_Texture* ruoi;
SDL_Rect srcR, destR;

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
	ruoi = LoadImage::Load("D:/C++/PBL2/Data/ruoi1.png", renderer);
}

void Window::update()
{
	srcR.x = (t % 3) * 300;
	srcR.y = 300;
	srcR.w = 300;
	srcR.h = 900;
	
	destR.x = 200;
	destR.y = 100;
	destR.w = 500;
	destR.h = 500;
	t++;
}

void Window::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, ruoi, &srcR, &destR);

	SDL_RenderPresent(renderer);
}
void Window::destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


