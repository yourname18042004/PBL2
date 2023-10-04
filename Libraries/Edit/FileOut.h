#ifndef FILE_OUT_H
#define FILE_OUT_H

#include <FlyEdit.h>
#include <vector>

static void FileOut(std::vector <FlyEdit*>* flys, const char* path)
{
	float k = 0.8f;
	FILE* f;
	f = fopen(path, "w");
	fprintf(f, "%d\n", flys->size());
	for (int i = 0; i < flys->size(); ++i)
	{
		fprintf
		(
			f, "%0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %d\n",
			(*flys)[i]->GetStart().x / k,
			(*flys)[i]->GetStart().y / k,
			(*flys)[i]->GetWidthHeight().x / k,
			(*flys)[i]->GetWidthHeight().y / k,
			(*flys)[i]->GetEnd().x / k,
			(*flys)[i]->GetEnd().y / k,
			(*flys)[i]->getTimeStart(),
			(*flys)[i]->getTimeEnd(),
			(*flys)[i]->getSpeed() / k,
			int((*flys)[i]->getScore())
		);
	}
	fclose(f);
}


#endif // !FILE_OUT_H
