#ifndef SCENE_H
#define SCENE_H
class Scene {
protected:
	const int FPS_rate = 120;
	bool isRunning;
	SDL_Renderer* renderer;
	// đối tượng nhận sự kiện
	SDL_Event event;
	HandelEvent Event;


public:
	bool quit;
	virtual void Loop() = 0;
	// Hàm nhận sự kiện
	virtual void handleEvent() = 0;
	// Hàm khởi tạo của sổ
	virtual void update() = 0;
	// Hàm hiện thị đối tượng
	virtual void render() = 0;
	// Hàm xóa đối tượng
	virtual void destroy() = 0;
	// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không
	virtual bool Running() { return isRunning; }
	virtual void SetIsrunning() = 0;
	virtual void init() = 0;
};




#endif