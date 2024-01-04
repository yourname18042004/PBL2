#include "Frame.h"

TextBox* tex;

Frame::Frame(int pos_x, int pos_y, int width, int height, SDL_Renderer* renderer) :
pos_x(pos_x), pos_y(pos_y), width(width), height(height), renderer(renderer),
Area(new FramesObject(new SDL_FRect{ float(pos_x), float(pos_y), float(width), float(height) }, "Data/Edit/OutBox_120_60_120_60.png", renderer, false))

{
	tex = new TextBox(pos_x + width * 0.1f, pos_y + height * 0.3f, width * 0.8f, width * 0.1f, renderer);
	OK = new Buttons(pos_x + width * 0.4f, pos_y + height * 0.7f, width * 0.1f, width * 0.1f, "Data//Edit//Back_50_50_100_50.png", renderer);
	Cancel = new Buttons(pos_x + width * 0.6f, pos_y + height * 0.7f, width * 0.1f, width * 0.1f, "Data//Edit//Back_50_50_100_50.png", renderer);

}

void Frame::Update(HandelEvent& event)
{
	tex->Update(event);

	OK->Setclick(event.BUTTON_LEFT);
	Cancel->Setclick(event.BUTTON_LEFT);
}
void Frame::Render()
{
	Area->Get_Texture();

	tex->Render();

	OK->Render();
	Cancel->Render();
}
std::string Frame::getContent()
{
	return tex->getContent();
}

Frame::~Frame()
{
	delete tex;
	delete OK;
	delete Cancel;
}

