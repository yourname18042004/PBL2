#ifndef FLY_H_
#define FLY_H_

#include "Object.h"
#include "Vector.h"

class Fly :public Object {
public:
	int score;
	bool status = true;
	Vector direction;
};


#endif
