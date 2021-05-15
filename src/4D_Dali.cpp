// Tiling found by Joshua Gehre

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <stdio.h>
#include <string>

// Size of our box
#define PeriodX 4
#define PeriodY 20
#define PeriodZ 20
#define PeriodW 20

void applyPB(int& val, int period)
{
	val %= period;
	// Make sure we dont get negative values
	if(val < 0)
		val += period;
}

// Fill a single cell
void fill(char* grid, int x, int y, int z, int w)
{
	// Periodic boundaries
	applyPB(x, PeriodX);
	applyPB(y, PeriodY);
	applyPB(z, PeriodZ);
	applyPB(w, PeriodW);
	// Calculate the index in the grid
	int index = ((x * PeriodY + y) * PeriodZ + z) * PeriodW + w;
	if(grid[index] != 0) {
		// Exit if the cell is already filled
		throw std::logic_error(("Already filled (" + std::to_string(x) + "," +
								std::to_string(y) + "," + std::to_string(z) + "," +
								std::to_string(w) + ")\n")
								   .c_str());
	}
	// Fill the cell
	grid[index] = 1;
}

// There are eight possible directions where the cross
// could be one block longer, but we only need
// +y and -y so we'll just use a boolean for that
void dali4d(char* grid, int x, int y, int z, int w, bool direction)
{
	// Center
	fill(grid, x, y, z, w);
	// One in each direction
	fill(grid, x + 1, y, z, w);
	fill(grid, x - 1, y, z, w);
	fill(grid, x, y + 1, z, w);
	fill(grid, x, y - 1, z, w);
	fill(grid, x, y, z + 1, w);
	fill(grid, x, y, z - 1, w);
	fill(grid, x, y, z, w + 1);
	fill(grid, x, y, z, w - 1);
	// Two steps in +y or -y
	fill(grid, x, y + (direction ? 2 : -2), z, w);
}

void step1(char* grid, int x, int y, int z, int w)
{
	// 2 crosses pointing in opposite directions
	// along the x-axis
	dali4d(grid, x, y, z, w, true);
	dali4d(grid, x + 2, y + 1, z, w, false);
}

void step2(char* grid, int x, int y, int z, int w)
{
	// Fill up plane using step1
	// This will make two loops along the y-axis
	// Filling in two layers in a 3D box
	for(int i = 0; i < 20; i++) {
		step1(grid, x - i, y - 2 * i, z - i, w);
	}
}

void step3(char* grid, int x, int y, int z, int w)
{
	// Fill in the an entire 3D volume except for
	// some intentional holes and with some blocks
	// sticking out on the w-axis
	for(int i = 0; i < 4; i++) {
		step2(grid, x + i, y - i, z + 2 * i, w);
	}
}

void step4(char* grid, int x, int y, int z, int w)
{
	// Fill the entire 4D space using the previous
	// 3D tiling so that the remaining holes are
	// filled by the neighbouring tilings
	for(int i = 0; i < 20; i++) {
		step3(grid, x + 2 * i, y, z + i, w + i);
	}
}

int countFilled(char* grid, int size)
{
	// Specify 0UL so we dont accumalete
	// 8-bit chars which would overflow
	return std::accumulate(grid, grid + size, 0UL);
}

int main()
{
	int totalSize = PeriodX * PeriodY * PeriodZ * PeriodW;
	char* grid = new char[totalSize];
	std::fill(grid, grid + totalSize, 0);
	// Test that we have zero
	printf("We start with %d filled cells!\n", countFilled(grid, totalSize));
	// Put in all crosses
	// Start with the last step working backwards
	step4(grid, 0, 0, 0, 0);
	// Test if we have filled all tiles
	int totalFilled = countFilled(grid, totalSize);
	double percentage = (100.0 * totalFilled) / totalSize;
	printf("Filled %d out of %d cells (%.2f%%)\n", totalFilled, totalSize, percentage);
	if(totalFilled == totalSize){
		printf("This is a valid tiling!\n");
	}else{
		printf("This is NOT a valid tiling!\n");
	}
	// Clean up allocated memory
	delete[] grid;
}
