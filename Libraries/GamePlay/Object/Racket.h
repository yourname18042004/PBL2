#ifndef _RACKET_
#define _RACKET_

#include "Object.h"
#include <Manager/HandelEvent.h>
#include <SDL.h>
class Racket : public Object {

private:
	bool setAnimation;// biến kiểm tra có thực hiện animation hay không

public:
	// khởi tạo giá trị false cho biến kiểm tra
	void SetTheAnimation() {
		this->setAnimation = false;
	}
	// update vị trí chuột
	void UpdatePositionOfMouse() {
	/*	int x, y;
		SDL_GetMouseState(&x, &y);
		dest.x = (float)(x - dest.w / 2);
		dest.y = (float)(y - dest.h / 2);*/

	}
	
	void AnimationRacket(HandelEvent handel) {
		//if (setAnimation) {
		//	Animation(true);
		//	}
		//if (handel.BUTTON_LEFT) {
		//	setAnimation = true;
		//}
		//if(count == WidthAni / HeightAni + 1) {// nếu count vượt quá giá trị khung hình thì trả về vị trí ban đầu
		//	setAnimation = false;
		//	scr.x = 0;// trả về vị trí ban đầu
		//	count = 0;
		//}	
	}
};

#endif