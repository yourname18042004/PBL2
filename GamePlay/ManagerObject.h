#ifndef MANAGER_OBJECT_H
#define	MANAGER_OBJECT_H
#include "Object.h"
#include "Init.h"
#include <iostream>
#include <vector>
#include "CollisionHandling.h"
#include "Racket.h"
#include "HandelEvent.h"
#include <cstdlib>
#include <time.h>
#define pi 3.1415926


class Manager {
private:
	std::vector<Fly> obJect;
	Racket* racKet;
	HandelEvent* Handel;
	
public:
	int scored = 0;
	//Thêm vào mảng vector 1 đối tượng
	void Add(Fly a); 
	
	void Add(Racket* racKet);
	
	void Add(HandelEvent* Handel);

	void render(SDL_Renderer* renderer);
	//Lấy giá trị độ lớn mảng vector
	int getSize();
	//Update vị trí, vector độ dời của đối tượng
	void UpdatePositionAndVector();
	
};



#endif 
