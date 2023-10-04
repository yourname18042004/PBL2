#ifndef FLY_EDIT_H
#define FLY_EDIT_H

#include <Init/Gameplay.h>

class FlyEdit
{
private:
	float *timeGame;
	float timeStart;
	float timePause;
	float timeEnd;

	float core;
	float speed;

	Vector direction;

	SDL_FRect Start, End, Fly;
	SDL_FRect line;

	FramesObject* renderFly = nullptr;
	FramesObject* renderStart = nullptr;
	FramesObject* renderEnd = nullptr;
	FramesObject* Line = nullptr;
	FramesObject* renderStartPick = nullptr;
	FramesObject* renderEndPick = nullptr;
	FramesObject* LinePick = nullptr;

	SDL_Point linePoint;

	SDL_Renderer* renderer;
	HandelEvent* Event;

	float k;
	float delta_x, delta_y;
	bool followE = false;
	bool followS = false;
	bool pick;
public:
	FlyEdit(float pos_x, float pos_y, float width, float height,
		float end_x, float end_y, float t_to_a, float t_to_land,
		float speed, SDL_Renderer* renderer, int score, float* timegame, HandelEvent* Event)
	{
		k = 0.8f;

		Start.x = pos_x * k;
		Start.y = pos_y * k;
		Start.w = width * k;
		Start.h = height * k;

		End.x = end_x * k;
		End.y = end_y * k;
		End.h = height * k;
		End.w = width * k;

		Fly = Start;

		this->speed = speed * k;
		this->timeGame = timegame;

		int x = End.x - Start.x;
		int y = End.y - Start.y;
		float r = sqrt(x * x + y * y);
		direction.x = x / r;
		direction.y = y / r;

		timeStart = t_to_a;
		timePause = t_to_land;
		timeEnd = timeStart + x / (direction.x * this->speed) + timePause;
		
		// dat vi tri chi line va goal
		line.w = 30 * k;
		line.h = r;
		line.x = Start.x + width / 2.0f - line.w / 2.0f;
		line.y = Start.y - line.h + Fly.h / 2;

		// dat vi tri xoay cua hinh chu Line
		linePoint.x = line.w / 2;
		linePoint.y = line.h;

		renderFly = new FramesObject(&Fly, "Data//fly_100_100_200_100.png", renderer, true);
		Line = new FramesObject(&line, "Data//Edit//Line_50_50_50_50.png", renderer, false);
		renderStart = new FramesObject(&Start, "Data//Edit//Goal_50_50_50_50.png", renderer, false);
		renderEnd = new FramesObject(&End, "Data//Edit//Goal_50_50_50_50.png", renderer, false);
		
		LinePick = new FramesObject(&line, "Data//Edit//LinePick_50_50_50_50.png", renderer, false);
		renderStartPick = new FramesObject(&Start, "Data//Edit//GoalPick_50_50_50_50.png", renderer, false);
		renderEndPick = new FramesObject(&End, "Data//Edit//GoalPick_50_50_50_50.png", renderer, false);

		this->renderer = renderer;
		this->Event = Event;
		this->pick = false;
	}

	void UpdateScore(int score) {
	
	}

	void UpdateFly()
	{
		
		
		int x = End.x - Start.x;
		int y = End.y - Start.y;
		float r = sqrt(x * x + y * y);
		direction.x = x / r;
		direction.y = y / r;

		timeEnd = timeStart + x / (direction.x * this->speed) + timePause;

		// dat vi tri chi line va goal
		line.w = 30 * k;
		line.h = r;
		line.x = Start.x + Start.w / 2.0f - line.w / 2.0f;
		line.y = Start.y - line.h + Fly.h / 2;

		// dat vi tri xoay cua hinh chu Line
		linePoint.x = line.w / 2;
		linePoint.y = line.h;
	}

	void Render()
	{
		double angle = atan((double)direction.y / (double)direction.x);
		if (direction.x < 0) angle += pi;

		if (pick)
		{
			LinePick->Get_Texture((angle * 180) / pi + 90, linePoint);
			renderEndPick->Get_Texture();
			renderStartPick->Get_Texture();
		}

		if (*timeGame >= timeStart && *timeGame <= timeEnd)
		{
			
			// ve line va goal
			
			Line->Get_Texture((angle * 180) / pi + 90, linePoint);
			renderEnd->Get_Texture();
			renderStart->Get_Texture();
			renderFly->Get_Texture((angle * 180) / pi + 90);
		}

		

	}

	void move() 
	{
		moveStart();
		moveEnd();

		if (*timeGame >= timeStart && *timeGame <= timeEnd - timePause)
		{
			float t = Timer::sInit->DeltaTime();

			Fly.x = Start.x + direction.x * speed * (*timeGame - timeStart);
			Fly.y = Start.y + direction.y * speed * (*timeGame - timeStart);
		}
	}

	bool setFly()
	{
		Vector v1{ Fly.x - Start.x, Fly.y - Start.y };
		Vector v2{ Fly.x - End.x, Fly.y - End.y };
		float dot = v1.x * v2.x + v1.y * v2.y;
		if (dot < 0) return false;
		else return true;
	}

	void moveStart()
	{
		if (CollisionButton(Start) && Event->BUTTON_LEFT_PRESS) followS = true;
		if (!Event->BUTTON_LEFT_PRESS) followS = false;
		if (followS && pick)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (Event->BUTTON_LEFT)
			{
				delta_x = x - Start.x;
				delta_y = y - Start.y;
			}
			
			Start.x = x - delta_x;
			Start.y = y - delta_y;

			UpdateFly();
		}
	}

	void moveEnd()
	{

		if (CollisionButton(End) && Event->BUTTON_LEFT_PRESS) followE = true;
		if (!Event->BUTTON_LEFT_PRESS) followE = false;
		if (followE && pick)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (Event->BUTTON_LEFT)
			{
				delta_x = x - End.x;
				delta_y = y - End.y;
			}

			End.x = x - delta_x;
			End.y = y - delta_y;

			UpdateFly();
		}
	}

	void updateSpeed(float speed)
	{
		if (pick)
		{
			this->speed = speed;
			UpdateFly();
		}
}

	void updateTimePause(float pause)
	{
		if (pick)
		{
			this->timePause = pause;
			UpdateFly();
		}	
	}

	void updateCore(float core)
	{
		if (pick)
		{
			this->core = core;
		}
	}

	void updateTimeStart(float timeStart)
	{
		if (pick)
		{
			this->timeStart = timeStart;
			UpdateFly();
		}
	}

	void Pick() { pick = true; }
	void unPick() { pick = false; }

	SDL_FRect getAreaFly() { return Fly; }
	float getSpeed() { return speed; }
	float getTimePause() { return timePause; }
	float getScore() { return core; }
	float getTimeStart() { return timeStart; }
	float getTimeEnd() { return timeEnd; }
	float* getAddTimeStart() { return &timeStart; }
	float* getAddTimeEnd() { return &timeEnd; }
};

#endif