#ifndef CONTENT_H
#define CONTENT_H
#include<SDL.h>
#include <Load/LoadDocument.h>
#include <string.h>
#include <time.h>
class Content {
protected:
	SDL_Texture* texture;
	SDL_FRect dest;
	SDL_FRect tmp;
	SDL_Rect src;
	SDL_Renderer* renderer;

	std::string content;
public:
	//Khởi tạo text;
	void init(int x, int y, int w, int h,
		const char* font, int size, SDL_Color Color,
		const char* content, SDL_Renderer* renderer)
	{
		texture = Font::LoadChar(font, &dest.w, &dest.h, size, Color, content, renderer);
		this->renderer = renderer;
		dest.w = w;
		dest.h = h;
		dest.x = x;
		dest.y = y;
		tmp = dest;
		this->content = content;
	}
	//cập nhật lại text
	void update(int x, int y, int w, int h,
		const char* font, int size, SDL_Color Color,
		const char* content)
	{
		SDL_Texture* tmp = texture;
		texture = nullptr;
		texture = Font::LoadChar(font, &dest.w, &dest.h, size, Color, content, renderer);
		dest.w = w;
		dest.h = h;
		dest.x = x;
		dest.y = y;
		this->content = content;
		SDL_DestroyTexture(tmp);
	}


	void render() {
		SDL_Rect src; 
		src.x = 0;
		src.y = 0;
		src.w = content.size() * dest.h / 2.0f;
		src.h = dest.h;

		dest.w = float(src.w);
		//std::cout << content << ":" << src.w << " " << src.h << std::endl;
		SDL_RenderCopyF(renderer, texture, &src, &dest);
	}

	void update(float x, float y)
	{
		dest.x = x;
		dest.y = y;
		tmp.x = x;
		tmp.y = y;
	}
	
	void update(bool set)
	{
		if (set)
		{
			dest.w = tmp.w * 1.2f;
			dest.h = tmp.h * 1.2f;
			dest.x = tmp.x - tmp.w * 0.2f / 2;
			dest.y = tmp.y - tmp.h * 0.2f / 2;
		}
		else {
			dest.w = tmp.w;
			dest.h = tmp.h;
			dest.x = tmp.x;
			dest.y = tmp.y;
			}
		}
	
};


static std::string toStr(float value)
{
	std::string content;

	std::ostringstream convert;
	convert << value;
	content = convert.str();

	return content;
}

static std::string toStr(float value, const char* str)
{
	std::string content;

	std::ostringstream convert;
	convert << value;
	content = str + convert.str();

	return content;
}

static std::string toClock(float value)
{
	int m = int(value / 60);
	int s = int(value - m * 60);
	int ms = int((value - m * 60 - s) * 100);

	std::string content;

	std::ostringstream M, S, MS;
	M << m;
	if (m < 10) content = "0" + M.str();
	else content = M.str();

	S << s;
	if (s < 10) content += " : 0" + S.str();
	else content += " : " + S.str();

	MS << ms;
	if (ms < 10) content += " : 0" + MS.str();
	else content += " : " + MS.str();
	//std::cout << content << "  " << m << " : " << s << " : " << ms  << std::endl;
	return content;
}


#endif