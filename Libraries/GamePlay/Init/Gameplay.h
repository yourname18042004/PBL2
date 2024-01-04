#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Init/Window.h>
#include "Scene.h"
#include <vector>
#include <Manager/Box.h>
#include <ScrollBar.h>

class Gameplay :public Scene {
private: 
	float timegame;
	int* choose;
	bool* Autorun;
	int* NumberOflevel;
	int *volume;
	bool* check;

public:
	Gameplay(SDL_Renderer* renderer);
	~Gameplay();

	void init(int *volume, bool *check);

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

	virtual void init() {}
	void setChoose(int* choose)
	{
		this->choose = choose;
	}
	void setAutorun(bool* Autorun) {
		this->Autorun = Autorun;
	}
	void setNumofLevel(int* NumofLevel) {
		this->NumberOflevel = NumofLevel;
	}
	
	void chooseMap();

};
#endif