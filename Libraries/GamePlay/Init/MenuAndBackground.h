#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H
#include <Load/LoadTexture.h>
#include <SDL.h>
#include<Init/Window.h>
#include "Scene.h"
#include "Load/LoadDocument.h"
#include "Load/LoadMusic.h"

class Menu:public Scene {
	int *volume;
	bool* check;
	
public:
	Menu(SDL_Renderer* renderer);
	~Menu();
	void init(int *volume, bool *check);

	virtual void Loop();
	// Hàm nhận sự kiện
	virtual void handleEvent();
	// Hàm khởi tạo của sổ
	virtual void update();
	// Hàm hiện thị đối tượng
	virtual void render() ;
	// Hàm xóa đối tượng
	virtual void destroy();
	// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không
	virtual bool Running() { return isRunning; }
	virtual void init() {} 
};

#endif