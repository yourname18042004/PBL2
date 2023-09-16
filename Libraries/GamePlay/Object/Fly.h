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
public:
	Fly(float pos_x, float pos_y, float width, float height, Vector direction, SDL_Renderer* Render) : Object(pos_x, pos_y, width, height, Render){
		area.x = pos_x;
		area.y = pos_y;
		area.h = height;
		area.w = width;
		this->direction = direction;
		FlyNormal = new FramesObject(&area, "Data//FlyKing_398_194.png", renderer, true);
	}
	
	int score;
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
		FlyNormal->Get_Texture();
	}
	SDL_FRect GetArea() {
		return area;
	}
};


#endif
