#ifndef FLY_H_
#define FLY_H_

#include "Object.h"
#include "Vector.h"
#define pi 3.1415926

class Fly :public Object {
protected:
	Vector direction;
	double angle;


public:
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

	void UpdateFly()
	{
		if (dest.x > 1440 || dest.x < 0)
		{
			direction.x *= -1;
		}
		if (dest.y > 720 || dest.y < 0)
		{
			direction.y *= -1;
		}

		dest.x += 0.5*direction.x;
		dest.y += 0.5*direction.y;
		pos_x += direction.x;
		pos_y += direction.y;
		angle = atan(direction.y / direction.x);

		if (direction.x < 0) angle = angle + pi;
		angle = angle * 180 / pi;
	}
	
	void Render()
	{
		SDL_RenderCopyExF(renderer, Texture, &scr, &dest, angle + 90, NULL, SDL_FLIP_NONE);
	}
	
};


#endif
