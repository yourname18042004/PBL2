#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "LoadTexture.h"

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
	SDL_Window* window;
	SDL_Renderer* renderer;
	// đối tượng nhận sự kiện
	SDL_Event event;
	// giá trị xet xem cửa sổ đã tắt hay chưa
	bool isRunning;
	
	SDL_Texture* ruoi;
	SDL_Texture* ruoi1;
	SDL_Texture* ruoi2;

	int t = 0;
};

#endif // INIT_WINDOW_H