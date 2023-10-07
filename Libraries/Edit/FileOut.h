#ifndef FILE_OUT_H
#define FILE_OUT_H

#include <FlyEdit.h>
#include <vector>

static void FileOut(std::vector <FlyEdit*>* flys, const char* path)
{
	float k = 0.8f;
	int count;
	FILE* f;
	
	f = fopen("Data//Map-dif//ManagerMap.txt", "r");
	fscanf(f, "%d", &count);

	fclose(f);


	std::string str = "Data//Map-dif//Level" + std::to_string(count + 1) + ".txt";
	f = fopen(str.c_str(), "w");
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


	f = fopen("Data//Map-dif//ManagerMap.txt", "w");
	fprintf(f, "%d", count + 1);

	fclose(f);
}


#endif // !FILE_OUT_H
