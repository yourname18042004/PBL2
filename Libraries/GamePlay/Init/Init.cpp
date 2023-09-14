#include "Init.h"


//Manager ManagerObject;
//Racket* RacKet1 = nullptr;
Fly* Fly1 = nullptr;
HandelEvent handelEvent;
ObjectLinkList<Fly>*  FlyLinkList = nullptr;

const int FPS_rate = 120;

Window::Window() {}

char text[100] = "FLY KILLER SCORE:";// thanh ghi điểm số, ban đầu sẽ không in điểm

Window::~Window() {}
void Window::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) isRunning = false;

	// Nhận sự kiện
	handelEvent.Handel(event);
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
		//SDL_ShowCursor(false);//Ẩn trỏ chuột mặc định

		TTF_Init();
		isRunning = true;
		mtimer = Timer::Init();

		//Fly1 = (Fly*)new Object(100, 100, 100, 100, renderer);
		//Fly1->Init();
		FlyLinkList = new ObjectLinkList<Fly>();
		FlyLinkList->push((Fly*)new Object(100, 100, 100, 100, renderer));
		FlyLinkList->push((Fly*)new Object(400, 100, 100, 100, renderer));
		FlyLinkList->push((Fly*)new Object(100, 400, 100, 100, renderer));
		FlyLinkList->push((Fly*)new Object(400, 400, 100, 100, renderer));
		while (!FlyLinkList->setIndex())
		{
			FlyLinkList->getIndex()->getData()->Init();
		}
		FlyLinkList->resetIndex();
		//FlyLinkList.push((Fly*)new Object(400, 400, 100, 100, renderer));
		//FlyLinkList.push((Fly*)new Object(600, 400, 100, 100, renderer));
		//FlyLinkList.push((Fly*)new Object(400, 700, 100, 100, renderer));
	}
	else
	{
		isRunning = false;
	}
	
}

void Window::update()
{	
	mtimer->Update();
	//Fly1->UpdateFly();
	
	while (!FlyLinkList->setIndex())
	{
		FlyLinkList->getIndex()->getData()->UpdateFly();
	}
	FlyLinkList->resetIndex();
	//FlyLinkList.resetIndex();
}

void Window::render()
{	
	if (mtimer->DeltaTime() >= 1.0f / FPS_rate) {
		SDL_RenderClear(renderer);
		
		while (!FlyLinkList->setIndex())
		{
			FlyLinkList->getIndex()->getData()->Render();
		}
		FlyLinkList->resetIndex();
		SDL_RenderPresent(renderer);
		mtimer->reset();
	}
	
}
void Window::destroy()
{
	mtimer->release();
	mtimer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


