#include "TexBox.h"

TextBox::TextBox(float pos_x, float pos_y, float width, float height, SDL_Renderer* renderer) :
pos_x(pos_x),
pos_y(pos_y),
width(width),
height(height),
renderer(renderer),
tex_rect(SDL_FRect{ pos_x, pos_y, width, height }),
frame_tex(new FramesObject(&tex_rect, "Data/Edit/TexBox_100_50_100_50.png", renderer, false))

{
	setPick = false;
	back_space = false;
	frame_content.init(pos_x + 10, pos_y, width, height, "Data//Galhau_Regular.ttf", height, { 0, 0, 0, 255 }, content.c_str(), renderer);
}

void TextBox::Update(HandelEvent& event)
{

	if (event.BUTTON_LEFT)
	{
		if (CollisionButton(tex_rect))
		{
			setPick = true;
		}
		else
		{
			setPick = false;
		}
	}
	if (!event.getBachSpace())
	{
		back_space = false;
	}
	if (!back_space && event.getBachSpace() && content.length() > 0)
	{
		back_space = true;
		content.pop_back();
		frame_content.update(pos_x + 10, pos_y, width, height, "Data//Galhau_Regular.ttf", height, { 0, 0, 0, 255 }, content.c_str());
	}
	if(event.event.type == SDL_TEXTINPUT && setPick)
	{
		if(content.length() <= 12)
		content = content + event.event.text.text;
		frame_content.update(pos_x + 10, pos_y, width, height, "Data//Galhau_Regular.ttf", height, { 0, 0, 0, 255 }, content.c_str());
	}
}

void TextBox::Render()
{
	frame_tex->Get_Texture();

	frame_content.render();
}