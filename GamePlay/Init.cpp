#include "Init.h"
#include "ManagerObject.h"
#include "LoadMusic.h"
#include "LoadDocument.h"
#include "ObjectText.h"
#include "MenuAndBackground.h"
#include <cstring>
#include <sstream>
#include <string.h>

Manager ManagerObject;
Racket* RacKet1 = nullptr;
HandelEvent handelEvent;
LoadMusic Sound2, Sound3;

Text Textwindow;Text Noti;// thông báo win game

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
	}
	else
	{
		isRunning = false;
	}
	//Them doi tuong vao vector Object
	for (int i = 0; i <4; i++) {
		//random độ lớn của Object
		int size = rand() % 50 + 50;

		Fly* Fly1 = (Fly*)new Fly::Object(100 * (rand() % 5), 100 * (rand() % 5), size, size, 
			renderer,
			"Data//FlyUpdate_400_100.png");
		Fly1->status = true;
		ManagerObject.Add(*Fly1);

	}
	//Tao con tro va quan ly
	RacKet1 = (Racket*)new Racket::Object(100, 200, 75, 75, renderer, "Data//Racket_200_100.png");
	RacKet1->SetTheAnimation();
	ManagerObject.Add(RacKet1);
	ManagerObject.Add(&handelEvent);
	// khởi tạo các thông báo in trên cửa sổ
	Textwindow.init(10,0,200, 50, "Data//arial.ttf", 25, { 255,0,0, 255}, "FLY KILLER SCORE:0", renderer);
	Noti.init(720, 360, 200, 50, "Data//arial.ttf", 50, { 255,0,0, 255 }, "YOU WIN", renderer);
	// âm thanh game
	Sound2.addSound("Data//congra.wav");
	//Sound2.playSound("Data//congra.wav");
	Sound3.addSound("Data//level.wav");
	//Sound3.playSound("Data//level.wav");

	
}

void Window::update()
{	
	RacKet1->AnimationRacket(handelEvent);
	RacKet1->UpdatePositionOfMouse();
	ManagerObject.UpdatePositionAndVector();
	char text1[100]; // dòng text null tạm thời được copy từ text khai báo bên trên
	strcpy(text1, text);
	//chuyển biến scorer thành chuỗi rồi nối vào chuỗi đã được copy rồi cập nhật lên màn hình 
	strcat(text1, std::to_string(ManagerObject.scored).c_str());
	Textwindow.update(10, 0, 200, 50, "Data//arial.ttf", 25, { 255 ,0 ,0 , 255 }, text1, renderer); 

}

void Window::render()
{	
	SDL_RenderClear(renderer);

	
	ManagerObject.render(renderer);
	RacKet1->Render(renderer);
	Textwindow.render(renderer);

	if (ManagerObject.getSize() == 0) {
		Noti.render(renderer);
		//Sound3.playSound("Data//level.wav");

	}

	//Hết đối tượng trên màn hình -> in ra thông báo chiến thắng

	SDL_RenderPresent(renderer);
}
void Window::destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


