// Copyright Joe Horacki 2020


#include "GridSystem.h"

// Sets default values
AGridSystem::AGridSystem()
	: GridDimensions(FGridCoord(4))
	, CellSize(100.0)
	, bShowPreviewGrid(true)
	, bShowTileTextInfo(false)
	, bDrawBoundingBox(true)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<FGridCoord> AGridSystem::GenerateGrid()
{
	GeneratedGrid.Empty();

	int xMin, xMax, yMin, yMax;

	xMin = 0;
	xMax = GridDimensions.Row;
	yMin = 0;
	yMax = GridDimensions.Col;

	for (int i = xMin; i < xMax; i++)
	{
		for (int j = yMin; j < yMax; j++)
		{
			FGridCoord Coord;
			Coord.Row = i;
			Coord.Col = j;
			GeneratedGrid.Emplace(Coord);
		}
	}

	return GeneratedGrid;
}

FVector AGridSystem::GetGridOriginRelative()
{
	FVector Result;
	const float CellHalfSize = CellSize * 0.5;

	Result.X = ((GridDimensions.Row * 0.5) * CellSize) - CellHalfSize;
	Result.Y = ((GridDimensions.Col * 0.5) * CellSize) - CellHalfSize;
	Result.Z = 0.0;
	return Result;
}

FVector AGridSystem::GetGridOriginWorld()
{
	return GetGridOriginRelative() + GetActorLocation();
}

FVector2D AGridSystem::GetGridSize()
{
	return FVector2D(GridDimensions.Row * CellSize, GridDimensions.Col * CellSize);
}

FVector2D AGridSystem::GetGridExtents()
{
	return GetGridSize() * 0.5;
}

FVector AGridSystem::GetGridRelativeFromWorld(FVector WorldLocation)
{
	return WorldLocation - GetActorLocation();
}

FVector AGridSystem::GetCellCenterFromRelative(FVector RelativeLocation, bool bReturnWorldSpace)
{
	int ID;

	const FGridCoord Coord = GetCoordinateFromRelative(RelativeLocation, ID);

	FVector CellCenter;

	CellCenter.X = Coord.Row * CellSize;
	CellCenter.Y = Coord.Col * CellSize;
	CellCenter.Z = 0.0;

	return bReturnWorldSpace ? CellCenter + GetActorLocation() : CellCenter;

}

bool AGridSystem::IsInGridBounds(FGridCoord Coordinate)
{
	return (Coordinate >= FGridCoord(0, 0) && Coordinate < GridDimensions);
}

bool AGridSystem::IsClearTile(FGridCoord Coordinate)
{

}

bool AGridSystem::IsValidLocation(FGridCoord Coordinate)
{

}

FGridCoord AGridSystem::GetCoordinateFromRelative(FVector RelativeLocation, int& CellID)
{

}

FGridCoord AGridSystem::GetCoordinateFromCellID(int ID)
{

}

// Called when the game starts or when spawned
void AGridSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

