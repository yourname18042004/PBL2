#include "Gameplay.h"

//Khai bao
Manager ManagerObject;// biển quản lí các đối tượng

Text ScoreNote;// ghi điểm 
Text Noti;// thông báo win game
Text HightScore;// điểm cao nhất
Text ifWin; // thông báo nếu thắng
Text ifLose; // thông báo nếu thua
Text ifResume; // thông báo nếu dừng

bool sethit = true;//Lúc Resume thì update huỷ collision 
bool resume = false; //Có resume hay không

Buttons* buttonBack = nullptr;// nút quay lui
Buttons* buttonEnd1 = nullptr; // nút kết thúc
Buttons* buttonResume = nullptr; // nút tạm dừng
Buttons* buttonNext = nullptr; // nút qua màn tiếp
Buttons* box = nullptr; // hộp thoại


FramesObject* background1; // viền game
FramesObject* ScoreTab; // thanh viền ghi điểm
std::vector <FramesObject> Heart;// vector chứa các mạng game

LoadMusic MixBackGround;

int MaxScored = 0;
int heart = 5;


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

void Gameplay::init()
{	
	// khởi tạo game 
	timegame = 0;
	
	// khởi tạo mạng chơi
	for (int i = 0; i < heart; i++) {
		FramesObject* tmp = new FramesObject(new SDL_FRect{ (i + 1) * 30.0f + 900, 0, 50.0f, 50.0f }, 
			"Data//Picture//heart_100_100_200_100.png", renderer, true);
		Heart.push_back(*tmp);
	}

	// thêm vào biến quản lý
	ManagerObject.Add(new Racket(100, 100,120, 120, renderer, &Event));
	ManagerObject.Add(&timegame);

	// khởi tạo các văn bản
	ScoreNote.init(52, 52, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "FLY KILLER SCORE:0", renderer);
	Noti.init(250, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOUR SCORE: ", renderer);
	HightScore.init(250, 300, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOUR HIGHT SCORE IS: ", renderer);
	ifWin.init(630, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOU WIN! ", renderer);
	ifLose.init(620, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOU LOSE!", renderer);
	ifResume.init(620, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "Resume", renderer);

	//khởi tạo các nút bấm
	buttonBack = new Buttons(630, 450, 100, 100, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
	buttonEnd1 = new Buttons(730, 450, 100, 100, "Data//Picture//ButtonEnd_100_100_200_100.png", renderer);
	buttonResume = new Buttons(1400, 690, 100, 100, "Data//Picture//ButtonResume_100_100_200_100.png", renderer);
	buttonNext = new Buttons(830, 450, 100, 100, "Data//Picture//ButtonNext_100_100_200_100.png", renderer);

	// khởi tạo hộp thoại
	box = new Buttons(720, 350, 450, 300, "Data//Picture//box_300_200_600_200.png", renderer);

	// khởi tạo viền map và thanh viền điểm
	background1 = new FramesObject(new SDL_FRect{ 0, 0, 1440.0f, 720.0f }, "Data//Picture//borders_640_320_640_320.png", renderer, false);
	ScoreTab = new FramesObject(new SDL_FRect{ 0, 0, 300.0f, 70.0f }, "Data//Picture//ScoreTab_600_100_600_100.png", renderer, false);

	
	// cho chạy map
	isRunning = true;
	back = false;
}

void Gameplay::Loop() {
	Timer::sInit->reset();
	//MixBackGround.addSound("Data//run.mp3");
	//chọn map
	chooseMap();
	SDL_ShowCursor(false);//ẩn con trỏ chuột
	if (*Autorun) SDL_ShowCursor(true);
	//vòng lặp gameplay 
	isRunning = true;
	Index = -1;
	while (isRunning && !quit) {
		//std::cout << timegame << std::endl;
		handleEvent();//nhận sự kiện
		update();
		render();
		buttonResume->Setclick(Event.BUTTON_LEFT); // cài click cho resume
		// click vào resume
		if (buttonResume->Getclick() ) {
			SDL_ShowCursor(true);
			resume = true; // hiện resume
			if (heart <= 0) resume = false;// nếu thua thì không hiện resume lại
			if (ManagerObject.IsEmty()) resume = false;// nếu thắng thì không hiện resume lại
		}
		// nếu đang hiện resume
		if (resume) {
			sethit = false; // không đánh dc đối tượng
			// cài click cho 2 buttons
			buttonEnd1->Setclick(Event.BUTTON_LEFT); 
			buttonBack->Setclick(Event.BUTTON_LEFT);
			if (buttonEnd1->Getclick()) {
				// reset lại thông số khi bấm nút thoát map
				heart = 5;
				ManagerObject.Reset();
				sethit = true; //cho phép đánh fly
				resume = false;// thoát resume
				back = true; // quay lùi listmap
				isRunning = false; // thoát map
				SDL_ShowCursor(false);

			}
			if (buttonBack->Getclick()) {
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
			
			buttonEnd1->Setclick(Event.BUTTON_LEFT);
			buttonBack->Setclick(Event.BUTTON_LEFT);
			if (buttonBack->Getclick()) {
				//chơi lại game
				timegame = 0;
				sethit = true; // cho phép đánh
				SDL_ShowCursor(false);
				heart = 5;// cài lại số mạng
				ManagerObject.Reset();
				// cài lại map
				chooseMap();
			}
			if (buttonEnd1->Getclick()) {
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
			SDL_ShowCursor(true);
			if (ManagerObject.scored > 0) {

				buttonEnd1->Setclick(Event.BUTTON_LEFT);// quay về listmap
				buttonBack->Setclick(Event.BUTTON_LEFT);// chơi lại màn chơi
				buttonNext->Setclick(Event.BUTTON_LEFT);// qua màn kế tiếp
				if (buttonBack->Getclick()) {
					//reset thông số màn chơi
					timegame = 0;
					ManagerObject.Reset();
					heart = 5;
					chooseMap();
				}
				if (buttonEnd1->Getclick()) {
					//quay lại litsmap
					back = true;
					timegame = 0;
					heart = 5;
					ManagerObject.Reset();
					isRunning = false;
				}
				if (buttonNext->Getclick()) {
					//qua màn tiếp theo
					timegame = 0;
					heart = 5;
					(*choose)++;
					chooseMap();
				}
				
			}
			else {
				sethit = false; // không cho phép đánh fly

				buttonEnd1->Setclick(Event.BUTTON_LEFT);
				buttonBack->Setclick(Event.BUTTON_LEFT);
				if (buttonBack->Getclick()) {
					//chơi lại game
					timegame = 0;
					sethit = true; // cho phép đánh
					SDL_ShowCursor(false);
					heart = 5;// cài lại số mạng
					ManagerObject.Reset();
					// cài lại map
					chooseMap();
				}
				if (buttonEnd1->Getclick()) {
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
	char text1[50] = "FLY KILLER SCORE:";
	char text2[50], text3[50] = "YOUR SCORE:", win[20] = "YOU WIN!", lose[20] = "YOU LOSE!";

	// dòng text null tạm thời được copy từ text khai báo bên trên
	strcpy(text2, text1);
	char Maxscored[50] = "YOUR HIGHT SCORE IS:";

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
}

void Gameplay::chooseMap()
{
	switch (*choose) {
	case 1:
		ManagerObject.ReadMap(renderer, "Data//Map-dif//Level1.txt");
		break;
	case 2:
		ManagerObject.ReadMap(renderer, "Data//Map-dif//Level2.txt");
		break;
	}
}

void Gameplay::render() {

		//Kẹp giữa dòng đầu 
		SDL_RenderClear(renderer);
		//winloseresume(resume, ManagerObject.IsEmty(), heart, ManagerObject.scored );
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
				// render hộp thoại thắng
				box->Render();
				buttonEnd1->Render();
				buttonBack->Render();
				buttonNext->Render();
				Noti.render();
				HightScore.render();
				ifWin.render();

			}
			else {
				//nếu điểm bằng 0 thì thua 
				box->Render();
				buttonEnd1->Render();
				buttonBack->Render();
				Noti.render();
				HightScore.render();
				ifLose.render();
			}
			
		}
		//nếu chưa dừng
		if (!resume) {
			           // nếu số mạng chưa thua thì render đối tượng
			if (heart > 0) ManagerObject.render(renderer);
			else {
				// nếu thua thì không render đối tượng mà render hộp thoại thua
				box->Render();
				buttonEnd1->Render();
				buttonBack->Render();
				Noti.render();
				HightScore.render();
				ifLose.render();
			}
		}
		//nếu dừng
		else {

			//render hộp thoại resume
			box->Render();
			buttonEnd1->Render();
			buttonBack->Render();
			Noti.render();
			HightScore.render();
			ifResume.render();
		}

		SDL_RenderPresent(renderer);
}
void Gameplay::destroy()
{
	Timer::sInit->release();// xoá thời gian
	SDL_DestroyRenderer(renderer);
}

