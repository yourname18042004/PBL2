#ifndef FILE_OUT_H
#define FILE_OUT_H

#include <FlyEdit.h>
#include <vector>
#include <random>
#include <ctime>
#include <Time_vector/Map.h>

static void FileOut(std::vector <FlyEdit*>* flys, std::string path)
{
	float k = 0.8f;
	int count;
	FILE* f;
	
	f = fopen("Data//Map-dif//ManagerMap.txt", "r");
	fscanf(f, "%d", &count);

	fclose(f);

	std::srand(std::time(0));
	int ran = std::rand() % 100000000;

	std::string str = "Data//Map-dif//" + path + ".txt";
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
			(*flys)[i]->getTimePause(),
			(*flys)[i]->getSpeed() / k,
			int((*flys)[i]->getScore())
		);
	}
	fclose(f);

	Map::sInit->addMap(str);
/*
	f = fopen("Data//Map-dif//ManagerMap.txt", "r+");

	int size;
	fscanf(f, "%d", &size);
	std::vector <std::string> map;

	for (int i = 0; i < size; ++i)
	{
		char p[50];
		fscanf(f, "%s", p);
		map.push_back(p);
	}

	fclose(f);

	
	++size;

	f = fopen("Data//Map-dif//ManagerMap.txt", "w");

	fprintf(f, "%d\n", size);

	for (int i = 0; i < size - 1; ++i)
	{
		std::cout << map[i] << "\n";
		fprintf(f, "%s\n", map[i].c_str());
	}
	std::string tmp = path + ".txt";
	fprintf(f, "%s\n", tmp.c_str());

	fclose(f);*/
}


#endif // !FILE_OUT_H
