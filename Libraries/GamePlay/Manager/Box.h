﻿#ifndef BOX_H
#define BOX_H
#include<Init/Window.h>
#include "ScrollBar.h"


struct Box {

	SDL_Event event;
	HandelEvent Event;
	Buttons* buttonNext = nullptr; // nút qua màn tiếp
	Buttons* buttonBack = nullptr;// nút quay lui
	Buttons* buttonEnd1 = nullptr; // nút kết thúc
	FramesObject* box = nullptr;
	FramesObject* TaskBar = nullptr;
	Text ifWin; // thông báo nếu thắng
	Text ifLose; // thông báo nếu thua
	Text ifResume; // thông báo nếu dừng
	Text Congrat;
	Buttons* SoundCheck = nullptr;
	

	void init(SDL_Renderer* renderer) {
		box = new FramesObject(new SDL_FRect{ 495,200,450,300 }, "Data//Picture//box_300_200_600_200.png", renderer, false);
		buttonBack = new Buttons(620, 435, 100, 100, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
		buttonEnd1 = new Buttons(720, 435, 100, 100, "Data//Picture//ButtonEnd_100_100_200_100.png", renderer);
		buttonNext = new Buttons(820, 435, 100, 100, "Data//Picture//ButtonNext_100_100_200_100.png", renderer);
		SoundCheck = new Buttons(870, 560, 40, 40, "Data//Picture//OK_100_100_200_100.png", renderer);
		TaskBar = new FramesObject(new SDL_FRect{ 470,500,500,140 }, "Data//Picture//Setting_540_160_540_160.png", renderer, false);

		ifWin.init(630, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOU WIN! ", renderer);
		ifLose.init(620, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "YOU LOSE!", renderer);
		ifResume.init(620, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "Resume", renderer);
		Congrat.init(620, 250, 200, 50, "Data//Galhau_Regular.ttf", 25, { 255,0,0, 255 }, "Congratulation!", renderer);

	
	}
	void renderWin(bool set) {
		
		box->Get_Texture();
		ifWin.render();
		
		buttonBack->Render();
		buttonEnd1->Render();
		buttonNext->Render();
		
	}
	void renderLast(bool set) {
	
		box->Get_Texture();
		Congrat.render();
		
		buttonBack->Render();
		buttonEnd1->Render();
		
	}
	void renderLose(bool set) {
		
		box->Get_Texture();
		ifLose.render();
		
		buttonBack->Render();
		buttonEnd1->Render();
		
	}
	void resume(bool set) {
		
		box->Get_Texture();
		ifResume.render();
		TaskBar->Get_Texture();
		buttonBack->Render();
		buttonEnd1->Render();
		if (!set) SoundCheck->Render();

	}
	void SetClick(bool set) {
		buttonBack->Setclick(set);
		buttonEnd1->Setclick(set);
		buttonNext->Setclick(set);
		SoundCheck->Setclick(set);
	}
	void SetClicklast(bool set) {
		buttonBack->Setclick(set);
		buttonEnd1->Setclick(set);
		SoundCheck->Setclick(set);
	}
	bool getclickBack() {
		return buttonBack->Getclick();
	}
	bool getclickNext() {
		return buttonNext->Getclick();
	}
	bool getclickEnd() {
		return buttonEnd1->Getclick();
	}
	bool getclickSoundCheck() {
		return SoundCheck->Getclick();
	}
};



#endif