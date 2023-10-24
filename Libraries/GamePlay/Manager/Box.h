#ifndef BOX_H
#define BOX_H
#include<Init/Window.h>

struct Box {
	SDL_Renderer* renderer;
	SDL_Event event;
	HandelEvent Event;
	Buttons* buttonNext = nullptr; // nút qua màn tiếp
	Buttons* buttonBack = nullptr;// nút quay lui
	Buttons* buttonEnd1 = nullptr; // nút kết thúc
	FramesObject* box = nullptr;
	FramesObject* TaskBar = nullptr;
	void init() {
		box = new FramesObject(new SDL_FRect{ 750,350,450,300 }, "Data//Picture//star_100_100_200_100.png", renderer, true);
		buttonBack = new Buttons(620, 550, 100, 100, "Data//Picture//ButtonBack_100_100_200_100.png", renderer);
		buttonEnd1 = new Buttons(720, 550, 100, 100, "Data//Picture//ButtonEnd_100_100_200_100.png", renderer);
		buttonNext = new Buttons(820, 550, 100, 100, "Data//Picture//ButtonNext_100_100_200_100.png", renderer);
		TaskBar = new FramesObject(new SDL_FRect{ 545, 500, 350.0f, 100.0f }, "Data//Picture//ScoreTab_600_100_600_100.png", renderer, false);
	}
	void renderWin() {
		box->Get_Texture();
		TaskBar->Get_Texture();
		buttonBack->Render();
		buttonEnd1->Render();
		buttonNext->Render();
	}
	void renderLose() {
		box->Get_Texture();
		TaskBar->Get_Texture();
		buttonBack->Render();
		buttonEnd1->Render();
	}
	void resume() {
		box->Get_Texture();
		TaskBar->Get_Texture();
		buttonBack->Render();
		buttonEnd1->Render();
	}
	void SetClick() {
		buttonBack->Setclick(Event.BUTTON_LEFT);
		buttonEnd1->Setclick(Event.BUTTON_LEFT);
		buttonNext->Setclick(Event.BUTTON_LEFT);
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
};



#endif