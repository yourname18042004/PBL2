#include "Window.h"

bool Quit = false;

Gameplay* gameplay = nullptr;
Menu* background = nullptr;
ListMap* map = nullptr;
Tool* tool = nullptr;

ObjectLinkList <Scene> scene1;
Tree <Scene> scene2;
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
		tool = new Tool(renderer);
		tool->init();
		gameplay->setChoose(map->getChoose());
		gameplay->setAutorun(map->getAutorun());
		scene2.Push(background);
		scene2.Push(map);
		scene2.Push(tool);
		scene2.NextIndex(0);
		scene2.Push(gameplay);
		scene2.Reset();

	}
	else
	{
		isRunning = false;
	}
}

void Window::update()
{
	while (scene2.getNodeIndex() != NULL)
	{
		scene2.getNodeIndex()->getData()->Loop();
		if (scene2.getNodeIndex()->getData()->quit) return;

		
		if (scene2.getNodeIndex()->getData()->Index != -1) {
			scene2.getNodeIndex()->getData()->back = false;
			scene2.NextIndex(scene2.getNodeIndex()->getData()->Index);
		}
		else if (scene2.getNodeIndex()->getData()->back) {
			scene2.PreviousIndex();
			scene2.getNodeIndex()->getData()->Index = -1;
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


