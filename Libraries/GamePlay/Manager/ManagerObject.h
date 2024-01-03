#ifndef MANAGER_OBJECT_H
#define	MANAGER_OBJECT_H
#include <Object/Object.h>
#include <Init/Window.h>
#include <iostream>
#include <vector>
#include <Vacham/CollisionHandling.h>
#include <Object/Racket.h>
#include <Data Structure/Linklist.h>
#include "HandelEvent.h"
#include <cstdlib>
#include <string.h>
#include <Time_vector/Timer.h>
#include <Manager/Docfile.h>

#define pi 3.1415926


class Manager {
private:
	float* timegame; // con tro tiem tro den bien time game cua gameplay roi tiep tuc truyen den cho game play
	
	std::vector<Fly> obJect;
	Racket* racKet;
	//HandelEvent* Handel;
	ObjectLinkList<Fly>* FlyLinkList = nullptr;

	int sizeStart;
	int sizeEnd;
	float percent;

public:
	int scored = 0;
	//Thêm vào mảng vector 1 đối tượng
	Manager();

	void Add(Fly* a); 
	
	void Add(Racket* racKet);
	
	void Add(HandelEvent* Handel);

	void Add(float* timegame);

	void ReadMap(SDL_Renderer* renderer, int level);

	void Update(bool set, int &heart, bool autorun, float *timegame);
	void render(SDL_Renderer* renderer);
	//Lấy giá trị độ lớn mảng vector
	int getSize();
	//Update vị trí, vector độ dời của đối tượng
	void UpdatePositionAndVector();

	void ManagerFly(bool set, int &heart, bool Autorun, float *timegame);

	bool IsEmty();

	void Reset();
	
	float getPercent();
	
};



#endif 
