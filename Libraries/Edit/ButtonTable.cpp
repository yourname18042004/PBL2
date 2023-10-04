#include "ButtonTable.h"
	
ButtonTable::ButtonTable
(
	float pos_x, float pos_y, float width, float height,
	float* time_start, float* time_end,
	SDL_Renderer* renderer, int num
) :
	pos_x(pos_x), pos_y(pos_y), width(width), height(height),
	time_start(time_start), time_end(time_end),
	renderer(renderer), num(num)
{
	Area.x = pos_x;
	Area.y = pos_y;
	Area.w = width;
	Area.h = height;

	Button = new Buttons( pos_x , pos_y, width, height, "Data//Edit//ButtonTable_80_40_160_40.png", renderer);

	Delete = new Buttons(pos_x + 0.35f * width, pos_y + 0.5f * height, 30, 30, "Data//Edit//Delete_50_50_100_50.png", renderer);

	Num.init(pos_x + 0.1f * width, pos_y + 0.2f * height, 0.6f * height, 0.6f * height, "Data//Galhau_Regular.ttf", 0.6f * height, { 0, 0,0, 255 }, "0", renderer);
	TimeStart.init(pos_x + 0.3f * width, pos_y + 0.2f * height, 0.6f * height, 0.6f * height, "Data//Galhau_Regular.ttf", 0.6f * height, { 0, 0,0, 255 }, "0", renderer);
	TimeEnd.init(pos_x + 0.6f * width, pos_y + 0.2f * height, 0.6f * height, 0.6f * height, "Data//Galhau_Regular.ttf", 0.6f * height, { 0, 0,0, 255 }, "0", renderer);
}

void ButtonTable::update(HandelEvent* Event, float delta)
{
	
	Button->setDest(Button->getDest().x, delta + num * 60);
	Delete->setDest(Delete->getDest().x, Button->getDest().y + 0.25f * height);
	
	// update content
	Num.update(int(pos_x - 0.45f * width), int(Button->getDest().y + 0.2f * height), int(0.3f * height), int(0.3f * height), "Data//Galhau_Regular.ttf", int(0.3f * height), { 0, 0, 0, 255 }, toStr(num).c_str());
	TimeStart.update(int(pos_x - 0.30f * width), int(Button->getDest().y + 0.2f * height), int(0.3f * height), int(0.3f * height), "Data//Galhau_Regular.ttf", int(0.3f * height), { 0, 0,0, 255 }, toClock(*time_start).c_str());
	TimeEnd.update(int(pos_x - 0.30f * width), int(Button->getDest().y + 0.5f * height), int(0.3f * height), int(0.3f * height), "Data//Galhau_Regular.ttf", int(0.3f * height), { 0, 0,0, 255 }, toClock(*time_end).c_str());

	Button->Setclick(Event->BUTTON_LEFT);
	Delete->Setclick(Event->BUTTON_LEFT);
}

void ButtonTable::render(float above, float below)
{

	if (Button->getDest().y >= above && Button->getDest().y <= below)
	{
		Button->Render();
		Delete->Render(); 
		
		Num.render();
		TimeStart.render();
		TimeEnd.render();
	}	
}

void ButtonTable::setNum(int num)
{
	this->num = num;
}

bool ButtonTable::getClick() { return Button->Getclick(); }
bool ButtonTable::getClickDelete() { return Delete->Getclick(); }