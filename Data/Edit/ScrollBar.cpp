#include <ScrollBar.h>

ScrollHorizontal::ScrollHorizontal(float pos_x, float pos_y, float width, float height, SDL_Renderer* renderer) :
	pos_x(pos_x), pos_y(pos_y), width(width), height(height),
	renderer(renderer),
	Scroll_Bar_Shaft(SDL_FRect{ pos_x, pos_y + height * 2.0f / 5.0f, width, height / 5.0f }),
	Scroll_Bar_Part(SDL_FRect{ pos_x, pos_y + height * 2.0f / 5.0f, 0, height / 5.0f }),
	Scroll_Thumb(SDL_FRect{ pos_x, pos_y + height / 5.0f, 30, height * 3.0f / 5.0f }),
	Frame_Scroll_Bar_Shaft(new FramesObject(&Scroll_Bar_Shaft, "Data/Edit/ScrollBarShaft_50_50_50_50.png", renderer, false)),
	Frame_Scroll_Bar_Part(new FramesObject(&Scroll_Bar_Part, "Data/Edit/ScrollBarPart_50_50_50_50.png", renderer, false)),
	Frame_Scroll_Thumb(new FramesObject(&Scroll_Thumb, "Data/Edit/ScrollThumb_50_50_50_50.png", renderer, false))
{
	value = 0;
	valueMin = 0;
	valueMax = 0;
}

void ScrollHorizontal::Render()
{
	Frame_Scroll_Bar_Shaft->Get_Texture();
	Frame_Scroll_Bar_Part->Get_Texture();
	Frame_Scroll_Thumb->Get_Texture();
}

bool ScrollHorizontal::MoveCroll(bool click)
{
	if (CollisionButton(Scroll_Thumb) && click) follow = true;
	if (!click) follow = false;

	if (follow && Scroll_Thumb.x >= pos_x && Scroll_Thumb.x <= pos_x + width)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		Scroll_Thumb.x = float(x);
		Scroll_Bar_Part.w = Scroll_Thumb.x - pos_x;
	}
	if (Scroll_Thumb.x < pos_x)
	{
		Scroll_Thumb.x = pos_x;
		Scroll_Bar_Part.w = Scroll_Thumb.x - pos_x;
	}

	if (Scroll_Thumb.x > pos_x + width)
	{
		Scroll_Thumb.x = pos_x + width;
		Scroll_Bar_Part.w = Scroll_Thumb.x - pos_x;
	}
	return CollisionButton(Scroll_Thumb);
}

void ScrollHorizontal::setValue(float min, float max)
{
	this->valueMin = min;
	this->valueMax = max;
}

float ScrollHorizontal::getValue()
{
	value = valueMin + (Scroll_Thumb.x - pos_x) / (width) * (valueMax - valueMin);
	return value;
}

float ScrollHorizontal::getData()
{
	return value;
}

void ScrollHorizontal::setValue(float value)
{
	this->value = value;
	if (value >= valueMin && value <= valueMax)
	{
		Scroll_Thumb.x = pos_x + (value - valueMin) / (valueMax - valueMin) * width;
		Scroll_Bar_Part.w = Scroll_Thumb.x - pos_x;
	}
	if (value < valueMin) Scroll_Thumb.x = pos_x;
	if (value > valueMax) Scroll_Thumb.x = pos_x + width;
}




/////////////////////////////////////////////// VERTICAL ////////////////////////////////////////////////////////
// truc tung

ScrollVertical::ScrollVertical(float pos_x, float pos_y, float width, float height, SDL_Renderer* renderer) :
	pos_x(pos_x), pos_y(pos_y), width(width), height(height),
	renderer(renderer),
	Scroll_Bar_Shaft(SDL_FRect{ pos_x + width  * 2.0f / 5.0f, pos_y, width / 5.0f, height }),
	Scroll_Bar_Part(SDL_FRect{ pos_x + width * 2.0f / 5.0f, pos_y, width / 5.0f, 0}),
	Scroll_Thumb(SDL_FRect{ pos_x + width / 5.0f , pos_y - 15, width * 4.0f / 5.0f, 30 }),
	Frame_Scroll_Bar_Shaft(new FramesObject(&Scroll_Bar_Shaft, "Data/Edit/ScrollBarShaft_50_50_50_50.png", renderer, false)),
	Frame_Scroll_Bar_Part(new FramesObject(&Scroll_Bar_Part, "Data/Edit/ScrollBarPart_50_50_50_50.png", renderer, false)),
	Frame_Scroll_Thumb(new FramesObject(&Scroll_Thumb, "Data/Edit/ScrollThumb_50_50_50_50.png", renderer, false))
{
	value = 0;
	valueMin = 0;
	valueMax = 0;
}

void ScrollVertical::Render()
{
	Frame_Scroll_Bar_Shaft->Get_Texture();
	Frame_Scroll_Bar_Part->Get_Texture();
	Frame_Scroll_Thumb->Get_Texture();
}

void ScrollVertical::MoveCroll(bool click)
{
	if (CollisionButton(Scroll_Thumb) && click) follow = true;
	if (!click) follow = false;

	if (follow && Scroll_Thumb.y + 15 >= pos_y && Scroll_Thumb.y + 15 <= pos_y + height)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		Scroll_Thumb.y = float(y) - 15;
		//Scroll_Bar_Part.h = Scroll_Thumb.y - pos_y;
	}
	if (Scroll_Thumb.y + 15 < pos_y) Scroll_Thumb.y = pos_y - 15;
	if (Scroll_Thumb.y + 15 > pos_y + height) Scroll_Thumb.y = pos_y + height - 15;
}

void ScrollVertical::MoveCrollWheel(HandelEvent* Event)
{
	
	if (Event->crossDown) Scroll_Thumb.y -= height * 0.1f;
	else if (Event->crossUp) Scroll_Thumb.y += height * 0.1f;

	if (Scroll_Thumb.y + 15 < pos_y) Scroll_Thumb.y = pos_y - 15;
	if (Scroll_Thumb.y + 15 > pos_y + height) Scroll_Thumb.y = pos_y + height - 15;
}

void ScrollVertical::setValue(float min, float max)
{
	this->valueMin = min;
	this->valueMax = max;
}

float ScrollVertical::getValue()
{
	return valueMin + (Scroll_Thumb.y + 15 - pos_y) / (height) * (valueMax - valueMin);
}

void ScrollVertical::setValue(float value)
{
	this->value = value;
	if (value >= valueMin && value <= valueMax)
	{
		Scroll_Thumb.y = pos_y + (value - valueMin) / (valueMax - valueMin) * height;
		//Scroll_Bar_Part.h = Scroll_Thumb.y - pos_y;
	}
	if (value < valueMin)
	{
		Scroll_Thumb.y = pos_y;
		value = valueMin;
	}
	if (value > valueMax)
	{
		Scroll_Thumb.y = pos_y + height;
		value = valueMax;
	}
		
}