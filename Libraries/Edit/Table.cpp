#include <Table.h>



ScrollVertical* Scroll = nullptr;
FramesObject* BackGround = nullptr;

std::vector <ButtonTable*> listButton;

Table::Table(float pos_x, float pos_y, float width, float height, std::vector<FlyEdit*>* flys, FlyEdit** fly, SDL_Renderer* renderer, HandelEvent* Event) :
	pos_x(pos_x), pos_y(pos_y), width(width), height(height),
	flys(flys), fly(fly), renderer(renderer), Event(Event)
{
	Area.x = pos_x;
	Area.y = pos_y;
	Area.w = width;
	Area.h = height;

	Scroll = new ScrollVertical(pos_x + width * 0.9f, pos_y + height * 0.22f, width * 0.05f, height * 0.65f, renderer);
	Scroll->setValue(0, 1000);
	BackGround = new FramesObject(new SDL_FRect{ pos_x, pos_y, width, height }, "Data/Edit/BackGround_60_120_60_120.png", renderer, false);

	Index = 0;
	Count = 0;
	for (int i = 0; i < flys->size(); ++i)
	{
		listButton.push_back(new ButtonTable(pos_x + width * 0.5f, pos_y + height * 0.23f, width * 0.65f, height * 0.1f, (*flys)[0]->getAddTimeStart(), (*flys)[0]->getAddTimeEnd(), renderer, Count++));
	}
}

void Table::update()
{
	if (CollisionButton(Area)) 
	{
		Scroll->MoveCrollWheel(Event);
		Scroll->MoveCroll(Event->BUTTON_LEFT_PRESS);
		pos_y_bottun = Scroll->getValue();
	}

	for (int i = 0; i < Count; ++i)
	{
		if (listButton[i]->getClickDelete() && flys->size() != 1)
		{
			std::cout << flys->size() << std::endl;
			DeleteButton(i);
			DeleteFly(i);
			std::cout << flys->size() << std::endl;
			
			Count--;
			break;
		}

		// chon ruoi de thay doi thong so
		listButton[i]->update(Event, pos_y + height * 0.23f -pos_y_bottun);
		if (listButton[i]->getClick() || (CollisionButton((*flys)[i]->getAreaFly()) && Event->BUTTON_LEFT) )
		{
			(*flys)[Index]->unPick();
			Index = i;
			*fly = (*flys)[i];
			(*fly)->Pick();
		}
	}	
}

void Table::render()
{

	for (int i = 0; i < listButton.size(); ++i)
	{
		listButton[i]->render(pos_y, pos_y + height * 0.9f);
	}
	Scroll->Render();
	BackGround->Get_Texture();
}

void Table::addButton(FlyEdit* fly)
{
	listButton.push_back(new ButtonTable(pos_x + width * 0.5f, pos_y + height * 0.23f, width * 0.65f, height * 0.1f, fly->getAddTimeStart(), fly->getAddTimeEnd(), renderer, Count++));
}

void Table::DeleteButton(int index)
{
	for (int i = index; i < listButton.size() - 1; ++i)
	{
		listButton[i] = listButton[i + 1];
		listButton[i]->setNum(i);
	}
	listButton.pop_back();
}
void Table::DeleteFly(int index)
{
	for (int i = index; i < flys->size() - 1; ++i)
	{
		(*flys)[i] = (*flys)[i + 1];

	}
	flys->pop_back();
}
