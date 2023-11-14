#ifndef FLY_H_
#define FLY_H_

#include "Object.h"
#include <Time_vector/Vector.h>
#include <Vacham/CollisionHandling.h>

#define pi 3.1415926

class Fly:public Object {
protected:
	float* timegame;
	Vector direction;
	double angle;
	FramesObject* FlyNormal = nullptr;
	FramesObject* FlySuper = nullptr;
	FramesObject* Goal = nullptr;
	FramesObject* Line = nullptr;
	SDL_FRect area;
	SDL_FRect goal;
	SDL_FRect line;
	SDL_Point linePoint;
	int score;
	Vector Start;
	Vector End;
	float speed;
	
	float t_to_a; //time to apear
	float t_to_land;

public:
	Fly
	(
		float pos_x, float pos_y, float width, float height,
		float end_x, float end_y, float t_to_a, float t_to_land,
		float speed, SDL_Renderer* Render, int score, float* timegame)
		: Object(pos_x, pos_y, width, height, Render) {
		area.x = pos_x;
		area.y = pos_y;
		area.h = height;
		area.w = width;

		this->Start = Vector{ pos_x, pos_y };
		this->End = Vector{ end_x, end_y };
		this->t_to_a = t_to_a;
		this->t_to_land = t_to_land;
		this->speed = speed;

		direction.x = End.x - Start.x;
		direction.y = End.y - Start.y;
		float r = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x = direction.x / r;
		direction.y = direction.y / r;

		status = false;//Trangj thái di chuyển
		this->score = score;

		FlyNormal = new FramesObject(&area, "Data//Picture//fly_100_100_200_100.png", renderer, true);

		this->timegame = timegame;


		// dat vi tri chi line va goal
		line.w = 10;
		line.h = r;
		line.x = Start.x + width / 2.0f - line.w / 2.0f ;
		line.y = Start.y  - line.h + area.h/2;

		goal.x = End.x + 25;
 		goal.y = End.y + 25;
		goal.h = height - 50;
		goal.w = width - 50;

		// dat vi tri xoay cua hinh chu Line
		linePoint.x = line.w / 2;
		linePoint.y = line.h;

		Line = new FramesObject(&line, "Data//Picture//Line_100_100_100_100.png", renderer, false);
		Goal = new FramesObject(&goal, "Data//Picture//Goal_100_100_100_100.png", renderer, false);
	}

	bool status;
	// hàm cập nhật điểm cho đối tượng (chú ý không gán trực tiếp lúc khai báo)

	SDL_FRect GetArea()
	{
		SDL_FRect tmp;
		tmp.x = area.x + area.w / 2;
		tmp.y = area.y + area.h / 2;
		tmp.h = area.h;
		tmp.w = area.w;
		return tmp;
	}

	void UpdateScore(int score) {
		this->score = score;
	}

	void UpdateFly()
	{
		if(*timegame > t_to_a) FlyNormal->UpdateFrames();

	}
	
	void Render()
	{
		if (*timegame > t_to_a)
		{
			double angle = atan((double)direction.y / (double)direction.x);
			if (direction.x < 0) angle += pi;
			// ve line va goal
			Line->Get_Texture((angle * 180) / pi + 90, linePoint);
			Goal->Get_Texture();
			FlyNormal->Get_Texture((angle * 180) / pi + 90);
		}
	}
	
	int Getscore() {
		return score;
	}

	void move() {
		if (*timegame > t_to_a)
		{
			float t = Timer::sInit->DeltaTime();

			if (!status)
			{
				area.x += direction.x * speed * t;
				area.y += direction.y * speed * t;
			}

			if (!status && setFly() && t_to_land > 0) status = true;
			if (status)
			{
				t_to_land -= t;
				if (t_to_land <= 0) status = false;
			}
		}
	}

	

	bool setFly()
	{
		Vector v1{ area.x - Start.x, area.y - Start.y };
		Vector v2{ area.x - End.x, area.y - End.y };
		float dot = v1.x * v2.x + v1.y * v2.y;
		if (dot < 0) return false;
		else return true;
	}

	void setStatus(bool set) {
		this->status = set;
	}

	bool getStatus()
	{
		return status;
	}
	bool Collison(SDL_FRect Racket) {
		return Collision(area, Racket);
	}
	bool TimeLand(float *timegame) {
		float r = sqrt((End.x - Start.x) * (End.x - Start.x) + (End.y - Start.y) * (End.y - Start.y));
		float t = r / speed;
		if (t - *timegame + t_to_a < 0.1) return true;
		else return false;
	}
	Vector GetEnd() {
		return End;
	}
};


#endif
