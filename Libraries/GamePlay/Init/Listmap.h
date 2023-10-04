#ifndef LISTMAP_H
#define LISTMAP_H
#include<Init/Gameplay.h>



class ListMap :public Scene {
	int choose;
	float pos_y_button;
	bool Autorun;
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


};
#endif // !LISTMAP_H
