#include "Init.h"
#include "CollisionHandling.h"



Object Butter, Bee;  Fly fly1;
Racket RacKet1;
HandelEvent handelEvent;

Window::Window() {}
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
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	fly1.Init(40, 80, 100, 100, renderer, "Data//fly_200_100.png");
	Butter.Init(40, 80, 100, 100, renderer, "Data//butterfly1_700_100.png");
	Bee.Init(100, 200, 100, 100, renderer, "Data//bee_200_100.png");
	RacKet1.Init(100, 200, 100, 100, renderer, "Data//Racket_200_100.png");
}

void Window::update()
{
	Butter.animation();
	Vector v = Vector{ 0.02, 0 };
	/*if (handelEvent.BUTTON_LEFT)
	{
		float vx = (float)(handelEvent.MOUSE_X - Butter.getPosition().x);
		float vy = (float)(handelEvent.MOUSE_Y - Butter.getPosition().y);

		float r = sqrt(vx * vx + vy * vy);

		v = Vector{ (vx / r) * 6, (vy / r) * 6 };
	}*/
	Butter.update(v);
	if (fly1.status) {
		fly1.animation();
	}
	
	fly1.update(Vector{ 0.005,0.005 });

	Bee.animation();
	Bee.update(Vector{ 0.005,0.005 });

	RacKet1.AnimationRacket(handelEvent);
	RacKet1.update();

	if (Collision(fly1.GetRect(), RacKet1.GetRect()) && handelEvent.BUTTON_LEFT) {
		fly1.status = false;
	}

}

void Window::render()
{
	SDL_RenderClear(renderer);

	Butter.Render(renderer);
	if (fly1.status) {
		fly1.Render(renderer);
	}

	Bee.Render(renderer);
	RacKet1.Render(renderer);

	SDL_RenderPresent(renderer);

}
void Window::destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


