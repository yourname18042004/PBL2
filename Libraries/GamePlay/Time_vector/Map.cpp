#include "Map.h"


Map* Map::sInit = NULL;


Map* Map::Init() {
	if (sInit == NULL)
		sInit = new Map();
	return sInit;

}

void Map::release() {
	delete sInit;
	sInit = NULL;

}

void Map::readFile()
{
	m.clear();
	std::string path;// = "Data//Map-dif//Level" + std::to_string(level) + ".txt";

	char pat[100];
	
	int count;

	std::ifstream myfile("Data//Map-dif//ManagerMap.txt");
	myfile.is_open();
	myfile >> count;
	std::string tmp;
	getline(myfile, tmp);
	for (int i = 0; i < count; i++) {
		std::string tmp;
		getline(myfile, tmp);
		path = tmp;
		m.push_back(path);
	}

	myfile.close();
}

void Map::writeFile()
{
	std::ofstream myfile("Data//Map-dif//ManagerMap.txt");
	myfile.is_open();
	myfile << m.size() << "\n";
	for (int i = 0; i < m.size(); i++) {
		std::string str = m[i];
		myfile << str << "\n";
	}

	myfile.close();
}

void Map::addMap(std::string path)
{
	m.push_back(path);
	writeFile();
}
void Map::deleteMap(int i)
{
	m.erase(m.begin() + i);
	writeFile();
}

Map::Map()
{
	readFile();
}