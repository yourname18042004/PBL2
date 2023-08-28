#ifndef OBJECT_H_
#define OBJECT_H_
#pragma warning(disable : 4996)
#include<SDL.h>
#include<SDL_image.h>
#include<cstring>
#include<string.h>
#include "LoadTexture.h"
#include "Vector.h"
class Object{
	private:
		int pos_x; // Vị trí ban đầu 
		int pos_y;
		SDL_Texture* Texture;
		SDL_Rect scr, dest; //Khung hình cắt ảnh, độ to của đối tượng và vị trí trên cửa sổ
		int WidthAni, HeightAni; // Thông số ảnh đưa vào
		int count = 0; // biến đếm animation
		const char* file_path; // địa chỉ file animation

	public:
		// Khởi tạo đối tượng
		void Init(int pos_x, int pos_y,int width, int height, SDL_Renderer* Render,const char* file_path) {
			this->pos_x = pos_x;
			this->pos_y = pos_y;
			Texture = LoadImage::Load(file_path, Render);
			this->file_path = file_path;
			dest.x = pos_x;
			dest.y = pos_y;
			dest.w = width;
			dest.h = height;
			// đọc và tách thông số từ địa chỉ ảnh
			char tmp[100];
			for (int i = 0; i < strlen(file_path); i++) {
				tmp[i] = file_path[i];
			}
			char* tmpoftmp = strtok(tmp, "_");
			char* Width = strtok(NULL, "_");
			char* Height = strtok(NULL, ".");
			WidthAni = atoi(Width);
			HeightAni = atoi(Height);
			scr.w = HeightAni;
			scr.h = HeightAni;

		}
		// vẽ đối tượng
		void Render(SDL_Renderer *render) {
			SDL_RenderCopy(render, Texture, &scr, &dest);
		}
		// chuyển động của đối tượng
		void animation() {

			scr.x = (count % (WidthAni / HeightAni)) * HeightAni;
			count++;
		}
		//cập nhật tốc độ và hướng di chuyển 
		void update(Vector v) {
			dest.x += v.x;
			dest.y += v.y;
		}

};

#endif

