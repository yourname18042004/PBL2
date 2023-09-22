#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H
#include <Load/LoadTexture.h>
#include <SDL.h>
#include<Init/Window.h>


class Menu {
public:
	Menu(SDL_Renderer* renderer);
	~Menu();
	void init();
	void handleEvent();
	void update();
	// Hàm hiện thị đối tượng
	void render();
	// Hàm xóa đối tượng
	void destroy();
	void Loop();
	// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không
	bool Running() { return isRunning; }
private:
	SDL_Renderer* renderer;
	// đối tượng nhận sự kiện
	SDL_Event event;
	// giá trị xet xem cửa sổ đã tắt hay chưa
	bool isRunning;

};




#endif