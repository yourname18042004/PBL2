﻿#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Init/Window.h>
#include "Scene.h"


class Gameplay :public Scene {
public:
	Gameplay(SDL_Renderer* renderer);
	~Gameplay();
	virtual void init();

	virtual void Loop();
	// Hàm nhận sự kiện
	virtual void handleEvent();
	// Hàm khởi tạo của sổ
	virtual void update();
	// Hàm hiện thị đối tượng
	virtual void render();
	// Hàm xóa đối tượng
	virtual void destroy();
	// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không
	virtual bool Running() { return isRunning; }
	virtual void SetIsrunning();

};
#endif