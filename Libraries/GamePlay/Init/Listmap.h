#ifndef LISTMAP_H
#define LISTMAP_H
#include<Init/Gameplay.h>
#include <Time_vector/Map.h>
#include <cstdio>

class ListMap :public Scene {
	
	int choose;
	bool* UpdateIfAddMap;
	float pos_y_button;
	int NumofLevel;
	bool Autorun;
	int volume;

	int level_default;

	bool setDelete;
public:
	
	ListMap(SDL_Renderer* renderer);
	~ListMap();
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

	int* getChoose() { return &choose; }
	bool* getAutorun() { return &Autorun; }
	int* Numoflevel() { return &NumofLevel; }
	void DeleteMap(int i);
	void setBoolUpdate(bool* set)
	{
		UpdateIfAddMap = set;
	}
	void updateMap();
};
#endif // !LISTMAP_H
