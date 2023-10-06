﻿#include "Listmap.h"

Buttons* level1 = nullptr;
Buttons* level2 = nullptr;
Buttons* level3 = nullptr;
Buttons* level4 = nullptr;
Buttons* level5 = nullptr;
Buttons* level6 = nullptr;
Buttons* level7 = nullptr;
Buttons* level8 = nullptr;
Buttons* level9 = nullptr;
Buttons* level10 = nullptr;

Buttons* yes = nullptr;
Buttons* no = nullptr;
Buttons* backMenu = nullptr;
FramesObject* background2 = nullptr;
FramesObject* Box = nullptr;

FramesObject* RacketChoose = nullptr;
float Racketpos = 500;

Text textAutorun;


ListMap::ListMap(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
ListMap::~ListMap() { }

void ListMap::init() {
	background2 = new FramesObject(new SDL_FRect{ 0, 0, 1440.0f, 720.0f },
		"Data//Picture//ListMap_640_320_640_320.png", renderer, false);
	level1 = new Buttons(980, 320, 280, 85, "Data//Picture//Level1_350_100_700_100.png", renderer);
	level2 = new Buttons(980, 420, 280, 85, "Data//Picture//Level2_350_100_700_100.png", renderer);
	level3 = new Buttons(980, 420, 280, 85, "Data//Picture//Level3_350_100_700_100.png", renderer);
	level4 = new Buttons(980, 420, 280, 85, "Data//Picture//Level4_350_100_700_100.png", renderer);
	level5 = new Buttons(980, 420, 280, 85, "Data//Picture//Level5_350_100_700_100.png", renderer);
	/*level6 = new Buttons(980, 420, 280, 85, "Data//Picture//Level2_350_100_700_100.png", renderer);
	level7 = new Buttons(980, 420, 280, 85, "Data//Picture//Level2_350_100_700_100.png", renderer);
	level8 = new Buttons(980, 420, 280, 85, "Data//Picture//Level2_350_100_700_100.png", renderer);
	level9 = new Buttons(980, 420, 280, 85, "Data//Picture//Level2_350_100_700_100.png", renderer);
	level10 = new Buttons(980, 420, 280, 85, "Data//Picture//Level2_350_100_700_100.png", renderer);*/
	yes = new Buttons(360, 550, 150, 70, "Data//Picture//Yes_350_100_700_100.png", renderer);
	no = new Buttons(540, 550, 150, 70, "Data//Picture//No_350_100_700_100.png", renderer);
	Box = new FramesObject(new SDL_FRect{ 230, 400, 450.0f, 300.0f }, "Data//Picture//Box_300_200_600_200.png", renderer, false);
	
	backMenu = new Buttons(1390, 670, 150, 150, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);

	textAutorun.init(330,450,250,50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "AUTORUN?", renderer);
	// khởi tạo các biến quản lý 
	back = false; // đi lùi
	Index = -1;
	isRunning = true;
	Autorun = false;
	pos_y_button = 50;
}
void ListMap::Loop() {
	isRunning = true;
	while (isRunning && !quit) {
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();
	}
}
// Hàm nhận sự kiện
void ListMap::handleEvent() {
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) quit = true;

	// Nhận sự kiện
	Event.Handel(event);
}
// Hàm khởi tạo của sổ
void ListMap::update() {
	RacketChoose = new FramesObject(new SDL_FRect{ Racketpos, 570, 100.0, 100.0 }, "Data//Picture//Racketchoose_100_100_100_100.png", renderer, false);
	if (Event.crossUp && pos_y_button + 10 * 100 > 720) pos_y_button -= 30.0f;
	if (Event.crossDown && pos_y_button < 50) pos_y_button += 30.0f;
	//std::cout << pos_y_button << std::endl;
	level1->setDest(level1->getDest().x, pos_y_button);
	level2->setDest(level1->getDest().x, pos_y_button + 100);
	level3->setDest(level1->getDest().x, pos_y_button + 200);
	level4->setDest(level1->getDest().x, pos_y_button + 300);
	level5->setDest(level1->getDest().x, pos_y_button + 400);
	/*level6->setDest(level1->getDest().x, pos_y_button + 500);
	level7->setDest(level1->getDest().x, pos_y_button + 600);
	level8->setDest(level1->getDest().x, pos_y_button + 700);
	level9->setDest(level1->getDest().x, pos_y_button + 800);
	level10->setDest(level1->getDest().x, pos_y_button + 900);*/

	level1->Setclick(Event.BUTTON_LEFT);
	level2->Setclick(Event.BUTTON_LEFT);
	level3->Setclick(Event.BUTTON_LEFT);
	level4->Setclick(Event.BUTTON_LEFT);
	level5->Setclick(Event.BUTTON_LEFT);
	/*level6->Setclick(Event.BUTTON_LEFT);
	level7->Setclick(Event.BUTTON_LEFT);
	level8->Setclick(Event.BUTTON_LEFT);
	level9->Setclick(Event.BUTTON_LEFT);
	level10->Setclick(Event.BUTTON_LEFT);*/

	yes->Setclick(Event.BUTTON_LEFT);
	no->Setclick(Event.BUTTON_LEFT);
	backMenu->Setclick(Event.BUTTON_LEFT);
	if (level1->Getclick()) {
		choose = 1;
		Index = 0;
		isRunning = false;
		
	}
	if (level2->Getclick()) {
		Index = 0;
		choose = 2;
		isRunning = false;
	}
	if (backMenu->Getclick()) {
		back = true;
		isRunning = false;

	}
	if (no->Getclick()) {
		Autorun = false;
		Racketpos = 500; 
	}
	if (yes->Getclick()) {
		Autorun = true;
		Racketpos = 300;
	}

}
// Hàm hiện thị đối tượng
void ListMap::render() {
	SDL_RenderClear(renderer);

	background2->Get_Texture();
	level1->Render();
	level2->Render();
	level3->Render();
	level4->Render();
	level5->Render();
	/*level6->Render();
	level7->Render();
	level8->Render();
	level9->Render();
	level10->Render();*/
	
	backMenu->Render();
	Box->Get_Texture();
	yes->Render();
	no->Render();
	RacketChoose->Get_Texture();
	textAutorun.render();
	SDL_RenderPresent(renderer);
}
// Hàm xóa đối tượng
void ListMap::destroy() {

}
// Hàm trả về giá trị để xét xem chương trình có tiếp tục chạy nữa hay không


