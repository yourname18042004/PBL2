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

		std::ifstream myfile("Data//Map-dif//Setting.txt");
		myfile.is_open();
		myfile >> checkSound;
		myfile >> volume;
		
		std::cout << volume;
		myfile.close();
		
		mtimer = Timer::Init();//Khởi tạo thời gian
		//khởi tạo menu
		vector_map = Map::Init();


		background = new Menu(renderer);
		background->init(getVolume(), getCheck());
		//khởi tạo gameplay
		gameplay = new Gameplay(renderer);
		gameplay->init(getVolume(), getCheck());

		map = new ListMap(renderer);
		map->init();
		tool = new Tool(renderer);
		tool->init(getVolume());

		gameplay->setChoose(map->getChoose());
		gameplay->setAutorun(map->getAutorun());
		gameplay->setNumofLevel(map->Numoflevel());
		//gameplay->SetMap(map->getMap());
		//std::cout << *getVolume();
		map->setBoolUpdate(tool->getBoolUpdate());
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
	vector_map->release();
	vector_map = NULL;
	std::ofstream myfile("Data//Map-dif//Setting.txt");
	myfile.is_open();
	myfile << checkSound << std::endl;
	myfile << volume;
	myfile.close();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


