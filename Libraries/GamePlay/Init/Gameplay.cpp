#include "Gameplay.h"

//Khai bao
Manager ManagerObject;
Text Textwindow; Text Noti;// thông báo win game
Buttons* buttonBack = nullptr;
Buttons* buttonEnd1 = nullptr;
Buttons* box = nullptr;
FramesObject* background1;
FramesObject* ScoreTab;
char text1[100] = "FLY KILLER SCORE:";


Gameplay::Gameplay(SDL_Renderer* renderer){
	this->renderer = renderer;
}

Gameplay::~Gameplay(){}

void Gameplay::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) {
		ManagerObject.Reset();
		quit = true;
		isRunning = false;
	}
	// Nhận sự kiện
	Event.Handel(event);
}

void Gameplay::init()
{		
	for (int i = 0; i < 8; i++) {
		ManagerObject.Add(new Fly(float((i + 1) * 10), 100.0f, 100.0f, 100.0f, Vector{ float(i + 1),
				float((i + 1) * pow(-1, i)) }, renderer, 100));
	}
	ManagerObject.Add(new Racket(100, 100,100, 100, renderer, &Event));
	Textwindow.init(50, 50, 200, 50, "Data//arial.ttf", 25, { 255,0,0, 255 }, "FLY KILLER SCORE:0", renderer);
	Noti.init(200, 200, 200, 50, "Data//arial.ttf", 25, { 255,0,0, 255 }, "YOUR SCORE: ", renderer);
	buttonBack = new Buttons(620, 360, 100, 100, "Data//ButtonBack_100_100_200_100.png", renderer);
	buttonEnd1 = new Buttons(720, 360, 100, 100, "Data//ButtonEnd_100_100_200_100.png", renderer);
	box = new Buttons(670, 300, 450, 300, "Data//box_300_200_600_200.png", renderer);
	background1 = new FramesObject(new SDL_FRect{ 0, 0, 1440.0f, 720.0f }, "Data//borders_640_320_640_320.png", renderer, false);
	ScoreTab = new FramesObject(new SDL_FRect{ 0, 0, 300.0f, 70.0f }, "Data//ScoreTab_600_100_600_100.png", renderer, false);
	isRunning = true;
}

void Gameplay::Loop() {
	SDL_ShowCursor(false);//ẩn con trỏ chuột
	//vòng lặp gameplay 
	while(isRunning && !quit){
		handleEvent();//nhận sự kiện
		update();
		render();
		//Nếu hết đối tượng trong stack -> thoát vòng lặp gameplay
		if (ManagerObject.IsEmty()) {
			buttonEnd1->Setclick(Event.BUTTON_LEFT);
			buttonBack->Setclick(Event.BUTTON_LEFT);
			if (buttonBack->Getclick()) {
				ManagerObject.Reset();
				for (int i = 0; i < 6; i++) {
					ManagerObject.Add(new Fly(100, 100, 100, 100, Vector{ float(i+1),
					float((i+1) * pow(-1, i)) }, renderer, 100));
				}
			}
				
			if (buttonEnd1->Getclick()){
				ManagerObject.Reset();
				isRunning = false;
			}
		}
	}
}

void Gameplay::update()
{

	Timer::sInit->Update();
	ManagerObject.Update();
	
	char text2[100], text3[100] = "YOUR SCORE:"; // dòng text null tạm thời được copy từ text khai báo bên trên
	strcpy(text2, text1);

	//chuyển biến scorer thành chuỗi rồi nối vào chuỗi đã được copy rồi cập nhật lên màn hình 
	strcat(text2, std::to_string(ManagerObject.scored).c_str());
	strcat(text3, std::to_string(ManagerObject.scored).c_str());
	Textwindow.update(40, 10, 200, 50, "Data//arial.ttf", 25, { 255 ,0 ,0 , 255 }, text2);
	Noti.update(570, 200, 200, 50, "Data//arial.ttf", 25, { 255,0,0, 255 }, text3);
	
}

void Gameplay::render()
{
		//Kẹp giữa dòng đầu 
		SDL_RenderClear(renderer);
		background1->Get_Texture();
		ScoreTab->Get_Texture();
		Textwindow.render();

		if (ManagerObject.IsEmty()) {
			box->Render();
			buttonEnd1->Render();
			buttonBack->Render();
			Noti.render();
		}
		ManagerObject.render(renderer);

		//và cái này
		SDL_RenderPresent(renderer);
	
}
void Gameplay::destroy()
{
	Timer::sInit->release();
	SDL_DestroyRenderer(renderer);
}
void Gameplay::SetIsrunning() {
	isRunning = true;
}
