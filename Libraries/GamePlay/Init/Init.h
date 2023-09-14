#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Time_vector/Vector.h>
#include <Load/LoadTexture.h>
#include <Object/Object.h>
#include <Object/Fly.h>
#include <Manager/HandelEvent.h>
#include <Object/Racket.h>
#include <Vacham/CollisionHandling.h>
#include <Time_vector/Timer.h>
#include <cstdlib>
#include "MenuAndBackground.h"
#include <Manager/ManagerObject.h>
#include <Load/LoadMusic.h>
#include <Load/LoadDocument.h>
#include <Object/ObjectText.h>
#include "MenuAndBackground.h"
#include <Linklist/Linklist.h>
#include <cstring>
#include <sstream>
#include <string.h>

// đối tượng nhận và xử lý tất cả các đối tượng sự kiện khác

class Window
{
public:
	Window();
	~Window();
	// Hàm nhận sự kiện
	void handleEvent();
	// Hàm khởi tạo của sổ
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	// Hàm update đối tượng
	void update();
	// Hàm hiện thị đối tượng
	void render();
	// Hàm xóa đối tượng
	void destroy();
	// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không
	bool Running() { return isRunning; }
private:
	Timer* mtimer;
	SDL_Window* window;
	SDL_Renderer* renderer;
	// đối tượng nhận sự kiện
	SDL_Event event;
	// giá trị xet xem cửa sổ đã tắt hay chưa
	bool isRunning;

};

#endif // INIT_WINDOW_H