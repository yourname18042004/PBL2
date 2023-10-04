#ifndef TABLE_H
#define TABLE_H

#include <Init/Gameplay.h>
#include <ScrollBar.h>
#include <Content.h>
#include <vector>
#include <ButtonTable.h>
#include <FlyEdit.h>

class Table
{
private:

	float pos_x;
	float pos_y;
	float width;
	float height;

	float pos_y_bottun;

	SDL_FRect Area;

	std::vector<FlyEdit*>* flys;
	SDL_Renderer* renderer;

	HandelEvent* Event;

	FlyEdit** fly = nullptr;

	int Index; // index ruoi hien tai dang duoc chon
	int Count; // so ruoi hien dang co

	void DeleteButton(int index);
	void DeleteFly(int index);

public:
	Table(float pos_x, float pos_y, float width, float height, std::vector<FlyEdit*>* flys, FlyEdit** fly, SDL_Renderer* renderer, HandelEvent* Event);
	
	// xoa ruoi va chon ruoi de edit
	void update();
	
	// render table
	void render();
	
	// them nut vao table
	void addButton(FlyEdit* fly);

};



#endif // 


