#ifndef FLY_H_
#define FLY_H_

#include "Object.h"
#include "Vector.h"

class Fly :public Object {
public:
	int score;
	bool status = true;
	Vector direction;
	// hàm cập nhật điểm cho đối tượng (chú ý không gán trực tiếp lúc khai báo)
	void UpdateScore(int score) {
		this->score = score;
	}
};


#endif
