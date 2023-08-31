#ifndef _RACKET_
#define _RACKET_

#include "Object.h"
#include "HandelEvent.h"
#include <SDL.h>
class Racket : public Object {

private:
	bool setanimation;// biến kiểm tra có thực hiện animation hay không

public:
	// khởi tạo giá trị false cho biến kiểm tra
	void SetTheAnimation() {
		this->setanimation = false;
	}
	// update vị trí chuột
	void UpdatePositionOfMouse() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		dest.x = (float)(x - dest.w / 2);
		dest.y = (float)(y - dest.h / 2);

	}
	
	void AnimationRacket(HandelEvent handel) {
		if (setanimation) {
			Animation();
			}
		if (handel.BUTTON_LEFT) {
			setanimation = true;

		}
		if(count == WidthAni / HeightAni + 1) {// nếu count vượt quá giá trị khung hình thì trả về vị trí ban đầu
			SDL_Delay(50);
			setanimation = false;
			scr.x = 0;// trả về vị trí ban đầu
			count = 0;
		}	
	}
};

#endif