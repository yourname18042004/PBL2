#include <SDL.h>
#include <SDL_image.h>
#include <Init/Window.h>


#undef main

// khởi tạo đối tượng
Window* window = nullptr;
// chiều rộng chiểu cao của của sổ
const int WIDTH_SCREEN = 1440;
const int HEIGHT_SCREEN = 720;

int main(int argc, char* argv[])
{
	// cấp phát bộ nhớ
	window = new Window();

	// tạo của sổ và render
	window->init("Thanh - Giap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_SCREEN, HEIGHT_SCREEN, false);

		// Cap nhat doi tuong
	window->update();

	// xóa bộ nhớ
	window->destroy();

	return 0;
}