// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "GridCoords.generated.h"

USTRUCT(BlueprintType)
struct FGridCoord
{
	GENERATED_BODY()

	// GridLocation Column, or Y component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grids")
	int Col;

	// GridLocation Row, or X component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grids")
	int Row;

	// Default constructor (no initialization).
	FORCEINLINE FGridCoord();

	/** 
	 * Constructor using initial values for each component.
	 *
	 * @param InColRow XY Coordinate
	 */
	FORCEINLINE FGridCoord(int InColRow);

	/**
	 * Constructor using initial values for each component.
	 *
	 * @param InCol Y Coordinate
	 * @param InRow X Coordinate.
	 */
	FORCEINLINE FGridCoord(int InCol, int InRow);

	/**
	 * Constructor using initial values for each component.
	 *
	 * @param InCoord XY Coordinate
	 */
	FORCEINLINE FGridCoord(FVector2D InCoord);

	FORCEINLINE bool operator==(FGridCoord& V) const;

	FORCEINLINE FGridCoord operator*(float Scale) const;

	FORCEINLINE FGridCoord operator*(int Scale) const;

	FORCEINLINE FGridCoord operator*(FGridCoord& V) const;
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

FORCEINLINE bool FGridCoord::operator==(FGridCoord& V) const
{
	return Col == V.Col && Row == V.Row;
}

FORCEINLINE FGridCoord FGridCoord::operator*(float Scale) const
{
	return FGridCoord(Col * Scale, Row * Scale);

}

FORCEINLINE FGridCoord FGridCoord::operator*(int Scale) const
{
	return FGridCoord(Col * Scale, Row * Scale);
}

FORCEINLINE FGridCoord FGridCoord::operator*(FGridCoord& V) const
{
	return FGridCoord(Col * V.Col, Row * V.Row);
}

FORCEINLINE uint32 GetTypeHash(const FGridCoord& V)
{
	return FCrc::MemCrc_DEPRECATED(&V, sizeof(FGridCoord));
}
