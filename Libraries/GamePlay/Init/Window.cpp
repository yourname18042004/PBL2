#include "Window.h"

bool Quit = false;

Gameplay* gameplay = nullptr;
Menu* background = nullptr;
ListMap* map = nullptr;
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

		map = new ListMap(renderer);
		map->init();

		gameplay->setChoose(map->getChoose());

		//Link background với gameplay
		scene1.push(background);
		scene1.push(map);
		scene1.push(gameplay);
	}
	else
	{
		isRunning = false;
	}
}

void Window::update()
{	
	while (scene1.getIndex() != NULL)
	{
		scene1.getIndex()->getData()->Loop();
		if (scene1.getIndex()->getData()->quit) return;
		std::cout << scene1.getIndex()->getData()->back << std::endl;
		if (scene1.getIndex()->getData()->back) {
			scene1.GoPrevious();
			scene1.getIndex()->getData()->next = false;

		}
		if (scene1.getIndex()->getData()->next) {
			scene1.GoNext();
			scene1.getIndex()->getData()->back = false;
		}
	}
}
void Window::destroy()
{
	mtimer->release();
	mtimer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


