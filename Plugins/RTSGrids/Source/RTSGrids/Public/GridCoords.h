// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GridCoords.generated.h"

USTRUCT(BlueprintType)
struct FGridCoord
{

public:

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

UCLASS()
class UGridCoordinateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Grids", meta=(DisplayName = "Equal (GridCoords)", CompactNodeTitle = "==", Keywords = "equal =", ToolTip = "Return true if A is equal to B"))
	static bool Equal_CoordCoord(FGridCoord A, FGridCoord B);

	UFUNCTION(BlueprintPure, Category = "Grids", meta = (DisplayName = "Multiply (float)", CompactNodeTitle = "*", Keywords = "multiply * times", ToolTip = "A * B"))
	static FGridCoord Multiply_CoordFloat(FGridCoord A, float B);

	UFUNCTION(BlueprintPure, Category = "Grids", meta = (DisplayName = "Multiply (int)", CompactNodeTitle = "*", Keywords = "multiply * times", ToolTip = "A * B"))
	static FGridCoord Multiply_CoordInt(FGridCoord A, int B);

	UFUNCTION(BlueprintPure, Category = "Grids", meta = (DisplayName = "Multiply (vector2D)", CompactNodeTitle = "*", Keywords = "multiply * times", ToolTip = "A * B"))
	static FGridCoord Multiply_CoordCoord(FGridCoord A, FGridCoord B);

	UFUNCTION(BlueprintPure, Category = "Grids", meta = (DisplayName = "Convert to vector2D", CompactNodeTitle = "conv", BlueprintAutocast, Keywords = "convert convVector2D", ToolTip = "Convert to vector2D"))
	static FVector2D Conv_GridCoordToVector2D(FGridCoord A);

};


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
