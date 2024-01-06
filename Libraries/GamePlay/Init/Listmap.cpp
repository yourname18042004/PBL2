#include "Listmap.h"

std::vector <Buttons*> MapLevel;
std::vector <std::pair<Buttons*, Buttons*>> CustomMap;
std::vector <Content> content;

Buttons* yes = nullptr;
Buttons* no = nullptr;
Buttons* backMenu = nullptr;
Buttons* setDeleteMap = nullptr;
FramesObject* background2 = nullptr;
FramesObject* Box = nullptr;

FramesObject* RacketChoose = nullptr;
float Racketpos = 500;

Text textAutorun;

std::string getName(std::string s) {
	std::string tmp;
	for (int i = 15; i < s.size(); ++i) {
		if (s[i] == '.') break;
		tmp.push_back(s[i]);
	}
	return tmp;
}

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
	
	setDeleteMap = new Buttons(1390, 550, 100, 100, "Data//Picture//bin_100_100_200_100.png", renderer);
	setDelete = false;

	backMenu = new Buttons(1390, 670, 150, 150, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);

	textAutorun.init(330,450,250,50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "AUTORUN?", renderer);
	// khởi tạo các biến quản lý 
	back = false; // đi lùi
	Index = -1;
	isRunning = true;
	Autorun = false;
	pos_y_button = 50;
	RacketChoose = new FramesObject(new SDL_FRect{ Racketpos, 570, 100.0, 100.0 }, "Data//Picture//Racketchoose_100_100_100_100.png", renderer, false);
	
	level_default = 5;

	updateMap();
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
	FILE* p;
	int k;
	//NumofLevel = 0;
	//p = fopen("Data//Map-dif//ManagerMap.txt", "r");
	//fscanf(p, "%d", &k);
	if (NumofLevel != Map::sInit->m.size())
	{
		
		NumofLevel = Map::sInit->m.size();
		CustomMap.clear();
		MapLevel.clear();
		content.clear();

		for (int i = 0; i < level_default; i++)
		{
			MapLevel.push_back(new Buttons(1100, 320, 280, 85, "Data//Picture//Level_350_100_700_100.png", renderer));

			Content tmp;
			std::string str = "LEVEL " + std::to_string(i + 1);
			tmp.init(980, 320, 50, 50, "Data//Galhau_Regular.ttf", 50, { 0, 0, 0, 255 }, str.c_str(), renderer);
			content.push_back(tmp);
		}
		
		for (int i = level_default; i < NumofLevel-1; ++i) {
			for (int j = i + 1; j < NumofLevel; ++j) {
				if (Map::sInit->m[i].compare(Map::sInit->m[j]) > 0) {
					std::swap(Map::sInit->m[i], Map::sInit->m[j]);
				}
			}
		}
		for (int i = level_default; i < NumofLevel; i++) {
			char path[100];
			CustomMap.push_back
			({ 
				new Buttons(1100, 320, 280, 85, "Data//Picture//Level_350_100_700_100.png", renderer), 
				new Buttons(930, 320, 50, 50, "Data//Edit//Delete_50_50_100_50.png", renderer)
			});
			Content tmp;
			std::string str = getName(Map::sInit->m[i]);
			int sizetext = 7 * 50 / (str.size());
			if (sizetext > 50) sizetext = 50;
			tmp.init(980, 320, sizetext, sizetext, "Data//Galhau_Regular.ttf", sizetext , { 0, 0, 0, 255 }, str.c_str(), renderer);
			content.push_back(tmp);
		}
		CustomMap.push_back
		({
			new Buttons(1100, 320, 280, 85, "Data//Picture//Level_350_100_700_100.png", renderer),
			new Buttons(930, 320, 50, 50, "Data//Edit//Delete_50_50_100_50.png", renderer)
		});
		Content tmp; 
		tmp.init(980, 320, 50, 50, "Data//Galhau_Regular.ttf", 50, { 0, 0, 0, 255 }, "NULL", renderer);
		content.push_back(tmp);
	}
	//fclose(p);
}

// Hàm khởi tạo của sổ
void ListMap::update() {
	if (*UpdateIfAddMap)
	{
		updateMap();
		*UpdateIfAddMap = !(*UpdateIfAddMap);
	}

	if (Event.crossUp && pos_y_button + NumofLevel * 100 > 720) pos_y_button -= 30.0f;
	if (Event.crossDown && pos_y_button < 50) pos_y_button += 30.0f;
	
	int index = 0;

	for (int i = 0; i < level_default; ++i)
	{
		MapLevel[i]->setDest(MapLevel[i]->getDest().x, pos_y_button + index * 100);
		if (setDelete == false)
		{
			MapLevel[i]->Setclick(Event.BUTTON_LEFT);
			if (MapLevel[i]->Getclick()) {
				Index = 0;
				choose = i + 1;
				isRunning = false;
			}
		}

		content[i].update(1020, pos_y_button + index * 100 + 20);
		content[i].update(CollisionButton(MapLevel[i]->getDest()));
		++index;
	}
	
	for (int i = 0; i < NumofLevel - level_default; i++)
	{
		CustomMap[i].first->setDest(CustomMap[i].first->getDest().x, pos_y_button + index * 100);
		if (setDelete == false)
		{
			CustomMap[i].first->Setclick(Event.BUTTON_LEFT);
			if (CustomMap[i].first->Getclick()) {
				Index = 0;
				choose = level_default + i + 1;
				isRunning = false;
			}
		}
		if(setDelete == true)
		{
			CustomMap[i].second->setDest(CustomMap[i].second->getDest().x, pos_y_button + index * 100);
			CustomMap[i].second->Setclick(Event.BUTTON_LEFT);
			if (CustomMap[i].second->Getclick())
			{
				DeleteMap(i + level_default);
			}
		}

		content[i + level_default].update(1020, pos_y_button + index * 100 + 20);
		content[i + level_default].update(CollisionButton(CustomMap[i].first->getDest()));
		index++;
	}
	
	yes->Setclick(Event.BUTTON_LEFT);
	no->Setclick(Event.BUTTON_LEFT);
	backMenu->Setclick(Event.BUTTON_LEFT);
	setDeleteMap->Setclick(Event.BUTTON_LEFT);

	if (backMenu->Getclick()) {
		back = true;
		isRunning = false;
	}
	if (setDeleteMap->Getclick())
	{
		setDelete = !setDelete;
	}
	if (no->Getclick()) {
		Autorun = false;
		Racketpos = 500; 
		RacketChoose->setPositionDest(Racketpos, 570);
	}
	if (yes->Getclick()) {
		Autorun = true;
		Racketpos = 300;
		RacketChoose->setPositionDest(Racketpos, 570);
	}

}
void ListMap::DeleteMap(int index)
{
	remove(Map::sInit->m[index].c_str());
	Map::sInit->deleteMap(index);

	//NumofLevel = Map::sInit->m.size();

	updateMap();
}

// Hàm hiện thị đối tượng
void ListMap::render() {
	SDL_RenderClear(renderer);

	background2->Get_Texture();

	for (int i = 0; i < level_default; ++i)
	{
		MapLevel[i]->Render();
		content[i].render();
	}
	for (int i = 0; i < NumofLevel - level_default; ++i)
	{
		CustomMap[i].first->Render();
		if(setDelete == true) CustomMap[i].second->Render();
		content[i + level_default].render();
	}

	backMenu->Render();
	setDeleteMap->Render();
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


