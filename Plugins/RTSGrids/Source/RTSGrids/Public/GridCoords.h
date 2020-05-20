// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "GridCoords.generated.h"

USTRUCT(BlueprintType)
struct FGridCoord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grids")
	int Col;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grids")
	int Row;

	FORCEINLINE FGridCoord();

	FORCEINLINE FGridCoord(int InColRow);

	FORCEINLINE FGridCoord(int InCol, int InRow);

	FORCEINLINE FGridCoord(FVector2D InCoord);
};

FORCEINLINE FGridCoord::FGridCoord()
	: Col(0), Row(0)
{}

FORCEINLINE FGridCoord::FGridCoord(int InColRow)
	: Col(InColRow), Row(InColRow)
{}

FORCEINLINE FGridCoord::FGridCoord(int InCol, int InRow)
	: Col(InCol), Row(InRow)
{}

FORCEINLINE FGridCoord::FGridCoord(FVector2D InCoord)
	: Col(InCoord.Y), Row(InCoord.X)
{};