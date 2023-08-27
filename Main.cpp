#include <SDL.h>
#include <SDL_image.h>
#include "GamePlay/Init.h"
#undef main

// khởi tạo đối tượng
Window* window = nullptr;

// chiều rộng chiểu cao của của sổ
const int WIDTH_SCREEN = 800;
const int HEIGHT_SCREEN = 600;

int main(int argc, char* argv[])
{
	// cấp phát bộ nhớ
	window = new Window();

	// tạo của sổ và render
	window->init("Thanh - Giap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_SCREEN, HEIGHT_SCREEN, false);

	while (window->Running())
	{
		// Nhận sự kiện
		window->handleEvent();

		// Cap nhat doi tuong
		window->update();

		// hiển thị đối tượng
		window->render();

	}

	// xóa bộ nhớ
	window->destroy();
	return 0;
}