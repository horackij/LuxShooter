// Copyright Joe Horacki 2020


#include "GridCoords.h"

bool UGridCoordinateLibrary::Equal_CoordCoord(FGridCoord A, FGridCoord B)
{
	return A == B;
}

FGridCoord UGridCoordinateLibrary::Multiply_CoordFloat(FGridCoord A, float B)
{
	return A * B;
}

FGridCoord UGridCoordinateLibrary::Multiply_CoordInt(FGridCoord A, int B)
{
	return A * B;
}

FGridCoord UGridCoordinateLibrary::Multiply_CoordCoord(FGridCoord A, FGridCoord B)
{
	return A * B;
}

FVector2D UGridCoordinateLibrary::Conv_GridCoordToVector2D(FGridCoord A)
{
	return FVector2D(A.Row, A.Col);
}
