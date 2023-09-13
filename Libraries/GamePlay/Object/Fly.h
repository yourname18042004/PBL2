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

public:
	int score;
	bool status;
	// hàm cập nhật điểm cho đối tượng (chú ý không gán trực tiếp lúc khai báo)
	
	void Init()
	{
		FlyNormal = new FramesObject(pos_x, pos_y, width, height, "Data//FlyUpdate_400_100.png", renderer);
		//FlySuper = new FramesObject(pos_x, pos_y, width, height, "Duong dan anh", renderer);
	}

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
		FlyNormal->UpdateFrames();

	}
	
	void Render()
	{
		FlyNormal->Get_Texture();
	}
	
};


#endif
