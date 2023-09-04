#ifndef OBJECT_H_
#define OBJECT_H_
#pragma warning(disable : 4996)
#include<SDL.h>
#include<SDL_image.h>
#include<cstring>
#include<string.h>
#include "LoadTexture.h"
#include "Vector.h"


class Object {
protected:
	float pos_x; // Vị trí ban đầu 
	float pos_y;
	SDL_Texture* Texture;
	SDL_Renderer* renderer;
	SDL_Rect scr; //Khung hình cắt ảnh, độ to của đối tượng và vị trí trên cửa sổ
	SDL_FRect dest;
	int WidthAni, HeightAni; // Thông số ảnh đưa vào
	int count = 0; // biến đếm animation
	const char* file_path; // địa chỉ file animation

public:
	// Khởi tạo đối tượng
	Object(float pos_x, float pos_y, float width, float height, SDL_Renderer* Render, const char* file_path); 
	// vẽ đối tượng
	void Render(SDL_Renderer* render); 
	// chuyển động của đối tượng
	void Animation(bool a);
	//cập nhật tốc độ và hướng di chuyển 
	void UpdateObject(Vector v);
	// Trả về vị trí đối tượng;
	void setPosition(Vector v); 

	Vector getPosition() { return Vector{ pos_x, pos_y }; }
	
	SDL_FRect GetRect();
};

#endif

