#ifndef FLY_H_
#define FLY_H_

#include "Object.h"
#include "Vector.h"

class Fly :public Object {
	int score;
	bool status;
	Vector direction;
};


#endif
