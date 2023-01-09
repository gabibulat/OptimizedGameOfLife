#include "CellMap.h"

CellMap::CellMap(unsigned int width, unsigned int height)
{
	w = width;
	h = height;
	cells = new unsigned char[width * height];  // Cell storage
	temp_cells = new unsigned char[width * height]; // Temp cell storage
	memset(cells, 0, width * height);  // Clear all cells, to start
}

CellMap::~CellMap()
{
	delete[] cells;
	delete[] temp_cells;
}

unsigned int CellMap::CellState(unsigned int x, unsigned int y)
{
	unsigned char* cell_ptr = cells + (y * w) + x;

	// Return first bit (LSB: cell state stored here)
	return *cell_ptr & 0x01;
}

void CellMap::Init()
{
	// Randomly initialise cell map with ~50% on pixels
	unsigned int x, y, init_length;
	seed = (unsigned)time(NULL);
	srand(seed);
	init_length = (w * h) / 2;
	do
	{
		x = rand() % (w - 1);
		y = rand() % (h - 1);
		if (CellState(x, y) == 0)
			AffectNeighbour(x, y, 2);
	} while (--init_length);
}

void CellMap::AffectNeighbour(unsigned int x, unsigned int y, int Add)
{
	int xoleft, xoright, yoabove, yobelow;
	unsigned char* cell_ptr = cells + (y * w) + x;

	// Calculate the offsets to the eight neighboring cells
	xoleft = (x == 0) ? 0 : -1;
	xoright = (x == (w - 1)) ? 0 : 1;
	yoabove = (y == 0) ? 0 : -w;
	yobelow = (y == (h - 1)) ? 0 : w;

	// Set first bit to 1
	if (Add > 0)	*(cell_ptr) |= 0x01;
	else *(cell_ptr) &= ~0x01;

	// Check if neighbour exists and add/subtract cell
	if (yoabove != 0) {
		if (xoleft != 0)*(cell_ptr + yoabove + xoleft) = *(cell_ptr + yoabove + xoleft) + Add;
		if (xoright != 0)*(cell_ptr + yoabove + xoright) = *(cell_ptr + yoabove + xoright) + Add;
		*(cell_ptr + yoabove) = *(cell_ptr + yoabove) + Add;
	}
	if (xoleft != 0)*(cell_ptr + xoleft) = *(cell_ptr + xoleft) + Add;
	if (xoright != 0)*(cell_ptr + xoright) = *(cell_ptr + xoright) + Add;

	if (yobelow != 0)
	{
		if (xoleft != 0)*(cell_ptr + yobelow + xoleft) = *(cell_ptr + yobelow + xoleft) + Add;

		if (xoright != 0)*(cell_ptr + yobelow + xoright) = *(cell_ptr + yobelow + xoright) + Add;
		*(cell_ptr + yobelow) = *(cell_ptr + yobelow) + Add;
	}

}

void CellMap::NextGen()
{
	unsigned int x, y, count;
	unsigned char* cell_ptr;

	// Copy to temp map to keep an unaltered version
	memcpy(temp_cells, cells, w * h);

	// Process all cells in the current cell map
	cell_ptr = temp_cells;
	for (y = 0; y < h; y++) {

		x = 0;
		do {

			// Zero bytes are off and have no neighbours 
			while (*cell_ptr == 0) {
				cell_ptr++; // Advance to the next cell
				// If all cells in row are off with no neighbours go to next row
				if (++x >= w) goto RowDone;
			}

			// Remaining cells are either on or have neighbours
			count = *cell_ptr >> 1; // Number of neighboring on-cells
			if (*cell_ptr & 0x01) {

				// On cell must turn off if not 2 or 3 neighbours
				if ((count != 2) && (count != 3)) {
					AffectNeighbour(x, y, -2);
					draw.DrawCell(x, y, OFF_COLOUR);
				}
			}
			else {

				// Off cell must turn on if 3 neighbours
				if (count == 3) {
					AffectNeighbour(x, y, 2);
					draw.DrawCell(x, y, ON_COLOUR);
				}
			}

			// Advance to the next cell byte
			cell_ptr++;

		} while (++x < w);
	RowDone:;
	}
}

