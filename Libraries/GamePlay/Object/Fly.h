#ifndef FLY_H_
#define FLY_H_

#include "Object.h"
#include <Time_vector/Vector.h>

#define pi 3.1415926

class Fly:public Object {
protected:
	Vector direction;
	double angle;
	FramesObject* FlyNormal = nullptr;
	FramesObject* FlySuper = nullptr;
	SDL_FRect area;
	int score;
public:
	Fly(float pos_x, float pos_y, float width, float height, Vector direction, SDL_Renderer* Render, int score) : Object(pos_x, pos_y, width, height, Render){
		area.x = pos_x;
		area.y = pos_y;
		area.h = height;
		area.w = width;
		this->direction = direction;
		this->score = score;
		FlyNormal = new FramesObject(&area, "Data//FlyUpdate_100_100_400_100.png", renderer, true);
		//FlySuper = new FramesObject(&area, "Data//FlyUpdate_100_100_200_100.png", renderer, true);
	}

	bool status;
	// hàm cập nhật điểm cho đối tượng (chú ý không gán trực tiếp lúc khai báo)

	void UpdateScore(int score) {
		this->score = score;
	}

	void UpdateVector(Vector v)
	{
		direction.x = v.x;
		direction.y = v.y;
	}

	Vector getDir() { return direction; }

	void UpdatePosition(Vector v)
	{
		area.x += v.x;
		area.y += v.y;
	}

	void UpdateFly()
	{
		FlyNormal->UpdateFrames();

	}
	
	void Render()
	{
		double angle = atan((double)direction.y / (double)direction.x);
		if (direction.x < 0) angle += pi;
		FlyNormal->Get_Texture((angle * 180) / pi + 90);
	}
	SDL_FRect GetArea() {
		return area;
	}
	void SetArea(float x, float y) {
		area.x = x;
		area.y = y;
	}
	int Getscore() {
		return score;
	}
};


#endif
