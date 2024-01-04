#ifndef _MAP_H
#define _MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Map {
private:

	
public:
	static Map* sInit;
	static Map* Init();
	static void release();

	void readFile();
	void writeFile();
	void addMap(std::string path);
	void deleteMap(int i);

public:
	std::vector <std::string> m;

	Map();
	~Map(){}

};

#endif // !MAP_H_