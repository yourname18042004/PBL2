#ifndef TOOL_EDIT_H
#define TOOL_EDIT_H
#include <Load/LoadTexture.h>
#include <SDL.h>
#include <Init/Window.h>
#include <ScrollBar.h>
#include <Table.h>
#include <Content.h>
#include "Scene.h"
#include <sstream>
#include <string>
#include <FlyEdit.h>
#include <FileOut.h>
#include <TexBox.h>
#include <Frame.h>


class Tool :public Scene {

private:
	float TimeEdit; // thoi gian game chay trong edit 
	bool TimeEditRun; // thoi gian edit chay hay ko
	bool UpdateIfAddMap;
	int* volume;
	FlyEdit* fly = nullptr;
	std::vector<std::string> sname;

	void UpdateButton(); // update button
	void UpdateScroll(); // update thanh cuon
	void UpdateContent(); // update hien thi chu
	void UpdateFly(); // update fly
	void UpdateFrame();

	void RenderButton(); // render button
	void RenderScroll(); // render thanh cuon
	void RenderContent(); // render hien thi chu
	void RenderFly(); // render fly
	void RenderFrame();
public:
	Tool(SDL_Renderer* renderer);
	~Tool();
	void init(int *volume);
	virtual void init(){}
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
	void docTen();
	bool* getBoolUpdate() { return &UpdateIfAddMap; }

};

#endif