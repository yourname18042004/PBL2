#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Init/Window.h>
class Gameplay {
public:
	Gameplay(SDL_Renderer* renderer);
	~Gameplay();
	void init(int xpos, int ypos, int width, int height, bool fullscreen);

	void Loop();
	// Hàm nhận sự kiện
	void handleEvent();
	// Hàm khởi tạo của sổ
	void update();
	// Hàm hiện thị đối tượng
	void render();
	// Hàm xóa đối tượng
	void destroy();
	// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không
	bool Running() { return isRunning; }

private:

	HandelEvent Event;
	const int FPS_rate = 120;
	SDL_Renderer* renderer;
	// đối tượng nhận sự kiện
	SDL_Event event;
	// giá trị xet xem cửa sổ đã tắt hay chưa
	bool isRunning;
};





#endif