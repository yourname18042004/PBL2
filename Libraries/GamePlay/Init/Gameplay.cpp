#include "Gameplay.h"
int MaxScored = 0;

//Khai bao
Manager ManagerObject;
Text Textwindow; 
Text Noti;// thông báo win game
Text HightScore;

bool set = true;//Lúc Resume thì update huỷ collision 
bool resume = false;//Có resume hay không

Buttons* buttonBack = nullptr;
Buttons* buttonEnd1 = nullptr;
Buttons* buttonResume = nullptr;
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
	for (int i = 0; i < 2; i++) {
		ManagerObject.Add(new Fly(float((i + 1) * 10), 100.0f, 100.0f, 100.0f, Vector{ float(i + 1),
				float((i + 1) * pow(-1, i)) }, renderer, 100));
	}
	ManagerObject.Add(new Racket(100, 100,100, 100, renderer, &Event));
	Textwindow.init(52, 52, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "FLY KILLER SCORE:0", renderer);
	Noti.init(250, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOUR SCORE: ", renderer);
	HightScore.init(250, 300, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOUR HIGHT SCORE IS: ", renderer);


	buttonBack = new Buttons(670, 410, 100, 100, "Data//ButtonBack_100_100_200_100.png", renderer);
	buttonEnd1 = new Buttons(770, 410, 100, 100, "Data//ButtonEnd_100_100_200_100.png", renderer);
	buttonResume = new Buttons(1400, 690, 100, 100, "Data//ButtonResume_100_100_200_100.png", renderer);


	box = new Buttons(720, 350, 450, 300, "Data//box_300_200_600_200.png", renderer);

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
		buttonResume->Setclick(Event.BUTTON_LEFT);
		if (buttonResume->Getclick()) {
			SDL_ShowCursor(true);
			resume = true;
		}
		if (resume) {
			set = false;
			buttonEnd1->Setclick(Event.BUTTON_LEFT);
			buttonBack->Setclick(Event.BUTTON_LEFT);
			if (buttonEnd1->Getclick()) {
				ManagerObject.Reset();
				set = true;
				resume = false;
				isRunning = false;
				SDL_ShowCursor(false);
			}
			if (buttonBack->Getclick()) {
				set = true;
				resume = false;
				SDL_ShowCursor(false);
			}

		}
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

	ManagerObject.Update(set);
	
	char text2[100], text3[100] = "YOUR SCORE:";
	// dòng text null tạm thời được copy từ text khai báo bên trên
	strcpy(text2, text1);
	char Maxscored[100] = "YOUR HIGHT SCORE IS:";
	if (ManagerObject.scored > MaxScored) MaxScored = ManagerObject.scored;
	//chuyển biến scorer thành chuỗi rồi nối vào chuỗi đã được copy rồi cập nhật lên màn hình 
	strcat(text2, std::to_string(ManagerObject.scored).c_str());
	strcat(text3, std::to_string(ManagerObject.scored).c_str());
	strcat(Maxscored, std::to_string(MaxScored).c_str());

	Textwindow.update(40, 13, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255 ,0 ,0 , 255 }, text2);
	Noti.update(620, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, text3);
	HightScore.update(565,300,300,50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, Maxscored);
}

void Gameplay::render()
{
		//Kẹp giữa dòng đầu 
		SDL_RenderClear(renderer);

		background1->Get_Texture();
		ScoreTab->Get_Texture();
		Textwindow.render();
		buttonResume->Render();
		
		
		if (ManagerObject.IsEmty()) {

			box->Render();
			buttonEnd1->Render();
			buttonBack->Render();
			Noti.render();
			HightScore.render();

		}
		if (!resume) {

			ManagerObject.render(renderer);

		}
		else{
			
			box->Render();
			buttonEnd1->Render();
			buttonBack->Render();
			Noti.render();
			HightScore.render();

		}
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
