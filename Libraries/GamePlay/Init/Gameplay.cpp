#include "Gameplay.h"

//Khai bao
Manager ManagerObject;// biển quản lí các đối tượng

Text ScoreNote;// ghi điểm 
Text Noti;// thông báo win game
Text HightScore;// điểm cao nhất

bool sethit = true;//Lúc Resume thì update huỷ collision 
bool resume = false; //Có resume hay không


Buttons* buttonResume = nullptr; // nút tạm dừng
FramesObject* background1; // viền game
FramesObject* ScoreTab; // thanh viền ghi điểm



std::vector <FramesObject> Heart;// vector chứa các mạng game
std::vector<FramesObject> Star;

Box box1;

ScrollHorizontal* volumeBackground = nullptr;
ScrollHorizontal* volumeSound = nullptr;

int MaxScored = 0;
int heart = 5;


LoadMusic* musicBackground;
LoadMusic* soundPause;


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
		ManagerObject.Reset(); // reset điểm và map mỗi lần tắt cửa sổ
		quit = true; // thoát loop
		isRunning = false; // thoát map
	}
	// Nhận sự kiện
	Event.Handel(event);
}
void Gameplay::init(int *volume, bool *check)
{	
	this->volume = volume;
	this->check = check;
	
	// khởi tạo game 
	timegame = 0;

	std::ifstream myfile("Data//Map-dif//highscore.txt");

	myfile.is_open();
	myfile >> MaxScored;
	
	myfile.close();
	// khởi tạo mạng chơi
	for (int i = 0; i < heart; i++) {
		FramesObject* tmp = new FramesObject(new SDL_FRect{ (i + 1) * 30.0f + 900, 0, 50.0f, 50.0f }, 
			"Data//Picture//heart_100_100_200_100.png", renderer, true);
		Heart.push_back(*tmp);
	}
	for (int i = 0; i < 3; i++) {
		FramesObject* tmp = new FramesObject(new SDL_FRect{ (i + 1) * 45.0f + 600,170,70.0f,70.0f }, "Data//Picture//star_100_100_200_100.png", renderer, true);
		Star.push_back(*tmp);
	}
	
	// thêm vào biến quản lý
	ManagerObject.Add(new Racket(100, 100,120, 120, renderer, &Event));
	ManagerObject.Add(&timegame);

	// khởi tạo các văn bản
	ScoreNote.init(52, 52, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "FLY KILLER SCORE:0", renderer);
	Noti.init(250, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOUR SCORE: ", renderer);
	HightScore.init(250, 300, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOUR HIGH SCORE IS: ", renderer);
	
	//khởi tạo các nút bấm
	buttonResume = new Buttons(1400, 690, 100, 100, "Data//Picture//ButtonResume_100_100_200_100.png", renderer);
	background1 = new FramesObject(new SDL_FRect{ 0, 0, 1440.0f, 720.0f }, "Data//Picture//borders_640_320_640_320.png", renderer, false);
	ScoreTab = new FramesObject(new SDL_FRect{ 0, 0, 300.0f, 70.0f }, "Data//Picture//ScoreTab_600_100_600_100.png", renderer, false);

	box1.init(renderer);

	volumeBackground = new ScrollHorizontal(560, 550, 250, 50, renderer);

	
	/*volumeSound = new ScrollHorizontal(600, 400, 250, 50, renderer);
	volumeSound->setValue(0, 128);
	volumeSound->setValue(128);*/

	// cho chạy map
	isRunning = true;
	back = false;

	musicBackground = new LoadMusic(1);
	musicBackground->addSound("Data//Sound//Nhacgame.mp3");

	soundPause = new LoadMusic(3);
	soundPause->addSound("Data//Sound//Pause.mp3");

}

void Gameplay::Loop() {
	Timer::sInit->reset();
	musicBackground->playSound(-1);
	musicBackground->updateVolume(*(this->volume));
	volumeBackground->setValue(0, 128);
	volumeBackground->setValue(*(this->volume));
	//chọn map
	chooseMap();
	if (*Autorun) SDL_ShowCursor(true);
	else SDL_ShowCursor(false);//ẩn con trỏ chuột

	//vòng lặp gameplay 
	isRunning = true;
	Index = -1;
	while (isRunning && !quit) {
		//std::cout << *choose << " " << *NumberOflevel << std::endl;
		//std::cout << timegame << std::endl;
		handleEvent();//nhận sự kiện
		update();
		render();
		buttonResume->Setclick(Event.BUTTON_LEFT); // cài click cho resume
		// click vào resume
		if (buttonResume->Getclick()) {

			soundPause->playSound(0);
			SDL_ShowCursor(true);
			resume = true; // hiện resume
			if (heart <= 0) resume = false;// nếu thua thì không hiện resume lại
			if (ManagerObject.IsEmty()) resume = false;// nếu thắng thì không hiện resume lại
		}
		// nếu đang hiện resume
		if (resume) {
			
			sethit = false; // không đánh dc đối tượng
			box1.SetClick(Event.BUTTON_LEFT);
			if (box1.getclickEnd()) {
				// reset lại thông số khi bấm nút thoát map
				heart = 5;
				ManagerObject.Reset();
				sethit = true; //cho phép đánh fly
				resume = false;// thoát resume
				back = true; // quay lùi listmap
				isRunning = false; // thoát map
				SDL_ShowCursor(false);

			}
			if (box1.getclickBack()) {
				// trở lại game 
				sethit = true; // cho phép đánh fly
				resume = false; // thoát resume
				SDL_ShowCursor(false);
			}
		}
		// nếu thua
		if (heart <= 0) {
			sethit = false; // không cho phép đánh fly
			SDL_ShowCursor(true);
			box1.SetClick(Event.BUTTON_LEFT);
			if (box1.getclickBack()) {
				//chơi lại game
				timegame = 0;
				sethit = true; // cho phép đánh
				SDL_ShowCursor(false);
				heart = 5;// cài lại số mạng
				ManagerObject.Reset();
				// cài lại map
				chooseMap();
			}
			if (box1.getclickEnd()) {
				//lùi lại listmap
				back = true;
				timegame = 0;
				sethit = true; // cho phép đánh
				SDL_ShowCursor(false);
				heart = 5;
				ManagerObject.Reset();
				isRunning = false; // thoát map
			}
		}
		//thắng game		
		if (ManagerObject.IsEmty()) {
			//SDL_ShowCursor(true);
			if (ManagerObject.scored > 0) {
				
				if (*choose == *NumberOflevel) {
					box1.SetClicklast(Event.BUTTON_LEFT);
				}
				else {
					box1.SetClick(Event.BUTTON_LEFT);
				}
				if (box1.getclickBack()) {
					//reset thông số màn chơi
					timegame = 0;
					ManagerObject.Reset();
					heart = 5;
					chooseMap();
				}
				if (box1.getclickEnd()) {
					//quay lại litsmap
					back = true;
					timegame = 0;
					heart = 5;
					ManagerObject.Reset();
					isRunning = false;
				}
				if (box1.getclickNext() && *choose < *NumberOflevel) {
					//qua màn tiếp theo
					timegame = 0;
					heart = 5;
					(*choose)++;
					chooseMap();
				}
			}
			else {
				sethit = false; // không cho phép đánh fly
				box1.SetClick(Event.BUTTON_LEFT);
				if (box1.getclickBack()) {
					//chơi lại game
					timegame = 0;
					sethit = true; // cho phép đánh
					SDL_ShowCursor(false);
					heart = 5;// cài lại số mạng
					ManagerObject.Reset();
					// cài lại map
					chooseMap();
				}
				if (box1.getclickEnd()) {
					//lùi lại listmap
					back = true;
					timegame = 0;
					sethit = true; // cho phép đánh
					SDL_ShowCursor(false);
					heart = 5;
					ManagerObject.Reset();
					isRunning = false;
				}
			}
		}
	}
	std::ofstream myfile("Data//Map-dif//highscore.txt");
	myfile.is_open();
	myfile << MaxScored;
	myfile.close();
	musicBackground->stopMusic();
}

void Gameplay::update()
{
	
	Timer::sInit->Update();

	if(!resume){
		timegame += Timer::sInit->DeltaTime();
		ManagerObject.Update(sethit, heart, *Autorun, &timegame);
	}
	for (int i = 0; i < heart; i++) {
		Heart[i].UpdateFrames();
	}

	for (int i = 0; i < 3; i++) {
		Star[i].UpdateFrames();
	}
	char text1[50] = "FLY KILLER SCORE:";
	char text2[50], text3[50] = "YOUR SCORE:";

	// dòng text null tạm thời được copy từ text khai báo bên trên
	strcpy(text2, text1);
	char Maxscored[50] = "YOUR HIGH SCORE IS:";

	// cập nhật max điểm
	if (ManagerObject.scored > MaxScored) MaxScored = ManagerObject.scored;

	//chuyển biến scorer thành chuỗi rồi nối vào chuỗi đã được copy rồi cập nhật lên màn hình 
	strcat(text2, std::to_string(ManagerObject.scored).c_str());
	strcat(text3, std::to_string(ManagerObject.scored).c_str());
	strcat(Maxscored, std::to_string(MaxScored).c_str());

	// cập nhật các text có trên màn hình
	ScoreNote.update(40, 13, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255 ,0 ,0 , 255 }, text2);
	Noti.update(620, 300, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, text3);
	HightScore.update(565,350,300,50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, Maxscored);
	if (box1.getclickSoundCheck()) {
		if (*check) *check = false;
		else *check = true;
	}
	volumeBackground->MoveCroll(Event.BUTTON_LEFT_PRESS);
	if (!*check) {
		*volume = 0;
		volumeBackground->setValue(*volume);
		musicBackground->updateVolume(*volume);
	}
	else {
		*volume = volumeBackground->getValue();
		musicBackground->updateVolume(*volume);
	}
	
	soundPause->updateVolume(128);
}

void Gameplay::chooseMap()
{
	ManagerObject.ReadMap(renderer, *choose);
	
}

void Gameplay::render() {

		//Kẹp giữa dòng đầu 
		SDL_RenderClear(renderer);
		background1->Get_Texture();//viền game
		ScoreTab->Get_Texture();// thanh điểm
		ScoreNote.render();// điểm
		buttonResume->Render();// nút resume
		//// in số hình trái tim tượng trưng cho số mạng

		 for (int i = 0; i < heart; i++) {
			Heart[i].Get_Texture();
		 }
		
		// thắng game 
		if (ManagerObject.IsEmty()) {
			if (ManagerObject.scored > 0) {

				if (*choose == *NumberOflevel) {
					
					box1.renderLast(*check);
					//volumeBackground->Render();
					for (int i = 0; i < int(ManagerObject.getPercent() / 33.3f); i++) {
						Star[i].Get_Texture();
					}
					Noti.render();
					HightScore.render();
				
				}
				// render hộp thoại thắng
				else {
					box1.renderWin(*check);
					//volumeBackground->Render();
					for (int i = 0; i < int(ManagerObject.getPercent() / 33.3f); i++) {
						Star[i].Get_Texture();
					}
					
					Noti.render();
					HightScore.render();
				}
			}
			else {
				box1.renderLose(*check);
				//volumeBackground->Render();
				Noti.render();
				HightScore.render();
			}
		}
		//nếu chưa dừng
		if (!resume) {
		   // nếu số mạng chưa thua thì render đối tượng
			if (heart > 0) ManagerObject.render(renderer);
			else {
				// nếu thua thì không render đối tượng mà render hộp thoại thua
				box1.renderLose(*check);
				//volumeBackground->Render();
				Noti.render();
				HightScore.render();
			}
		}
		//nếu dừng
		else {
			box1.resume(*check);
			volumeBackground->Render();
			Noti.render();
			HightScore.render();
		}
		SDL_RenderPresent(renderer);
}
void Gameplay::destroy()
{
	
	Timer::sInit->release();// xoá thời gian
	SDL_DestroyRenderer(renderer);
}

