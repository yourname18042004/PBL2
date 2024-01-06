#include "ToolEdit.h"

Buttons* toolback = nullptr;
Buttons* add = nullptr; // button them doi tuong ruoi
Buttons* stop = nullptr; // button dung thoi gian chay
Buttons* start = nullptr; // button bat dau chay thoi gian 
Buttons* outFile = nullptr; // button xuat file

LoadMusic* background = nullptr;

// thanh cuon
ScrollHorizontal* Timing = nullptr; // thoi gian chay 
ScrollHorizontal* TimingFly = nullptr; // thoi gian bat dau chay cua Fly
ScrollHorizontal* Time_Fly_Pause = nullptr; // thoi gian ruoi dung yen
ScrollHorizontal* Speed = nullptr; // toc do cua ruoi
ScrollHorizontal* Score = nullptr; // diem

// hien thi noi dung
Content Text_Timing;
Content Text_Time_Fly_Pause;
Content Text_Speed;
Content Text_Score;

bool set = 0;
float timelimit = -1;
float timelimit1 = -1;
float timelimit2 = -1;

Table* table = nullptr;

Frame* box;

FramesObject* Thatbai = nullptr;
FramesObject* Thanhcong = nullptr;
FramesObject* Trungten = nullptr;
FramesObject* editArea = nullptr;

std::vector <FlyEdit*> flys;

std::string getName1(std::string s) {
	std::string tmp;
	for (int i = 15; i < s.size(); ++i) {
		if (s[i] == '.') break;
		tmp.push_back(s[i]);
	}
	return tmp;
}

Tool::Tool(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
Tool::~Tool() {

}
void Tool::init(int *volume) {
	this->volume = volume;
	// back ground
	editArea = new FramesObject(new SDL_FRect{ 0, 0, 1440 * 0.8f, 720 * 0.8f }, "Data/Edit/BackGround_120_60_120_60.png", renderer, false);
	Thatbai = new FramesObject(new SDL_FRect{ 400, 200, 640, 320 }, "Data/Edit/Trongten_640_320_640_320.png", renderer, false);
	Thanhcong = new FramesObject(new SDL_FRect{ 400, 200, 640, 320 }, "Data/Edit/Thanhcong_640_320_640_320.png", renderer, false);
	Trungten = new FramesObject(new SDL_FRect{ 400, 200, 640, 320 }, "Data/Edit/Trungten_640_320_640_320.png", renderer, false);

	// nut 
	toolback = new Buttons(1390, 50, 50, 50, "Data//Edit//Back_50_50_100_50.png", renderer);
	add		= new Buttons(1300, 50, 50, 50, "Data//Edit//Add_50_50_100_50.png", renderer);
	stop	= new Buttons(680, 600, 50, 50, "Data//Edit//Pause_50_50_100_50.png", renderer);
	start   = new Buttons(680, 600, 50, 50, "Data//Edit//Start_50_50_100_50.png", renderer);
	outFile = new Buttons(1210, 50, 50, 50, "Data//Edit//Down_50_50_100_50.png", renderer);;

	//thanh truot 
	Timing				= new ScrollHorizontal(100, 600, 1060, 80, renderer);
	TimingFly			= new ScrollHorizontal(100, 650, 1060, 80, renderer);
	Time_Fly_Pause		= new ScrollHorizontal(1200, 100, 200, 50, renderer);
	Speed				= new ScrollHorizontal(1200, 180, 200, 50, renderer);
	Score				= new ScrollHorizontal(1200, 260, 200, 50, renderer);
	
	// gan gia tri nhỏ nhất và giá trị lớn nhất cho thanh trượt
	Timing->setValue(0, 100);
	TimingFly->setValue(0, 100);
	Time_Fly_Pause->setValue(0.1f, 5);
	Speed->setValue(10, 10000);
	Score->setValue(100, 1000);

	// hiển thị nội dung
	Text_Timing.init(50, 600, 20, 20, "Data//Galhau_Regular.ttf", 25, { 0, 0,0, 255 }, "0", renderer);
	Text_Time_Fly_Pause.init(1150, 100, 20, 20, "Data//Galhau_Regular.ttf", 25, { 0, 0,0, 255 }, "0", renderer);
	Text_Speed.init(1150, 150, 400, 20, "Data//Galhau_Regular.ttf", 25, { 0,0,0, 255 }, "0", renderer);
	Text_Score.init(1150, 200, 20, 20, "Data//Galhau_Regular.ttf", 25, { 0,0,0, 255 }, "0", renderer);

	box = new Frame(200, 100, 1000, 400, renderer);

	// ruoi
	flys.push_back(new FlyEdit(100, 100, 70, 70, 200, 200, 0, 5, 100, renderer, 100, &TimeEdit, &Event));
	
	fly = flys[0]; fly->Pick();

	table = new Table(1185, 305, 208, 416, &flys, &fly, renderer, &Event);

	background = new LoadMusic(7);
	background->addSound("Data//Sound//tooledit.mp3");
	

	// điều kiện thoát và nhảy
	isRunning = true;
	Index = -1;
	back = false;

	TimeEdit = 0;
	TimeEditRun = false;
	UpdateIfAddMap = false;
}
void Tool::docTen() {
	std::string path;

	char pat[100];

	int count;

	std::ifstream myfile("Data//Map-dif//ManagerMap.txt");
	myfile.is_open();
	myfile >> count;
	std::string tmp;
	getline(myfile, tmp);
	for (int i = 0; i < count; i++) {
		std::string tmp;
		getline(myfile, tmp);
		path = tmp;
		sname.push_back(path);
	}

	myfile.close();

	for (int i = 0; i < sname.size(); ++i) {
		sname[i] = getName1(sname[i]);
	}
}
void Tool::handleEvent()
{
	// Nhận sự kiện từ của sổ
	SDL_PollEvent(&event);
	// Nếu của sổ bị đóng thì trả giá trị của isRunning false để dừng chương trình
	if (event.type == SDL_QUIT) quit = true;

	// Nhận sự kiện
	Event.Handel(event);
}

void Tool::update() 
{
	if (!set) {
		UpdateButton();

		table->update();

		UpdateScroll();
		UpdateContent();
		UpdateFly();
		
	}
	else
	{
		UpdateFrame();
	}
	
	if (toolback->Getclick()) 
	{
		isRunning = false;
		back = true;
	}
	if (set) {
		box->SetClick(Event.BUTTON_LEFT);
	}
	background->updateVolume(*(this->volume));

	
}


void Tool::render() 
{
	SDL_RenderClear(renderer);
	editArea->Get_Texture();

	RenderButton();
	RenderScroll();
	RenderContent();
	RenderFly();
	
	table->render();
	
	RenderFrame();

	SDL_RenderPresent(renderer);
}
void Tool::destroy() 
{
	
}
void Tool::Loop() 
{
	Timer::sInit->reset();
	isRunning = true;
	background->playSound(-1);
	docTen();
	while (isRunning && !quit) 
	{
		Timer::sInit->Update();
		SDL_ShowCursor(true);
		handleEvent();
		update();
		render();
	}
	background->stopMusic();
}

void Tool::UpdateButton() 
{
	toolback->Setclick(Event.BUTTON_LEFT);
	add->Setclick(Event.BUTTON_LEFT);
	stop->Setclick(Event.BUTTON_LEFT);
	start->Setclick(Event.BUTTON_LEFT);
	outFile->Setclick(Event.BUTTON_LEFT);

	if (stop->Getclick())
	{
		TimeEditRun = !TimeEditRun;
	}

	if (add->Getclick())
	{
		flys.push_back(new FlyEdit(300, 300, 70, 70, 500, 300, TimeEdit, 5, 100, renderer, 100, &TimeEdit, &Event));
		table->addButton(*(flys.end() - 1));
	}

	// xuat file
	if (outFile->Getclick())
	{
		set = 1;
		
	}
}
void Tool::UpdateScroll()
{
	Timing->MoveCroll(Event.BUTTON_LEFT_PRESS);
	TimingFly->MoveCroll(Event.BUTTON_LEFT_PRESS);

	// neu thoi gian Edit chay thi thanh cuon cung chay
	if (TimeEditRun)
	{
		TimeEdit += Timer::sInit->DeltaTime();
		Timing->setValue(TimeEdit);
	}
	// neu thanh cuon chay thi thoi gian thay doi thanh cuon
	else if (!TimeEditRun) TimeEdit = Timing->getValue();

}
void Tool::UpdateContent()
{
	Text_Timing.update(200, 600, 20, 20, "Data//Galhau_Regular.ttf", 25, { 0, 0,0, 255 }, toClock(Timing->getValue()).c_str());
	Text_Time_Fly_Pause.update(1160, 85, 20, 20, "Data//Galhau_Regular.ttf", 25, { 0, 0,0, 255 }, toStr(Time_Fly_Pause->getValue(), "Time: ").c_str());
	Text_Speed.update(1160, 165, 400, 20, "Data//Galhau_Regular.ttf", 25, { 0,0,0, 255 }, toStr(Speed->getValue(), "Speed: ").c_str());
	Text_Score.update(1160, 245, 20, 20, "Data//Galhau_Regular.ttf", 25, { 0,0,0, 255 }, toStr(Score->getValue(), "Score: ").c_str());
}
void Tool::UpdateFly()
{
	// neu mot con ruoi dc chon thi cac gia tri cua thanh cuon pause, speed, score, thoi gian bat dau chay
	// se duoc cap nhat dung voi gia tri hien tai cua ruoi
	if (CollisionButton(fly->getAreaFly()) && Event.BUTTON_LEFT)
	{
		Time_Fly_Pause->setValue(fly->getTimePause());
		Speed->setValue(fly->getSpeed());
		Score->setValue(fly->getScore());
		TimingFly->setValue(fly->getTimeStart());
	}

	// neu cac thanh cuon thanh di chuyen thi gia tri tuong ung cua moi con ruoi do cung thay doi
	if (Time_Fly_Pause->MoveCroll(Event.BUTTON_LEFT_PRESS))
	{
		fly->updateTimePause(Time_Fly_Pause->getValue());
	}
	if (Speed->MoveCroll(Event.BUTTON_LEFT_PRESS))
	{
		fly->updateSpeed(Speed->getValue());
	}
	if (Score->MoveCroll(Event.BUTTON_LEFT_PRESS))
	{
		fly->updateScore(Score->getValue());
	}
	if (TimingFly->MoveCroll(Event.BUTTON_LEFT_PRESS))
	{
		fly->updateTimeStart(TimingFly->getValue());
	}

	// update fly
	for(int i = 0; i < flys.size(); ++i)
		flys[i]->move();
}
void Tool::UpdateFrame()
{
	box->Update(Event);
	bool checkTrung = false;
	for (int i = 0; i < sname.size(); ++i) {
		if (sname[i] == box->getContent()) {
			checkTrung = true;
			break;
		}
	}
	if (box->getclickOK() && box->getContent().size() != 0) {
		if (checkTrung) timelimit2 = 10;
		else {
			FileOut(&flys, box->getContent());
			UpdateIfAddMap = true;
			timelimit1 = 10;
			set = 0;
			//docTen();
		}
	}
	else if (box->getclickOK() && box->getContent().size() == 0) {
		timelimit = 10;
	}
	if (box->getclickCancel()) {
		set = 0;
	}
}


void Tool::RenderButton()
{
	toolback->Render();
	add->Render();
	outFile->Render();
	if (!TimeEditRun) stop->Render();
	else start->Render();

}
void Tool::RenderScroll()
{
	Timing->Render();
	TimingFly->Render();
	Time_Fly_Pause->Render();
	Speed->Render();
	Score->Render();
}
void Tool::RenderContent()
{
	Text_Timing.render();
	Text_Time_Fly_Pause.render();
	Text_Speed.render();
	Text_Score.render();
}
void Tool::RenderFly()
{
	for (int i = 0; i < flys.size(); ++i)
		flys[i]->Render();
}
void Tool::RenderFrame()
{
	if(set)
	box->Render();

	if (timelimit >=0 ) {
		Thatbai->Get_Texture();
		timelimit -= 0.01;
	}
	if (timelimit1 >= 0) {
		Thanhcong->Get_Texture();
		timelimit1 -= 0.01;
	}
	if (timelimit2 >= 0) {
		Trungten->Get_Texture();
		timelimit2 -= 0.01;
	}
}