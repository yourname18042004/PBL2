#include "Listmap.h"


std::vector <Buttons*> level;
std::vector <Content> content;
int NumofLevel;
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

	FILE* p;
	p = fopen("Data//Map-dif//ManagerMap.txt", "r");
	fscanf(p, "%d", &NumofLevel);
	fclose(p);
	for (int i = 0; i < NumofLevel; i++) {
		level.push_back(new Buttons(980, 320, 280, 85, "Data//Picture//Level_350_100_700_100.png", renderer));
		Content tmp;
		std::string str = "LEVEL " + std::to_string(i + 1);
		tmp.init(980, 320, 50, 50, "Data//Galhau_Regular.ttf", 50, { 0, 0,0, 255 }, str.c_str(), renderer);
		content.push_back(tmp);
	}
	
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

void ListMap::updateMap()
{
	level.clear();
	content.clear();
	FILE* p;
	p = fopen("Data//Map-dif//ManagerMap.txt", "r");
	fscanf(p, "%d", &NumofLevel);
	fclose(p);
	for (int i = 0; i < NumofLevel; i++) {
		level.push_back(new Buttons(980, 320, 280, 85, "Data//Picture//Level_350_100_700_100.png", renderer));
		Content tmp;
		std::string str = "LEVEL " + std::to_string(i + 1);
		tmp.init(980, 320, 50, 50, "Data//Galhau_Regular.ttf", 50, { 0, 0,0, 255 }, str.c_str(), renderer);
		content.push_back(tmp);
	}
	
}

// Hàm khởi tạo của sổ
void ListMap::update() {

	if (*UpdateIfAddMap)
	{
		updateMap();
		*UpdateIfAddMap = !(*UpdateIfAddMap);
	}

	RacketChoose = new FramesObject(new SDL_FRect{ Racketpos, 570, 100.0, 100.0 }, "Data//Picture//Racketchoose_100_100_100_100.png", renderer, false);
	if (Event.crossUp && pos_y_button + NumofLevel * 100 > 720) pos_y_button -= 30.0f;
	if (Event.crossDown && pos_y_button < 50) pos_y_button += 30.0f;
	//std::cout << pos_y_button << std::endl;
	for (int i = 0; i < NumofLevel; i++)
	{
		level[i]->setDest(level[i]->getDest().x, pos_y_button + i * 100);
		level[i]->Setclick(Event.BUTTON_LEFT);
		if (level[i]->Getclick()) {
			Index = 0;
			choose = i + 1;
			isRunning = false;
		}

		content[i].update(900, pos_y_button + i * 100 + 20);
		content[i].update(CollisionButton(level[i]->getDest()));
	}
	
	yes->Setclick(Event.BUTTON_LEFT);
	no->Setclick(Event.BUTTON_LEFT);
	backMenu->Setclick(Event.BUTTON_LEFT);
	
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

	for (int i = 0; i < NumofLevel; ++i)
	{
		level[i]->Render();
		content[i].render();
	}

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


