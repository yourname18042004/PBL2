
#ifndef FLY_EDIT_H
#define FLY_EDIT_H

#include <Init/Gameplay.h>

class FlyEdit
{
private:
	// thoi gian hien tai cua game
	float *timeGame;
	// thoi gian ruoi bat dau chay
	float timeStart;
	// khoang thoi gian ruoi dung yen
	float timePause;
	// thoi gian ruoi 
	float timeEnd;

	// diem 
	float score;
	// toc do
	float speed;

	// huong cua ruoi di chuyen
	Vector direction;

	// Rect vi tri ruoi bat dau,
	SDL_FRect Start, End, Fly;
	SDL_FRect line;

	FramesObject* renderFly = nullptr; // hinh anh ruoi
	FramesObject* renderStart = nullptr; // hinh anh diem bat dau
	FramesObject* renderEnd = nullptr; // hinh anh diem ket thuc
	FramesObject* Line = nullptr; // hinh anh duong di
	
	// hinh anh xuat hien neu ruoi duoc chon de dieu chinh thong so
	FramesObject* renderStartPick = nullptr; 
	FramesObject* renderEndPick = nullptr;
	FramesObject* LinePick = nullptr;

	// diem ma Rect line dung la trung diem de xoay
	SDL_Point linePoint;

	SDL_Renderer* renderer;
	HandelEvent* Event;

	float k; // ti le, dau vao se bi giam ti le de phu hop voi man hinh nho trong Edit
	float delta_x, delta_y; // giu cho x, y cua Rect khong bi dinh vao chuot khi click chon doi tuong
	bool followE = false; // chon diem cuoi de di chuyen diem do 
	bool followS = false; // chon diem dau de di chuyen diem do
	bool pick; // set xem doi tuong co duoc chon hay khong
public:
	FlyEdit(float pos_x, float pos_y, float width, float height,
		float end_x, float end_y, float t_to_a, float t_to_land,
		float speed, SDL_Renderer* renderer, int score, float* timegame, HandelEvent* Event)
	{
		k = 0.8f; // ti le so voi man hinh chinh

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
		// tinh toan thoi gian cuoi voi cac thong so toc do, diem dau, diem cuoi
		timeEnd = timeStart + x / (direction.x * this->speed) + timePause;
		
		// dat vi tri chi line va goal
		line.w = 30 * k;
		line.h = r;
		line.x = Start.x + width / 2.0f - line.w / 2.0f;
		line.y = Start.y - line.h + Fly.h / 2;

		// dat vi tri xoay cua hinh chu Line
		linePoint.x = line.w / 2;
		linePoint.y = line.h;

		renderFly = new FramesObject(&Fly, "Data//Picture//fly_100_100_200_100.png", renderer, true);
		Line = new FramesObject(&line, "Data//Edit//Line_50_50_50_50.png", renderer, false);
		renderStart = new FramesObject(&Start, "Data//Edit//Goal_50_50_50_50.png", renderer, false);
		renderEnd = new FramesObject(&End, "Data//Edit//Goal_50_50_50_50.png", renderer, false);
		
		LinePick = new FramesObject(&line, "Data//Edit//LinePick_50_50_50_50.png", renderer, false);
		renderStartPick = new FramesObject(&Start, "Data//Edit//GoalPick_50_50_50_50.png", renderer, false);
		renderEndPick = new FramesObject(&End, "Data//Edit//GoalPick_50_50_50_50.png", renderer, false);

		this->renderer = renderer;
		this->Event = Event;
		this->pick = false;
		this->score = score;
	}

	// Tinh toan lai tat ca cac gia tri neu co mat ki mot gia tri nao bi thay doi
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

		// render chi khi ruoi duoc chon
		if (pick)
		{
			LinePick->Get_Texture((angle * 180) / pi + 90, linePoint);
			renderEndPick->Get_Texture();
			renderStartPick->Get_Texture();
		}

		// render trong khoang thoi gian ruoi bat dau xuat hien va thoi gian ket thuc cua ruoi
		if (*timeGame >= timeStart && *timeGame <= timeEnd)
		{
			
			// ve line va goal
			
			Line->Get_Texture((angle * 180) / pi + 90, linePoint);
			renderEnd->Get_Texture();
			renderStart->Get_Texture();
			renderFly->Get_Texture((angle * 180) / pi + 90);
		}

		

	}

	// cho ruoi chay khi thoi gian cua game chay
	void move() 
	{
		moveStart(); // di chuyen diem bat dau cua ruoi theo vi tri hien tai cuar chuot
		moveEnd(); // di chuyen diem ket thuc cua ruoi theo vi tri hien tai cuar chuot

		if (*timeGame >= timeStart && *timeGame <= timeEnd - timePause)
		{
			float t = Timer::sInit->DeltaTime();

			Fly.x = Start.x + direction.x * speed * (*timeGame - timeStart);
			Fly.y = Start.y + direction.y * speed * (*timeGame - timeStart);
		}
	}

	// chua dc su dung nhung cu de do 
	bool setFly()
	{
		Vector v1{ Fly.x - Start.x, Fly.y - Start.y };
		Vector v2{ Fly.x - End.x, Fly.y - End.y };
		float dot = v1.x * v2.x + v1.y * v2.y;
		if (dot < 0) return false;
		else return true;
	}

	// di chuyen bat dau theo chuot
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


	// di chuyen diem cuot theo chuot
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

	// cap nhat toc do
	void updateSpeed(float speed)
	{
		if (pick)
		{
			this->speed = speed;
			UpdateFly();
		}
	}

	// cap nhat htoi gian dung
	void updateTimePause(float pause)
	{
		if (pick)
		{
			this->timePause = pause;
			UpdateFly();
		}	
	}

	// cap nhat diem
	void updateScore(float score)
	{
		if (pick)
		{
			this->score = score;
		}
	}

	// cap nhat thoi gian bat dau
	void updateTimeStart(float timeStart)
	{
		if (pick)
		{
			this->timeStart = timeStart;
			UpdateFly();
		}
	}

	void Pick() { pick = true; } // Chon ruoi
	void unPick() { pick = false; } // Bo chon ruoi


	// lay tat ca ca gia tri
	Vector GetStart() { return { Start.x, Start.y }; }
	Vector GetWidthHeight() { return { Start.w, Start.w }; }
	Vector GetEnd() { return { End.x, End.y }; }
	SDL_FRect getAreaFly() { return Fly; }
	float getSpeed() { return speed; }
	float getTimePause() { return timePause; }
	float getScore() { return score; }
	float getTimeStart() { return timeStart; }
	float getTimeEnd() { return timeEnd; }
	float* getAddTimeStart() { return &timeStart; }
	float* getAddTimeEnd() { return &timeEnd; }
};

#endif