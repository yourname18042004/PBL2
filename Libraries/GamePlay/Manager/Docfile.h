#ifndef DOCFILE_H
#define DOCFILE_H
#include <Init/Window.h>
#include <fstream>

static void ReadFile(ObjectLinkList<Fly>* FlyLinkList, SDL_Renderer* Render, float* timegame, const char* path)
{
	int count; // so ruoi;
	float pos_x;
	float pos_y;
	float width;
	float height;
	float end_x;
	float end_y;
	float t_to_a;
	float t_to_land;
	float speed;
	int score;

	FILE* f;
	f = fopen(path, "r");
	if (f == NULL) {
		printf("khong doc duoc tep");
	}

	fscanf(f, "%d", &count);
	int i;
	for (i = 0; i < count; i++) {
		fscanf(f, "%f", &pos_x);
		fscanf(f, "%f", &pos_y);
		fscanf(f, "%f", &width);
		fscanf(f, "%f", &height);
		fscanf(f, "%f", &end_x);
		fscanf(f, "%f", &end_y);
		fscanf(f, "%f", &t_to_a);
		fscanf(f, "%f", &t_to_land);
		fscanf(f, "%f", &speed);
		fscanf(f, "%d", &score);
		FlyLinkList->push(new Fly(pos_x, pos_y, width, height,
									end_x, end_y, t_to_a, t_to_land,
									speed, Render, score, timegame));
		}
	fclose(f);
}



#endif // !DOCFILE_H
