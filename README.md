# Tiling space in 4D with the unfoldings of 5D hypercubes

This project is inspired [WHUTS](https://whuts.org/) started by Matt Parker accompinied by this [video](https://www.youtube.com/watch?v=Yq3P-LhlcQo). However unlike trying to tile 3D space with the unfoldings of 4D hypercubes, this is my attempt at stepping this up one dimension and tiling 4D Space with the unfoldings of 5D hypercubes.
As of me writing this I have only found a solution for one out of the 9694 possible unfoldings however I might try to find some more. However I do not attempt to find tilings for all such unfoldings.

## Validity tests
To test the validity of the tiling some single file C++ code was written which will create a 4D grid and initialize it with zeros. Then the unfoldings will be filled in using periodic boundary conditions. Each cell that is filled is set to one, if a cell is allready one and the programm attempts to fill it again an exception will be thrown. Which for a valid tiling should not happen. At the end we can test all cells to check if we missed any, which again should not be the case for a valid tiling.
Compile the test using:
	make all
Run the test by running the corresponding file in build.

## Currently solved
4D equivalent of the Dali Cross: [Explanaition](4DDali.md)
