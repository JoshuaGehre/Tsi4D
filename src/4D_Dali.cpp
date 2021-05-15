#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <stdio.h>
#include <string>

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

void fill(char* grid, int x, int y, int z, int w)
{
	applyPB(x, PeriodX);
	applyPB(y, PeriodY);
	applyPB(z, PeriodZ);
	applyPB(w, PeriodW);
	int index = ((x * PeriodY + y) * PeriodZ + z) * PeriodW + w;
	if(grid[index] != 0) {
		throw std::logic_error(("Allready filled (" + std::to_string(x) + "," +
								std::to_string(y) + "," + std::to_string(z) + "," +
								std::to_string(w) + ")\n")
								   .c_str());
	}
	grid[index] = 1;
}

// There are eight possible directions but we only need
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
	dali4d(grid, x, y, z, w, true);
	dali4d(grid, x + 2, y + 1, z, w, false);
}

void step2(char* grid, int x, int y, int z, int w)
{
	for(int i = 0; i < 20; i++) {
		step1(grid, x - i, y - 2 * i, z - i, w);
	}
}

void step3(char* grid, int x, int y, int z, int w)
{
	for(int i = 0; i < 4; i++) {
		step2(grid, x + i, y - i, z + 2 * i, w);
	}
}

void step4(char* grid, int x, int y, int z, int w)
{
	for(int i = 0; i < 20; i++) {
		step3(grid, x + 2 * i, y, z + i, w + i);
	}
}

int main()
{
	int totalSize = PeriodX * PeriodY * PeriodZ * PeriodW;
	char* grid = new char[totalSize];
	std::fill(grid, grid + totalSize, 0);
	// Test that we have zero
	int sum = std::accumulate(grid, grid + totalSize, 0UL);
	printf("We start with %d filled\n", sum);
	// Put in all crosses
	step4(grid, 0, 0, 0, 0);
	// Test if we have filled all tiles
	sum = std::accumulate(grid, grid + totalSize, 0UL);
	printf("Filled %d out of %d\n", sum, totalSize);
}
