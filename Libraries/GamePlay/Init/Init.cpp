#include "Init.h"


Manager ManagerObject;
HandelEvent handelEvent;

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
		SDL_ShowCursor(false);//Ẩn trỏ chuột mặc định

		TTF_Init();
		isRunning = true;
		mtimer = Timer::Init();

		//Fly1 = (Fly*)new Object(100, 100, 100, 100, renderer);
		//Fly1->Init();
		for (int i = 0; i < 100; i++) {
			int ranx = rand() % 1400;
			int rany = rand() % 720;
			ManagerObject.Add(new Fly(ranx, rany, 100, 100, Vector{1,3}, renderer));
		}
		ManagerObject.Add(new Racket(100, 100, 75, 75, renderer, &handelEvent));
	
	}
	else
	{
		isRunning = false;
	}
	
}

void Window::update()
{	
	mtimer->Update();
	ManagerObject.Update();
}

void Window::render()
{	
	if (mtimer->DeltaTime() >= 1.0f / FPS_rate) {
		SDL_RenderClear(renderer);
		ManagerObject.render(renderer);
		SDL_RenderPresent(renderer);
		std::cout << mtimer->DeltaTime() << std::endl;
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


