﻿#include "Window.h"

bool Quit = false;

Gameplay* gameplay = nullptr;
Menu* background = nullptr;
ObjectLinkList <Scene> scene1;

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
		mtimer = Timer::Init();//Khởi tạo thời gian
		//khởi tạo menu
		background = new Menu(renderer);
		background->init();
		//khởi tạo gameplay
		gameplay = new Gameplay(renderer);
		gameplay->init();
		//Link background với gameplay
		scene1.push(background);
		scene1.push(gameplay);
		
	}
	else
	{
		isRunning = false;
	}
	
}

void Window::update()
{	
	while (true)
	{
		scene1.getIndex()->getData()->Loop();//BackGroundLoop
		if (scene1.getIndex()->getData()->quit) return;//Neu tat cua so-> thoat loop
		// Nhảy qua Gameplay
		scene1.GoNext();
	
		//Loop Gameplay
		scene1.getIndex()->getData()->Loop();

		if (scene1.getIndex()->getData()->quit) return;// Tắt cửa sổ gameplay -> thoát loop
			//Set is Running gameplay
		scene1.getIndex()->getData()->SetIsrunning();
			//Init fly gameplay
		scene1.getIndex()->getData()->init();
		
			//Set isRunning background
		scene1.getIndex()->getPrevious()->getData()->SetIsrunning();
			//Gọi background loop
		scene1.resetIndex();
	}
}
void Window::destroy()
{
	mtimer->release();
	mtimer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


