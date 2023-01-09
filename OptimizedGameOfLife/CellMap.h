#pragma once
#include <iostream>
#include "Draw.h"

using namespace std;

#define OFF_COLOUR 0x00
#define ON_COLOUR 0xFF

class CellMap
{
public:
	CellMap(unsigned int w, unsigned int h);
	~CellMap();
	void NextGen();
	void Init();
	Draw draw;
private:
	unsigned char* cells;
	unsigned char* temp_cells;
	int w, h, seed;
	void AffectNeighbour(unsigned int x, unsigned int y, int add);
	unsigned int CellState(unsigned int x, unsigned int y);
};

